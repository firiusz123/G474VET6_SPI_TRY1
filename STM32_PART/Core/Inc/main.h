/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Motor_A_CH1_Pin GPIO_PIN_0
#define Motor_A_CH1_GPIO_Port GPIOC
#define Motor_A_CH2_Pin GPIO_PIN_1
#define Motor_A_CH2_GPIO_Port GPIOC
#define Motor_B_CH3_Pin GPIO_PIN_2
#define Motor_B_CH3_GPIO_Port GPIOC
#define Motor_A_CH4_Pin GPIO_PIN_3
#define Motor_A_CH4_GPIO_Port GPIOC
#define Limiter_switch_j19_Pin GPIO_PIN_8
#define Limiter_switch_j19_GPIO_Port GPIOD
#define LS2_DRV1_NO_Pin GPIO_PIN_12
#define LS2_DRV1_NO_GPIO_Port GPIOD
#define LS1_DRV1_NO_Pin GPIO_PIN_14
#define LS1_DRV1_NO_GPIO_Port GPIOD
#define Motor_B_EN_CH1_Pin GPIO_PIN_6
#define Motor_B_EN_CH1_GPIO_Port GPIOC
#define Motor_B_EN_CH2_Pin GPIO_PIN_7
#define Motor_B_EN_CH2_GPIO_Port GPIOC
#define Motor_A_EN_CH2_Pin GPIO_PIN_11
#define Motor_A_EN_CH2_GPIO_Port GPIOA
#define Motor_A_EN_CH1_Pin GPIO_PIN_12
#define Motor_A_EN_CH1_GPIO_Port GPIOA
#define LS_DRV2_NO_Pin GPIO_PIN_6
#define LS_DRV2_NO_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
