// stm32f7_loop_intr.c
// Jay's Lab

#include "stm32f7_wm8994_init.h"
#include "stm32f7_display.h"

#define SOURCE_FILE_NAME "stm32f7_loop_intr.c"
#define N 16384
#define sampleFreq 48000.0

extern int16_t rx_sample_L;
extern int16_t rx_sample_R;
extern int16_t tx_sample_L;
extern int16_t tx_sample_R;

uint8_t displayOn = 1;							// 0 = off, 1 = on
	
void BSP_AUDIO_SAI_Interrupt_CallBack()
{
// when we arrive at this interrupt service routine (callback)
// the most recent input sample values are (already) in global variables
// rx_sample_L and rx_sample_R

	static float32_t xMS = 0;					// mean square value for input sequence
	static float32_t yMS = 0;					// mean square value for output sequence
	static float32_t xZC = 0;					// current zero crossing for input
	static float32_t yZC = 0;					// current zero crossing for output
	static float32_t xZCOld[10] = {0};// past zero crossings for input
	static float32_t xbuff[N] = {0};	// circular buffer for input
	static float32_t ybuff[N] = {0};	// circular buffer for output
	static uint16_t ptr = 0;					// current time index (modulo N)
	static float32_t Gain = 0;				// for gain computation
	static float32_t GdB = 0;					// gain in decibels
	static float32_t Phase = 0;				// for phase computation
	static float32_t Delta_n = 0;			// estimate of time difference between x and y
	static float32_t Delta_N = 0;			// estimate of signal period
	static float32_t Freq = 0;				// frequency estimate
	static float32_t xOldN, yOldN = 0;	// x[n-N], y[n-N]
	static float32_t xOld1, yOld1 = 0;	// x[n-1], y[n-1]
	static float32_t xOld2, yOld2 = 0;	// x[n-2], y[n-2] EXTRA
	float32_t xn, yn;										// x[n], y[n]
	
	xn = (float32_t)rx_sample_L;	// current input x[n] = left channel input
	yn = (float32_t)rx_sample_L;	// current output y[n] = x[n] (loop system)
	
	// CUT FOLLOWING LINES IF GIVING THIS CODE TO STUDENTS
	// yn = (xn+xOld2)/2.0;					  // y[n] = (x[n]+x[n-2])/2
	yn = xOld1;										// y[n] = x[n-1]
	// yn = (xn + xOld1 + xOld2)/3.0;	// 3-pt averaging filter
	// yn = xn + xOld2 - 0.9801*yOld2;		// notch filter with notch at fs/4
	// END CUT LINES HERE
	
	// The following code assumes that a sinusoid has been applied as the left channel input.
	// It computes the gain between the output and input signals using mean square values,
	// It also computes the frequency by using zero crossing data to estimate the period.
	// It also computes the phase difference between the input and output signals based on zero crossing data.
	
	// Get values from buffer
	xOldN = xbuff[ptr];						// get x[n-N]
	yOldN = ybuff[ptr];						// get y[n-N]
	// Put new values in buffer
	xbuff[ptr] = xn;							// write x[n] to replace x[n-N]
	ybuff[ptr] = yn;							// write y[n] to replace y[n-N]
	// Update mean square values for input and output signals
	xMS += xn*xn - xOldN*xOldN;		// update the mean square estimate for the input signal
	yMS += yn*yn - yOldN*yOldN;		// same, but for the output signal
	// Zero crossing, period, and phase calculations
	if ((xn>0) && (xOld1<0)) {
		int i;
		// update past ZC locations
		float32_t xZCOld10 = xZCOld[9];
		for (i=9; i>0; i--) xZCOld[i] = xZCOld[i-1];
		xZC = (float)ptr - xn/(xn-xOld1);		// compute new ZC using interpolation
		xZCOld[0] = xZC;										// assign new ZC estimate to buffer
		float ZCdiff = xZC - xZCOld10;			// difference between current ZC and 10 ZCs ago
		while (ZCdiff < 0) ZCdiff += N;			// in case ptr returned to zero between ZCs
		Delta_N = 0.1f*ZCdiff;							// compute period estimate from averaging over last ten ZCs
		Freq = sampleFreq/Delta_N;					// compute frequency estimate
	}
	if ((yn>0) && (yOld1<0)) {
		yZC = (float)ptr - yn/(yn-yOld1);		// compute new ZC using interpolation
		Delta_n = xZC - yZC;								// compute time difference between input and output
		if(Delta_n > (float)N/2) Delta_n -= N;
		Phase = 360.0*Delta_n/Delta_N;			// compute phase difference in degrees
	}
	// Print values if ptr == 0
	char text[20];
	if (ptr==0 && displayOn) {
		snprintf((char *)text, sizeof(text), "Freq:%7.1f Hz", Freq);
		BSP_LCD_DisplayStringAt(80, 200, (uint8_t *)text, LEFT_MODE);
		Gain = sqrt(yMS/xMS);								// sqrt is computationally expensive; do only as needed
		if (Gain>0) GdB = 20*log10(Gain);		// similarly log10...
		else GdB = -999.9;									// outlying value in case Gain < 0
		if (fabs(GdB) < 999.99) {
			snprintf((char *)text, sizeof(text), "Gain:%7.2f dB", GdB);
			BSP_LCD_DisplayStringAt(80, 220, (uint8_t *)text, LEFT_MODE);
		}
		if (fabs(Phase) < 999.9) {
			snprintf((char *)text, sizeof(text), "Phase:%6.1f deg", Phase);
			BSP_LCD_DisplayStringAt(80, 240, (uint8_t *)text, LEFT_MODE);
		}
	}
	// Update immediate past values for next time and increment pointer
	xOld2 = xOld1;			// EXTRA: next x[n-2] = current x[n-1]
	xOld1 = xn;					// next x[n-1] = current x[n]
	yOld2 = yOld1;			// EXTRA: next x[n-2] = current x[n-1]
	yOld1 = yn;					// next y[n-1] = current y[n]
	ptr = (ptr+1)%N;		// increment ptr by 1 (modulo the buffer length N)
	
  tx_sample_L = (int16_t)xn;	// left channel output = x[n] 
  tx_sample_R = (int16_t)yn;	// right channel output = y[n]
  BSP_LED_Toggle(LED1);				// for timing purposes
  return;
}

int main(void)
{  
  
  stm32f7_wm8994_init(AUDIO_FREQUENCY_48K,
                      IO_METHOD_INTR,
                      INPUT_DEVICE_INPUT_LINE_1,  // change to INPUT_DEVICE_DIGITAL_MICROPHONE_2 as needed
                      OUTPUT_DEVICE_HEADPHONE,
                      WM8994_HP_OUT_ANALOG_GAIN_0DB,
                      WM8994_LINE_IN_GAIN_0DB,
                      WM8994_DMIC_GAIN_17DB,
                      SOURCE_FILE_NAME,
                      NOGRAPH);
	
  while(1){}
}

