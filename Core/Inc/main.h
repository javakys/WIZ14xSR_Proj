/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
void Reset_W5300(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define UART1_CTS_Pin			GPIO_PIN_11
#define UART1_CTS_GPIO_Port		GPIOA
#define UART1_RTS_Pin			GPIO_PIN_12
#define UART1_RTS_GPIO_Port		GPIOA
#define HW_TRIGGER_Pin			GPIO_PIN_0
#define HW_TRIGGER_GPIO_Port	GPIOB
#define STATUS_1_Pin				GPIO_PIN_5
#define STATUS_1_GPIO_Port		GPIOB
#define STATUS_3_Pin				GPIO_PIN_6
#define STATUS_3_GPIO_Port		GPIOB
#define STATUS_4_Pin				GPIO_PIN_7
#define STATUS_4_GPIO_Port		GPIOB
#define STATUS_5_Pin				GPIO_PIN_8
#define STATUS_5_GPIO_Port		GPIOB
#define UART3_CTS_Pin			GPIO_PIN_13
#define UART3_CTS_GPIO_Port		GPIOB
#define UART3_RTS_Pin			GPIO_PIN_14
#define UART3_RTS_GPIO_Port		GPIOB
#define INT_W5300_Pin			GPIO_PIN_0
#define INT_W5300_GPIO_Port		GPIOC
#define LINK_LED_Pin				GPIO_PIN_1
#define LINK_LED_GPIO_Port		GPIOC
#define TX_LED_Pin				GPIO_PIN_2
#define TX_LED_GPIO_Port			GPIOC
#define RX_LED_Pin				GPIO_PIN_3
#define RX_LEDG_GPIO_Port		GPIOC
#define ACT_LED_Pin				GPIO_PIN_4
#define ACT_LED_GPIO_Port		GPIOC
#define UART4_CTS_Pin			GPIO_PIN_8
#define UART4_CTS_GPIO_Port		GPIOC
#define UART4_RTS_Pin			GPIO_PIN_9
#define UART4_RTS_GPIO_Port		GPIOC
#define SW_INPUT_Pin				GPIO_PIN_13
#define SW_INPUT_GPIO_Port		GPIOC
#define RESET_W5300_Pin			GPIO_PIN_6
#define RESET_W5300_GPIO_Port	GPIOF
#define DEBUG_LED_Pin			GPIO_PIN_7
#define DEBUG_LED_GPIO_Port		GPIOF
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
