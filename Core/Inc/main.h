/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI1_DC_Pin GPIO_PIN_9
#define SPI1_DC_GPIO_Port GPIOB
#define PWMY_Pin GPIO_PIN_7
#define PWMY_GPIO_Port GPIOI
#define PWMX_Pin GPIO_PIN_6
#define PWMX_GPIO_Port GPIOI
#define PWMW_Pin GPIO_PIN_5
#define PWMW_GPIO_Port GPIOI
#define PWMZ_Pin GPIO_PIN_2
#define PWMZ_GPIO_Port GPIOI
#define PWMH_Pin GPIO_PIN_0
#define PWMH_GPIO_Port GPIOI
#define LED8_Pin GPIO_PIN_8
#define LED8_GPIO_Port GPIOG
#define LED7_Pin GPIO_PIN_7
#define LED7_GPIO_Port GPIOG
#define LED6_Pin GPIO_PIN_6
#define LED6_GPIO_Port GPIOG
#define PWMG_Pin GPIO_PIN_12
#define PWMG_GPIO_Port GPIOH
#define LED5_Pin GPIO_PIN_5
#define LED5_GPIO_Port GPIOG
#define LED4_Pin GPIO_PIN_4
#define LED4_GPIO_Port GPIOG
#define LED3_Pin GPIO_PIN_3
#define LED3_GPIO_Port GPIOG
#define PWMF_Pin GPIO_PIN_11
#define PWMF_GPIO_Port GPIOH
#define PWME_Pin GPIO_PIN_10
#define PWME_GPIO_Port GPIOH
#define PWMD_Pin GPIO_PIN_15
#define PWMD_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_2
#define LED2_GPIO_Port GPIOG
#define LED1_Pin GPIO_PIN_1
#define LED1_GPIO_Port GPIOG
#define PWMC_Pin GPIO_PIN_14
#define PWMC_GPIO_Port GPIOD
#define PWMB_Pin GPIO_PIN_13
#define PWMB_GPIO_Port GPIOD
#define PWMT_Pin GPIO_PIN_1
#define PWMT_GPIO_Port GPIOA
#define PWMS_Pin GPIO_PIN_0
#define PWMS_GPIO_Port GPIOA
#define PWMA_Pin GPIO_PIN_12
#define PWMA_GPIO_Port GPIOD
#define PWMU_Pin GPIO_PIN_2
#define PWMU_GPIO_Port GPIOA
#define OLED_KEY_ADC_CH_Pin GPIO_PIN_6
#define OLED_KEY_ADC_CH_GPIO_Port GPIOA
#define LEDR_Pin GPIO_PIN_11
#define LEDR_GPIO_Port GPIOE
#define PWMV_Pin GPIO_PIN_3
#define PWMV_GPIO_Port GPIOA
#define LEDG_Pin GPIO_PIN_14
#define LEDG_GPIO_Port GPIOF
#define SPI1_RST_Pin GPIO_PIN_10
#define SPI1_RST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
