#include "scs_port_stm32_hal_hw_uart.h"

#if CONFIG_BSP_USE_CMSIS_RTOS2
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"
#endif

extern UART_HandleTypeDef huart6; // 8n1 500000 baud

void ftUart_Send(uint8_t *nDat, int nLen)
{
  HAL_UART_Transmit(&huart6, nDat, nLen, HAL_MAX_DELAY);
}

int ftUart_Read(uint8_t *nDat, int nLen)
{
  // HAL_UART_Receive(&huart6, nDat, nLen, HAL_MAX_DELAY);
  uint16_t rxLen = 0;
  HAL_UARTEx_ReceiveToIdle(&huart6, nDat, nLen, &rxLen, HAL_MAX_DELAY);
  return rxLen; // Return the number of bytes read
}

void ftBus_Delay(void)
{
  #if CONFIG_BSP_USE_CMSIS_RTOS2
  osDelay(1); // Delay for 1 millisecond using CMSIS-RTOS2
  #else
  HAL_Delay(1); // Delay for 1 millisecond using HAL
  #endif
}