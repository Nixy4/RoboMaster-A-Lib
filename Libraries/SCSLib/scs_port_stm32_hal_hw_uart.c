#include "scs_port_stm32_hal_hw_uart.h"

#ifdef USE_FREERTOS
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"
#endif

/**
 * @param baudrate 1000000
 * @param wordLength 8
 * @param stopBits 1
 * @param parity none
 * @param mode tx/rx
 * @param hwFlowCtl none
 */
extern UART_HandleTypeDef huart6;

void ftUart_Send(uint8_t *nDat, int nLen)
{
#ifdef USE_FREERTOS
  taskENTER_CRITICAL();
  HAL_UART_Transmit(&huart6, nDat, nLen, 100);
  taskEXIT_CRITICAL();
#else
  HAL_UART_Transmit(&huart6, nDat, nLen, HAL_MAX_DELAY);
#endif
}

int ftUart_Read(uint8_t *nDat, int nLen)
{
  uint16_t rxLen = 0;
#ifdef USE_FREERTOS
  taskENTER_CRITICAL();
  HAL_UARTEx_ReceiveToIdle(&huart6, nDat, nLen, &rxLen, 100);
  taskEXIT_CRITICAL();
#else
  HAL_UARTEx_ReceiveToIdle(&huart6, nDat, nLen, &rxLen, 100);
#endif
  return rxLen;
}

void ftBus_Delay(void)
{
#ifdef USE_FREERTOS
  osDelay(1);
#else
  HAL_Delay(1);
#endif
}