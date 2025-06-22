#pragma once


#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum led_index
{
  LED_START = 0,
  LED1 = LED_START,
  LED2,
  LED3,
  LED4,
  LED5,
  LED6,
  LED7,
  LED8,
  LEDR,
  LEDG,
  LED_END = LEDG,
  LED_COUNT,
} led_index;

typedef enum led_state
{
  LED_ON = GPIO_PIN_RESET,
  LED_OFF = GPIO_PIN_SET,
} led_state;

void led_ctrl(led_index led, led_state state);
void led_test(void);

#ifdef __cplusplus
}
#endif