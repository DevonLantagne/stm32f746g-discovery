// stm32f7_loop_buf_dma.c
//
// For more information on how the DMA and buffers work, see /docs/stm32f7_loop_buf_dma.md

#include "stm32f7_wm8994_init.h"
#include "stm32f7_display.h"

#define SOURCE_FILE_NAME "stm32f7_loop_buf_dma.c"

#define BUFFER_SIZE PING_PONG_BUFFER_SIZE

extern volatile int32_t TX_buffer_empty;        // these may not need to be int32_t
extern volatile int32_t RX_buffer_full;         // they were extern volatile int16_t in F4 version
extern int16_t rx_buffer_proc, tx_buffer_proc;  // will be assigned token values PING or PONG

// Display Buffers
float32_t rbuffer[BUFFER_SIZE];
int16_t rbufptr = 0;
float32_t lbuffer[BUFFER_SIZE];
int16_t lbufptr = 0;

// this function processes one DMA transfer block worth of data
void process_buffer(void) 
{
  int i;
  int16_t left, right;
  int16_t *rx_buf, *tx_buf;
	
  // Select the appropriate ping pong buffer
  if (rx_buffer_proc == PING) {rx_buf = (int16_t *)PING_IN;}
  else {rx_buf = (int16_t *)PONG_IN;}
  if (tx_buffer_proc == PING) {tx_buf = (int16_t *)PING_OUT;}
  else {tx_buf = (int16_t *)PONG_OUT;}

  // Invalidate cached data now that it was been written to
  SCB_InvalidateDCache_by_Addr(
      (uint32_t *)rx_buf,
      PING_PONG_BUFFER_SIZE * 4
  );
	
  for (i=0 ; i<(PING_PONG_BUFFER_SIZE) ; i++)
  {
    // Extract L and R samples from input buffer to local space
    left = *rx_buf++;
    right = *rx_buf++;
    // Copy samples to output buffer
    *tx_buf++ = left;
    *tx_buf++ = right;
    // Transfer local samples to display buffers
    lbuffer[lbufptr] = (float32_t)left;
    rbuffer[rbufptr] = (float32_t)right;
    // Range check display buffer pointers
    lbufptr = (lbufptr + 1) % BUFFER_SIZE;
    rbufptr = (rbufptr + 1) % BUFFER_SIZE;
  }

  // CPU has written to buffer, invalidate cache
  SCB_CleanDCache_by_Addr(
      (uint32_t *)tx_buf - (PING_PONG_BUFFER_SIZE * 2),
      PING_PONG_BUFFER_SIZE * 4
  );

  plotWaveNoAutoScale(rbuffer, 128);      // plot the right channel samples
  RX_buffer_full = 0;                     // Release the buffers
  TX_buffer_empty = 0;
}

int main(void)
{  
  stm32f7_wm8994_init(AUDIO_FREQUENCY_8K,
                      IO_METHOD_DMA,
                      INPUT_DEVICE_INPUT_LINE_1,
                      OUTPUT_DEVICE_HEADPHONE,
                      WM8994_HP_OUT_ANALOG_GAIN_0DB,
                      WM8994_LINE_IN_GAIN_0DB,
                      WM8994_DMIC_GAIN_0DB,
                      SOURCE_FILE_NAME,
                      GRAPH);
  
  while(1)
  {
    while(!(RX_buffer_full && TX_buffer_empty)){}
    process_buffer();
  }
}

