// stm32f7_basic_TS_synth_dma.c
// Jay's Lab
//
// Gets caught in MemManage_Handler()

#include "stm32f7_wm8994_init.h"
#include "stm32f7_display.h"
#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd.h"

#define SOURCE_FILE_NAME 	"stm32f7_basic_TS_synth_dma.c"
#define BLANK_COLOR			LCD_COLOR_WHITE
#define BACKGROUND_COLOR	LCD_COLOR_WHITE
#define FOREGROUND_COLOR	LCD_COLOR_BLACK
#define HIGHLIGHT_COLOR		LCD_COLOR_RED
#define UpDownStateMax		255
#define amplitudeMax		4000

extern volatile int32_t TX_buffer_empty; 		// these may not need to be int32_t
extern volatile int32_t RX_buffer_full; 		// they were extern volatile int16_t in F4 version
extern int16_t rx_buffer_proc, tx_buffer_proc; 	// will be assigned token values PING or PONG
static TS_StateTypeDef TS_State;				// keeps track of touchscreen state
static uint16_t x, y;							// x, y coordinates for TS press
static uint8_t mode;							// keeps track of which key pressed
static uint8_t TSPressed;						// 1 if TS pressed in current DMA block
static uint8_t LastPress;						// 1 if TS pressed in previous DMA block
static float32_t theta;							// keeps track of signal phase
const float32_t sampleFreq = 8000.0;			// use 8000 Hz sample rate in DMA mode with TS input
int j, k;
static float32_t freq[5] = {440, 880, 1760, 3520, 7040};						// NEED TO ASSIGN FREQUENCIES FOR EACH MODE (KEY PRESS)
static float32_t thetaIncr[5];					// corresponding digital frequencies (computed in main())
static int16_t amplitude = 2000;				// amplitude for synth output
static uint8_t CircleOn = 0;					// default state off = 0; on if nonzero
static uint8_t UpDownState = 0;					// default state = 0
static uint16_t sliderPos = 60;					// should be between 20 and 100

// draw basic keyboard features
void DrawKeyboard(void) {
	// Top line
	BSP_LCD_DrawHLine(0,136,480);
	// Bottom line
	BSP_LCD_DrawHLine(0,271,480);
	// Left side of key 0
	BSP_LCD_DrawVLine(0,136,136);
	// Line between keys 0 and 1
	BSP_LCD_DrawVLine(96,136,136);
	// Line between keys 1 and 2
	BSP_LCD_DrawVLine(192,136,136);
	// Line between keys 2 and 3
	BSP_LCD_DrawVLine(288,136,136);
	// Line between keys 3 and 4
	BSP_LCD_DrawVLine(384,136,136);
	// Right side of key 4
	BSP_LCD_DrawVLine(479,136,136);
}

// draw up or down button
void DrawUpDownButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t ButtonUp) {
	Point triangle[3];
	uint16_t xcenter = x + (uint16_t) (width/2);
	uint16_t xleft = x + (uint16_t) (0.1*width);
	uint16_t xright = x + (uint16_t) (0.9*width);
	uint16_t ytop = y + (uint16_t) (0.1*height);
	uint16_t ybottom = y + (uint16_t) (0.9*height);
	BSP_LCD_DrawRect(x,y,width,height);
	if (ButtonUp) {
		triangle[0].X = xcenter;
		triangle[0].Y = ytop;
		triangle[1].X = xleft;
		triangle[1].Y = ybottom;
		triangle[2].X = xright;
		triangle[2].Y = ybottom;
	} else {
		triangle[0].X = xcenter;
		triangle[0].Y = ybottom;
		triangle[1].X = xleft;
		triangle[1].Y = ytop;
		triangle[2].X = xright;
		triangle[2].Y = ytop;
	}
	BSP_LCD_FillPolygon(triangle, 3);
}

// unchanging info for top screen
void DrawTopScreen(void) {
	// circle button on upper left
	BSP_LCD_DrawCircle(48, 68, 20);
	// up/down buttons in upper center
	DrawUpDownButton(210, 100, 25, 25, 1);
	DrawUpDownButton(245, 100, 25, 25, 0);
	// box for number display above up/down buttons
	BSP_LCD_DrawRect(210, 20, 60, 60);
	// slider on upper right
	BSP_LCD_DrawVLine(432, 20, 80);
	BSP_LCD_DrawHLine(422, 20, 20);
	BSP_LCD_DrawHLine(427, 40, 10);
	BSP_LCD_DrawHLine(427, 60, 10);
	BSP_LCD_DrawHLine(427, 80, 10);
	BSP_LCD_DrawHLine(422, 100, 20);
}

// make changes to info on top screen when needed
void UpdateTopScreen(void) {
	char text[10];
	Point triangle[3];
	// fill circle button if on
	if (CircleOn) BSP_LCD_FillCircle(48, 68, 18);
	// number above up/down buttons
	sprintf((char *)text, "%2d", UpDownState);
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(0, 30, (uint8_t *)text, CENTER_MODE);
	BSP_LCD_SetFont(&Font12);
	// update slider position
	triangle[0].X = 432;
	triangle[1].X = 426;
	triangle[2].X = 438;
	triangle[0].Y = sliderPos;
	triangle[1].Y = sliderPos + 5;
	triangle[2].Y = sliderPos + 5;
	BSP_LCD_SetTextColor(HIGHLIGHT_COLOR);
	BSP_LCD_FillPolygon(triangle, 3);
	BSP_LCD_SetTextColor(FOREGROUND_COLOR);
}

// (re)draw screen whenever info changes
void ResetScreen(void) {
	BSP_LCD_Clear(BLANK_COLOR);
	BSP_LCD_SetBackColor(BACKGROUND_COLOR);
	BSP_LCD_SetTextColor(FOREGROUND_COLOR);
	BSP_LCD_SetFont(&Font12);
	DrawKeyboard();
	DrawTopScreen();
	UpdateTopScreen();
}

// test whether (x, y) is in rectangle with corners (x_left, y_top), (x_right, y_bottom)
uint8_t inrect(uint16_t x, uint16_t y, uint16_t x_left, uint16_t x_right, uint16_t y_top, uint16_t y_bottom) {
	uint8_t IsInRect = 0; // default not in rectangle
	if((x>=x_left)&&(x<x_right)&&(y>=y_top)&&(y<y_bottom)) IsInRect = 1;
	return IsInRect;
}

// update mode based on which key is pressed
void WhichKeyIsPressed(uint16_t x, uint16_t y) {
	int i;
	for (i=0;i<5;i++) {
		// Key i is pressed
		if (inrect(x, y, 96*i, 96*i+95, 136, 271)) mode = i;
	}
}

// update values based on press in top half of screen
void CheckUpperPress(uint16_t x, uint16_t y) {
	uint16_t distSq;
	// Check if in circle
	if (inrect(x, y, 28, 68, 48, 88) && !(LastPress)) {
		distSq = (x - 48)*(x - 48) + (y - 68)*(y - 68);
		if (distSq <= 400) {
			if (CircleOn) CircleOn = 0;
			else CircleOn = 1;
			ResetScreen();
		}
		// Note that CircleOn does not control any synth function yet
	}
	// Check if up button pressed
	if (inrect(x, y, 210, 235, 100, 125) && !(LastPress)) {
		if (UpDownState < UpDownStateMax) {
			UpDownState++;
			ResetScreen();
		}
		// Note that UpDownState does not control any synth function yet
	}
	// Check if down button pressed
	if (inrect(x, y, 245, 270, 100, 125) && !(LastPress)) {
		if (UpDownState > 0) {
			UpDownState--;
			ResetScreen();
		}
	}
	// Check if slider pressed
	if (inrect(x, y, 422, 442, 20, 100)) {
		sliderPos = y;
		amplitude = amplitudeMax*(100-sliderPos)/80.0;
		ResetScreen();
	}
}

// triangle wave - CUT FOR STUDENT VERSION
float32_t trianglewave(float32_t amplitude, float32_t theta) {
	float32_t result = 0;
	if (fabsf(theta) <= PI/2.0) result = 2.0*amplitude*theta/PI;
	else if (theta < -PI/2.0) result = -2.0*amplitude*(1+theta/PI);
	else if (theta > PI/2.0) result = 2.0*amplitude*(1-theta/PI);
	return result;
}

// this function processes one DMA transfer block worth of data
void process_buffer(void) {
	int i;
  	int16_t *rx_buf, *tx_buf;
	float32_t yn;
	
	if (rx_buffer_proc == PING) {rx_buf = (int16_t *)PING_IN;}
	else {rx_buf = (int16_t *)PONG_IN;}
	if (tx_buffer_proc == PING) {tx_buf = (int16_t *)PING_OUT;}
	else {tx_buf = (int16_t *)PONG_OUT;}
		
	for (i=0 ; i<PING_PONG_BUFFER_SIZE ; i++) {
		// output one of the following based on which key is pressed
		if (TSPressed && (mode<5)) {
			switch(mode) {
				case 0:		// sawtooth
					yn = 0;		// This value needs to be changed
					break;
				case 1:		// triangle (function defined above)
					yn = trianglewave(amplitude, theta);
					break;
				case 2:		// square
					yn = 0;		// This value needs to be changed
					break;
				case 3:		// sin
					yn = 0;		// This value needs to be changed
					break;
				case 4:		// prbs (noise)
					yn = amplitude*prbs(1);		// Don't change this
					break;
			}
			// Output synth sound to next two output samples (left and right)
			*tx_buf++ = (short)yn;
			*tx_buf++ = (short)yn;
		} else {
			// Output next two input samples to next two output samples (loop through audio)
			*tx_buf++ = *rx_buf++;
			*tx_buf++ = *rx_buf++;
		}
		// update theta according to theta increment for current mode
		theta += thetaIncr[mode];
		if (theta>PI) theta -= 2.0*PI;
		else if (theta<-PI) theta += 2.0*PI;
	}

	RX_buffer_full = 0;
	TX_buffer_empty = 0;

}

int main(void)
{
	// compute frequencies for each mode (key press)
	for (j=0;j<5;j++) thetaIncr[j] = 2*PI*freq[j]/sampleFreq;
	
  	stm32f7_wm8994_init(AUDIO_FREQUENCY_8K,
						IO_METHOD_DMA,
						INPUT_DEVICE_DIGITAL_MICROPHONE_2,
						OUTPUT_DEVICE_HEADPHONE,
						WM8994_HP_OUT_ANALOG_GAIN_0DB,
						WM8994_LINE_IN_GAIN_0DB,
						WM8994_DMIC_GAIN_9DB,
						SOURCE_FILE_NAME,
						NOGRAPH);
	
	volatile uint8_t ts_status = BSP_TS_Init(480, 272);
	if (ts_status != TS_OK) {
		// Initialization failed � handle error
	}
	
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
	BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
	ResetScreen();

  while(1)
  {
    while(!(RX_buffer_full && TX_buffer_empty)){}
		BSP_LED_On(LED1);		// for timing purposes
    	process_buffer();
		BSP_LED_Off(LED1);	// measures duration of process_buffer()
		// Poll touchscreen
		BSP_TS_GetState(&TS_State);
		// Currently only tracks one touch screen press
		if (TS_State.touchDetected) {
			TSPressed = 1;
			x = TS_State.touchX[0];
			y = TS_State.touchY[0];
			// Check whether touch is on a key (in lower half)
			if(inrect(x,y,0,480,136,272)) {
				WhichKeyIsPressed(x,y);
			// If in upper half, see what needs to be changed
			} else if (inrect(x,y,0,480,0,135)) {
				mode = 255;
				CheckUpperPress(x,y);
			}
		} else TSPressed = 0;
		LastPress = TSPressed;		// keep track of previous press state
	}
}