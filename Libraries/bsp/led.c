#include "main.h"
#include "gpio.h"

#include "led.h"

#ifdef USE_FREERTOS
#include "cmsis_os2.h"
#endif

void led_ctrl(led_index led, led_state state)
{
  switch (led)
  {
    case LED1:
      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, (GPIO_PinState)state);
      break;
    case LED2:
      HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, (GPIO_PinState)state);
      break;
    case LED3:
      HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, (GPIO_PinState)state);
      break;
    case LED4:
      HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, (GPIO_PinState)state);
      break;
    case LED5:
      HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, (GPIO_PinState)state);
      break;
    case LED6:
      HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, (GPIO_PinState)state);
      break;
    case LED7:
      HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, (GPIO_PinState)state);
      break;
    case LED8:
      HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, (GPIO_PinState)state);
      break;
    case LEDR:
      HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, (GPIO_PinState)state);
      break;
    case LEDG:
      HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, (GPIO_PinState)state);
      break;
    default:
      // Invalid LED index, do nothing or handle error
      break;
  }
}

void led_test(void)
{
  for (led_index i = LED_START; i < LED_COUNT; i++)
  {
    led_ctrl(i, LED_ON);
    
#ifdef USE_FREERTOS
    osDelay(100);
#else
    HAL_Delay(100);
#endif
    led_ctrl(i, LED_OFF);
  }
}