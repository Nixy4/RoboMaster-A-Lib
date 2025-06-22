#pragma once

#ifdef USE_HAL_DRIVER
#include "stm32f4xx_hal.h"
#endif

#ifdef USE_LL_DRIVER
#include "stm32f4xx_ll.h"
#endif

#include "stdint.h"

#define CONFIG_BSP_USE_CMSIS_RTOS2 1