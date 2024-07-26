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
void main_function();
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Ready_button_Pin GPIO_PIN_13
#define Ready_button_GPIO_Port GPIOC
#define Motor1_Encoder_Pin GPIO_PIN_0
#define Motor1_Encoder_GPIO_Port GPIOC
#define Motor1_EncoderC1_Pin GPIO_PIN_1
#define Motor1_EncoderC1_GPIO_Port GPIOC
#define Motor2_Encoder_Pin GPIO_PIN_0
#define Motor2_Encoder_GPIO_Port GPIOA
#define Motor2_EncoderA1_Pin GPIO_PIN_1
#define Motor2_EncoderA1_GPIO_Port GPIOA
#define LPUART1_TX_Pin GPIO_PIN_2
#define LPUART1_TX_GPIO_Port GPIOA
#define LPUART1_RX_Pin GPIO_PIN_3
#define LPUART1_RX_GPIO_Port GPIOA
#define Motor3_Encoder_Pin GPIO_PIN_4
#define Motor3_Encoder_GPIO_Port GPIOA
#define Finish_LED_Pin GPIO_PIN_5
#define Finish_LED_GPIO_Port GPIOA
#define Motor3_EncoderA6_Pin GPIO_PIN_6
#define Motor3_EncoderA6_GPIO_Port GPIOA
#define TIM1_INA_Pin GPIO_PIN_6
#define TIM1_INA_GPIO_Port GPIOC
#define TIM1_INB_Pin GPIO_PIN_7
#define TIM1_INB_GPIO_Port GPIOC
#define TIM2_INa_Pin GPIO_PIN_8
#define TIM2_INa_GPIO_Port GPIOC
#define TIM2_INB_Pin GPIO_PIN_9
#define TIM2_INB_GPIO_Port GPIOC
#define TIM3_INA_Pin GPIO_PIN_8
#define TIM3_INA_GPIO_Port GPIOA
#define TIM3_INB_Pin GPIO_PIN_9
#define TIM3_INB_GPIO_Port GPIOA
#define Motor1_PWM_Pin GPIO_PIN_11
#define Motor1_PWM_GPIO_Port GPIOA
#define Motor2_PWM_Pin GPIO_PIN_12
#define Motor2_PWM_GPIO_Port GPIOA
#define T_SWDIO_Pin GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define T_SWO_Pin GPIO_PIN_3
#define T_SWO_GPIO_Port GPIOB
#define Motor3_PWM_Pin GPIO_PIN_9
#define Motor3_PWM_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
