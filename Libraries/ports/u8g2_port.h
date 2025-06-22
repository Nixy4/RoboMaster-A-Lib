#pragma once
#include "u8g2.h"

//! RTOS
#ifdef USE_FREERTOS
#include "cmsis_os2.h"
#include "freertos.h"
#include "task.h"
#define u8g2_delay_ms(x) osDelay(x)
#else
#define u8g2_delay_ms(x) HAL_Delay(x)
#endif

#ifdef __cplusplus
extern "C" {
#endif

void u8g2_init(u8g2_t* u8g2);

#ifdef __cplusplus
}
#endif