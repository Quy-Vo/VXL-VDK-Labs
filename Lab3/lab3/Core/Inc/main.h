/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f1xx_hal.h"

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
#define seg0_Pin GPIO_PIN_0
#define seg0_GPIO_Port GPIOA
#define seg1_Pin GPIO_PIN_1
#define seg1_GPIO_Port GPIOA
#define seg2_Pin GPIO_PIN_2
#define seg2_GPIO_Port GPIOA
#define seg3_Pin GPIO_PIN_3
#define seg3_GPIO_Port GPIOA
#define seg4_Pin GPIO_PIN_4
#define seg4_GPIO_Port GPIOA
#define seg5_Pin GPIO_PIN_5
#define seg5_GPIO_Port GPIOA
#define seg6_Pin GPIO_PIN_6
#define seg6_GPIO_Port GPIOA
#define seg7_Pin GPIO_PIN_7
#define seg7_GPIO_Port GPIOA
#define r0_Pin GPIO_PIN_0
#define r0_GPIO_Port GPIOB
#define y0_Pin GPIO_PIN_1
#define y0_GPIO_Port GPIOB
#define g0_Pin GPIO_PIN_2
#define g0_GPIO_Port GPIOB
#define btn2_Pin GPIO_PIN_10
#define btn2_GPIO_Port GPIOB
#define btn3_Pin GPIO_PIN_11
#define btn3_GPIO_Port GPIOB
#define en0_Pin GPIO_PIN_8
#define en0_GPIO_Port GPIOA
#define en1_Pin GPIO_PIN_9
#define en1_GPIO_Port GPIOA
#define en2_Pin GPIO_PIN_10
#define en2_GPIO_Port GPIOA
#define en3_Pin GPIO_PIN_11
#define en3_GPIO_Port GPIOA
#define status_Pin GPIO_PIN_12
#define status_GPIO_Port GPIOA
#define r1_Pin GPIO_PIN_3
#define r1_GPIO_Port GPIOB
#define y1_Pin GPIO_PIN_4
#define y1_GPIO_Port GPIOB
#define g1_Pin GPIO_PIN_5
#define g1_GPIO_Port GPIOB
#define en4_Pin GPIO_PIN_6
#define en4_GPIO_Port GPIOB
#define en5_Pin GPIO_PIN_7
#define en5_GPIO_Port GPIOB
#define btn0_Pin GPIO_PIN_8
#define btn0_GPIO_Port GPIOB
#define btn1_Pin GPIO_PIN_9
#define btn1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
