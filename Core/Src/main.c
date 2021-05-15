/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"

#include "wizchip_conf.h"
#include "W5300BasicFunctions.h"

#include "socket.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DATA_BUF_SIZE		2048
#define DEBUG_BUF_SIZE		DATA_BUF_SIZE + 20
#define PRINTF_BUF_SIZE		1024
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_uart4_tx;
DMA_HandleTypeDef hdma_uart4_rx;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart3_tx;
DMA_HandleTypeDef hdma_usart3_rx;

SRAM_HandleTypeDef hsram3;

/* USER CODE BEGIN PV */
wiz_NetInfo gWIZNETINFO = {
		.mac = {0x00, 0x08, 0xdc, 0xff, 0xff, 0xff},
		.ip = {192, 168, 0, 60},
		.sn = {255, 255, 255, 0},
		.gw = {192, 168, 0, 1},
		.dns = {168, 126, 63, 1},
		.dhcp = NETINFO_DHCP
};

uint8_t debugBuf[DEBUG_BUF_SIZE];
uint16_t debugWrite = 0;
uint16_t debugRead = 0;
uint8_t uart5TxBuf[DEBUG_BUF_SIZE];
uint16_t uart5TxLen = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_UART4_Init(void);
static void MX_UART5_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_FSMC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
//	for(i=0; i<len; i++)
//		ITM_SendChar((*ptr++));
//	HAL_UART_Transmit(&huart5, (uint8_t *)ptr, len, 10);
//	HAL_UART_Transmit_IT(&huart5, (uint8_t *)ptr, len);
	for(int i=0; i<len; i++)
	{
		debugBuf[debugWrite++] = ptr[i];
		if(debugWrite >= DEBUG_BUF_SIZE)
			debugWrite = 0;
	}

	return len;
}

uint8_t count = 0;
uint16_t ms_count = 0;
uint8_t onesecondElapsed = 0;
uint8_t intervalElapsed = 0;

uint8_t msg[200];
uint16_t retval;

#define MAX_RX_BUF 	512

#define ARRAY_LEN(x)	(sizeof(x) / sizeof((x)[0]))


uint16_t sentbytes = 0;


uint8_t W5300_memsize[2][8] = {{8,8,8,8,8,8,8,8}, {8,8,8,8,8,8,8,8}};
//uint8_t W5300_memsize[2][8] = {{4,4,4,4,4,4,4,4}, {4,4,4,4,4,4,4,4}};


//DMA 처리를 위한 송수신 버퍼
uint8_t DMATxBuf[4][DATA_BUF_SIZE] = {0,};
uint8_t DMARxBuf[4][DATA_BUF_SIZE] = {0,};

uint8_t RxBuf[4][DATA_BUF_SIZE] = {0,};

//UART
uint8_t UartTxEnable[4] = {1, 1, 1, 1};
uint8_t UartRxEnable[4] = {0, 0, 0, 0};

uint8_t DMATxStart[4] = {0, 0, 0, 0};

uint16_t ethDataLen3 = 0;
uint16_t ethDataLen4 = 0;

uint16_t _TX_Count[4] = {0,};
uint16_t _HT_Count[4] = {0,};
uint16_t _TC_Count[4] = {0,};
uint16_t _IDLE_Count[4] = {0,};

uint32_t totalSentBytes[4] = {0,};
uint32_t totalRcvdBytes[4] = {0,};

uint16_t wrPtr[4] = {0,};
uint16_t rdPtr[4] = {0,};
uint16_t rcvdLen[4] = {0,};
uint8_t rcvFlag[4] = {0,};

uint8_t ch;

#define BAUDRATE		2000000


#define _LOOPBACK_DEBUG_
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  uint8_t tmpaddr[6];

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_FSMC_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  Reset_W5300();

  reg_wizchip_bus_cbfunc(W5300_read, W5300_write);

  printf("GetMR()=%04X\r\n", getMR());

//  getSHAR(tmpaddr);
//  printf("SHAR=%02X:%02X:%02X:%02X:%02X:%02X\r\n", tmpaddr[0], tmpaddr[1], tmpaddr[2], tmpaddr[3], tmpaddr[4], tmpaddr[5]);
//  getSIPR(tmpaddr);
//  printf("SIPR=%d.%d.%d.%d\r\n", tmpaddr[0], tmpaddr[1], tmpaddr[2], tmpaddr[3]);
//  getGAR(tmpaddr);
//  printf("SIPR=%d.%d.%d.%d\r\n", tmpaddr[0], tmpaddr[1], tmpaddr[2], tmpaddr[3]);
//  getSUBR(tmpaddr);
//  printf("SUBR=%d.%d.%d.%d\r\n", tmpaddr[0], tmpaddr[1], tmpaddr[2], tmpaddr[3]);
//
//  setSHAR(gWIZNETINFO.mac);
//  setSIPR(gWIZNETINFO.ip);
//  setGAR(gWIZNETINFO.gw);
//  setSUBR(gWIZNETINFO.sn);

  W5300Initialize(W5300_memsize);
  printf("GetTMS01R()\%04X\r\n", getTMS01R());
  printf("GetTMS23R()\%04X\r\n", getTMS23R());
  printf("GetTMS45R()\%04X\r\n", getTMS45R());
  printf("GetTMS67R()\%04X\r\n", getTMS67R());
  printf("GetRMS01R()\%04X\r\n", getRMS01R());
  printf("GetRMS23R()\%04X\r\n", getRMS23R());
  printf("GetRMS45R()\%04X\r\n", getRMS45R());
  printf("GetRMS67R()\%04X\r\n", getRMS67R());

  ctlnetwork(CN_SET_NETINFO, (void *)&gWIZNETINFO);
  print_network_information();

//  memset(tmpbuf, 0, MAX_RX_BUF);
//  HAL_UART_Receive_DMA(&huart1, &rxByte1, 1);
//  HAL_UART_Receive_DMA(&huart2, &rxByte2, 1);

//  __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
//  HAL_UART_Receive_DMA(&huart1, DMARxBuf[0], DATA_BUF_SIZE);

  __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
  HAL_UART_Receive_DMA(&huart2, DMARxBuf[1], DATA_BUF_SIZE);

  __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
  HAL_UART_Receive_DMA(&huart3, DMARxBuf[2], DATA_BUF_SIZE);

  __HAL_UART_ENABLE_IT(&huart4, UART_IT_IDLE);
  HAL_UART_Receive_DMA(&huart4, DMARxBuf[3], DATA_BUF_SIZE);


  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(onesecondElapsed)
	  {
		  onesecondElapsed = 0;
		  count++;	// increment count
		  HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);

	  }

	  if(intervalElapsed)
	  {
		  intervalElapsed = 0;

		  for(ch=0; ch<4; ch++)
		  {
			  if(UartTxEnable[ch])
				  DMATxStart[ch] = 1;
//			  printf("CH[%d] UartTxEnable: %d, DMATxStart: %d\r\n",
//					  ch, UartTxEnable[ch], DMATxStart[ch]);
		  }
	  }

//	  DMALoopback(1);
//	  DMALoopback(2);
//	  DMALoopback(3);
	  U2E_tcps(1, 5000);
	  U2E_tcps(2, 5001);
	  U2E_tcps(3, 5002);


	  if(HAL_UART_GetState(&huart5) == HAL_UART_STATE_READY)
	  {
		  if(debugWrite != debugRead)
		  {
			  if(debugWrite > debugRead)
			  {
				  uart5TxLen = debugWrite - debugRead;
				  memcpy(uart5TxBuf, debugBuf + debugRead, uart5TxLen);
				  debugRead = debugWrite;
			  }else
			  {
				  uart5TxLen = DEBUG_BUF_SIZE - debugRead;
				  memcpy(uart5TxBuf, debugBuf + debugRead, uart5TxLen);
				  memcpy(uart5TxBuf + uart5TxLen, debugBuf, debugWrite);
				  uart5TxLen += debugWrite;
				  debugRead = debugWrite;
			  }
			  HAL_UART_Transmit_IT(&huart5, uart5TxBuf, uart5TxLen);
		  }
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 1000;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 72;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 2000000;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 2000000;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 2000000;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 2000000;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 2000000;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
  /* DMA1_Channel7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
  /* DMA2_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Channel3_IRQn);
  /* DMA2_Channel4_5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Channel4_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Channel4_5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC0 PC1 PC2
                           PC3 PC8 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2
                          |GPIO_PIN_3|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PF6 PF7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PC4 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB13 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB14 PB5 PB6 PB7
                           PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* FSMC initialization function */
static void MX_FSMC_Init(void)
{

  /* USER CODE BEGIN FSMC_Init 0 */

  /* USER CODE END FSMC_Init 0 */

  FSMC_NORSRAM_TimingTypeDef Timing = {0};

  /* USER CODE BEGIN FSMC_Init 1 */

  /* USER CODE END FSMC_Init 1 */

  /** Perform the SRAM3 memory initialization sequence
  */
  hsram3.Instance = FSMC_NORSRAM_DEVICE;
  hsram3.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram3.Init */
  hsram3.Init.NSBank = FSMC_NORSRAM_BANK3;
  hsram3.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram3.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  hsram3.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram3.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram3.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram3.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  hsram3.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram3.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  hsram3.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  hsram3.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  hsram3.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram3.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
  /* Timing */
  Timing.AddressSetupTime = 0;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 3;
  Timing.BusTurnAroundDuration = 0;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&hsram3, &Timing, NULL) != HAL_OK)
  {
    Error_Handler( );
  }

  /** Disconnect NADV
  */

  __HAL_AFIO_FSMCNADV_DISCONNECTED();

  /* USER CODE BEGIN FSMC_Init 2 */

  /* USER CODE END FSMC_Init 2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == htim2.Instance)
	{
		ms_count++;

		if((ms_count % 10) == 0) intervalElapsed = 1;

		if(ms_count >= 1000)
		{
			onesecondElapsed = 1;
			ms_count = 0;
		}

		/* Toggle LEDs */
	}
}

void UART_Data_Process(UART_HandleTypeDef *huart)
{
	uint8_t ch;

	if(huart->Instance == huart1.Instance)
	{
		ch = 0;
		printf("CH%d selected in UART_DATA_Process\r\n", ch);
	}
	else if(huart->Instance == huart2.Instance)
	{
		ch = 1;
		printf("CH%d selected in UART_DATA_Process\r\n", ch);	}
	else if(huart->Instance == huart3.Instance)
	{
		ch = 2;
		printf("CH%d selected in UART_DATA_Process\r\n", ch);	}
	else if(huart->Instance == huart4.Instance)
	{
		ch = 3;
		printf("CH%d selected in UART_DATA_Process\r\n", ch);	}

//	printf("UART_Data_Process was called with %d\r\n", ch);

	wrPtr[ch] = DATA_BUF_SIZE - huart->hdmarx->Instance->CNDTR;

	rcvdLen[ch] = 0;

	if(wrPtr[ch] != rdPtr[ch])
	{
		memset(RxBuf[ch], 0, DATA_BUF_SIZE);

		if (wrPtr[ch] > rdPtr[ch])
		{
			rcvdLen[ch] = wrPtr[ch] - rdPtr[ch];
			memcpy(RxBuf[ch], DMARxBuf[ch] + rdPtr[ch], rcvdLen[ch]);
		}else
		{
			rcvdLen[ch] = DATA_BUF_SIZE - rdPtr[ch];
			memcpy(RxBuf[ch], DMARxBuf[ch] + rdPtr[ch], rcvdLen[ch]);
			if(wrPtr[ch] > 0)
			{
				memcpy(RxBuf[ch] + rcvdLen[ch], DMARxBuf[ch], wrPtr[ch]);
				rcvdLen[ch] += wrPtr[ch];
			}
		}
		rdPtr[ch] = wrPtr[ch];
	}

	totalRcvdBytes[ch] += rcvdLen[ch];
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t ch;

	if(huart->Instance == huart1.Instance) ch = 0;
	else if(huart->Instance == huart2.Instance) ch = 1;
	else if(huart->Instance == huart3.Instance) ch = 2;
	else if(huart->Instance == huart4.Instance) ch = 3;

	_TC_Count[ch]++;

//	printf("CH[%d] _TX_Count: %d, _HT_Count: %d, _TC_Count: %d, _IDLE_Count: %d, rdPtr: %d, wrPtr: %d, rcvdLen: %d, totalSentBytes: %d, totalRcvdBytes: %d\r\n",
//		  ch, _TX_Count[ch], _HT_Count[ch], _TC_Count[ch], _IDLE_Count[ch], rdPtr[ch], wrPtr[ch], rcvdLen[ch], totalSentBytes[ch], totalRcvdBytes[ch]);

//	UART_Data_Process(huart);

	if(rcvFlag[ch] == 0) rcvFlag[ch] = 1;
}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t ch;

	if(huart->Instance == huart1.Instance) ch = 0;
	else if(huart->Instance == huart2.Instance) ch = 1;
	else if(huart->Instance == huart3.Instance) ch = 2;
	else if(huart->Instance == huart4.Instance) ch = 3;

	_HT_Count[ch]++;

//	printf("CH[%d] _TX_Count: %d, _HT_Count: %d, _TC_Count: %d, _IDLE_Count: %d, rdPtr: %d, wrPtr: %d, rcvdLen: %d, totalSentBytes: %d, totalRcvdBytes: %d\r\n",
//		  ch, _TX_Count[ch], _HT_Count[ch], _TC_Count[ch], _IDLE_Count[ch], rdPtr[ch], wrPtr[ch], rcvdLen[ch], totalSentBytes[ch], totalRcvdBytes[ch]);

//	UART_Data_Process(huart);

	if(rcvFlag[ch] == 0) rcvFlag[ch] = 1;
}


void UART_IDLECallback(UART_HandleTypeDef *huart)
{
	uint8_t ch;

	if(huart->Instance == huart1.Instance) ch = 0;
	else if(huart->Instance == huart2.Instance) ch = 1;
	else if(huart->Instance == huart3.Instance) ch = 2;
	else if(huart->Instance == huart4.Instance) ch = 3;

	_IDLE_Count[ch]++;

//	printf("CH[%d] _TX_Count: %d, _HT_Count: %d, _TC_Count: %d, _IDLE_Count: %d, rdPtr: %d, wrPtr: %d, rcvdLen: %d, totalSentBytes: %d, totalRcvdBytes: %d\r\n",
//		  ch, _TX_Count[ch], _HT_Count[ch], _TC_Count[ch], _IDLE_Count[ch], rdPtr[ch], wrPtr[ch], rcvdLen[ch], totalSentBytes[ch], totalRcvdBytes[ch]);

//	UART_Data_Process(huart);

	if(rcvFlag[ch] == 0) rcvFlag[ch] = 1;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t ch;

	if(huart->Instance == huart1.Instance) ch = 0;
	else if(huart->Instance == huart2.Instance) ch = 1;
	else if(huart->Instance == huart3.Instance) ch = 2;
	else if(huart->Instance == huart4.Instance) ch = 3;

	if(UartTxEnable[ch] == 0) UartTxEnable[ch] = 1;
//	printf("UartTxEnable[%d] was changed to %d in HAL_UART_TxCpltCallback\r\n", index, UartTxEnable[index]);
}

void print_network_information(void)
{

    wizchip_getnetinfo(&gWIZNETINFO);
    printf("Mac address: %02x:%02x:%02x:%02x:%02x:%02x\n\r",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
    printf("IP address : %d.%d.%d.%d\n\r",gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);
    printf("SM Mask    : %d.%d.%d.%d\n\r",gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
    printf("Gate way   : %d.%d.%d.%d\n\r",gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
    printf("DNS Server : %d.%d.%d.%d\n\r",gWIZNETINFO.dns[0],gWIZNETINFO.dns[1],gWIZNETINFO.dns[2],gWIZNETINFO.dns[3]);
}

UART_HandleTypeDef * gethuart(uint8_t sn)
{
	printf("ch: %d in gethuart\r\n", sn);
	if(sn == 0)
		return &huart1;
	else if(sn == 1)
		return &huart2;
	else if(sn == 2)
		return &huart3;
	else if(sn == 3)
		return &huart4;
}

void DMALoopback(uint8_t ch)
{
	UART_HandleTypeDef *huart;
	uint16_t i;

	// DMA Tx Start Flag가 set 되어 있으면 HAL_UART_Transmit_DMA를 수행한다.
	if(DMATxStart[ch])
	{
		for(i=0; i<DATA_BUF_SIZE; i++) DMATxBuf[ch][i] = '0' + (i % 10);

		HAL_UART_Transmit_DMA(gethuart(ch), DMATxBuf[ch], DATA_BUF_SIZE);
		printf("================\r\n");
		printf("UART%d HAL_UART_Transmit_DMA sent: %d bytes\r\n", (ch + 1), DATA_BUF_SIZE);
		_TX_Count[ch] += 1;
		totalSentBytes[ch] += DATA_BUF_SIZE;
		UartTxEnable[ch] = 0;
		DMATxStart[ch] = 0;
	}

	// DMA Rx Data가 있으면 User Buffer로 복사한다.
	if(rcvFlag[ch])
	{
//		huart = gethuart(ch);
		printf("ch[%d] rcvFlag: %d, %d, %d, %d\r\n", ch, rcvFlag[0], rcvFlag[1], rcvFlag[2], rcvFlag[3]);
		rcvFlag[ch] = 0;
		printf("ch[%d] rcvFlag: %d, %d, %d, %d\r\n", ch, rcvFlag[0], rcvFlag[1], rcvFlag[2], rcvFlag[3]);

		UART_Data_Process(gethuart(ch));
		printf("RxBuf[%d]:", ch);
		for(i=0; i<rcvdLen[ch]; i++)
		{
		  if((i % 100) == 0) printf("\r\n\t");
		  printf("%c", RxBuf[ch][i]);
		}
		printf("\r\n");
		printf("CH[%d] _TX_Count: %d, _HT_Count: %d, _TC_Count: %d, _IDLE_Count: %d, rdPtr: %d, wrPtr: %d, rcvdLen: %d, totalSentBytes: %d, totalRcvdBytes: %d\r\n",
			  ch, _TX_Count[ch], _HT_Count[ch], _TC_Count[ch], _IDLE_Count[ch], rdPtr[ch], wrPtr[ch], rcvdLen[ch], totalSentBytes[ch], totalRcvdBytes[ch]);
	}
}

int32_t U2E_tcps(uint8_t sn, uint16_t port)
{
//	UART_HandleTypeDef *huart;
//	huart = gethuart(sn);
   int32_t ret;
   uint16_t size = 0, sentsize=0;
   uint16_t i;

   uint8_t buf[DATA_BUF_SIZE] = {0,};

#ifdef _LOOPBACK_DEBUG_
   uint8_t destip[4];
   uint16_t destport;
#endif

   switch(getSn_SR(sn))
   {
      case SOCK_ESTABLISHED :
         if(getSn_IR(sn) & Sn_IR_CON)
         {
#ifdef _LOOPBACK_DEBUG_
			getSn_DIPR(sn, destip);
			destport = getSn_DPORT(sn);

			printf("%d:Connected - %d.%d.%d.%d : %d\r\n",sn, destip[0], destip[1], destip[2], destip[3], destport);
#endif
			setSn_IR(sn,Sn_IR_CON);
         }

//		if(DMATxStart[sn])
		if(UartTxEnable[sn])
     	{
//			printf("data to read arrived\r\n");
			if((size = getSn_RX_RSR(sn)) > 0) // Don't need to check SOCKERR_BUSY because it doesn't occur.
			{
				if(size > DATA_BUF_SIZE) size = DATA_BUF_SIZE;
				ret = recv(sn, DMATxBuf[sn], size);
				printf("rcvd bytes: %d\r\n", ret);
//				printf("\r\nrcvd data: \r\n%s\r\n\r\n", DMATxBuf[sn]);

				HAL_UART_Transmit_DMA(gethuart(sn), DMATxBuf[sn], ret);
				UartTxEnable[sn] = 0;
//				DMATxStart[sn] = 0;
				_TX_Count[sn] += 1;
				totalSentBytes[sn] += ret;
				printf("================\r\n");
				printf("UART%d HAL_UART_Transmit_DMA sent: %d bytes\r\n", (sn + 1), ret);
			}
     	}

		// DMA Rx Data가 있으면 User Buffer로 복사한다.
		if(rcvFlag[sn])
		{
	//		huart = gethuart(ch);
			printf("ch[%d] rcvFlag: %d, %d, %d, %d\r\n", sn, rcvFlag[0], rcvFlag[1], rcvFlag[2], rcvFlag[3]);
			rcvFlag[sn] = 0;
			printf("ch[%d] rcvFlag: %d, %d, %d, %d\r\n", sn, rcvFlag[0], rcvFlag[1], rcvFlag[2], rcvFlag[3]);

			UART_Data_Process(gethuart(sn));
			if(rcvdLen[sn] > 0)
			{
//				printf("\r\nRxBuf[%d] rcvdLen: %d \r\n%s\r\n", sn, rcvdLen[sn], RxBuf[sn]);
				ret = send(sn, RxBuf[sn], rcvdLen[sn]);
				printf("sent bytes: %d\r\n", ret);
			}
			printf("CH[%d] _TX_Count: %d, _HT_Count: %d, _TC_Count: %d, _IDLE_Count: %d, rdPtr: %d, wrPtr: %d, rcvdLen: %d, totalSentBytes: %d, totalRcvdBytes: %d\r\n",
					sn, _TX_Count[sn], _HT_Count[sn], _TC_Count[sn], _IDLE_Count[sn], rdPtr[sn], wrPtr[sn], rcvdLen[sn], totalSentBytes[sn], totalRcvdBytes[sn]);
		}

         break;
      case SOCK_CLOSE_WAIT :
#ifdef _LOOPBACK_DEBUG_
         //printf("%d:CloseWait\r\n",sn);
#endif
         if((ret = disconnect(sn)) != SOCK_OK) return ret;
#ifdef _LOOPBACK_DEBUG_
         printf("%d:Socket Closed\r\n", sn);
#endif
         break;
      case SOCK_INIT :
#ifdef _LOOPBACK_DEBUG_
    	 printf("%d:Listen, TCP server loopback, port [%d]\r\n", sn, port);
#endif
         if( (ret = listen(sn)) != SOCK_OK) return ret;
         break;
      case SOCK_CLOSED:
#ifdef _LOOPBACK_DEBUG_
         //printf("%d:TCP server loopback start\r\n",sn);
#endif
         if((ret = socket(sn, Sn_MR_TCP, port, 0x00)) != sn) return ret;
#ifdef _LOOPBACK_DEBUG_
         //printf("%d:Socket opened\r\n",sn);
#endif
         break;
      default:
         break;
   }
   return 1;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
