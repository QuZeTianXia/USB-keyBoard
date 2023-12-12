/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
#define KEY1_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_3
#define KEY2_GPIO_Port GPIOC
#define KEY2_Pin GPIO_PIN_13
#define KEY3_GPIO_Port GPIOB
#define KEY3_Pin GPIO_PIN_9

#define LED1_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_4
#define LED1_ON                    HAL_GPIO_WritePin(LED1_GPIO_Port ,LED1_Pin ,GPIO_PIN_RESET);
#define LED1_OFF                   HAL_GPIO_WritePin(LED1_GPIO_Port ,LED1_Pin ,GPIO_PIN_SET);
#define LED2_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_8
#define LED2_ON                    HAL_GPIO_WritePin(LED2_GPIO_Port ,LED2_Pin ,GPIO_PIN_RESET);
#define LED2_OFF                   HAL_GPIO_WritePin(LED2_GPIO_Port ,LED2_Pin ,GPIO_PIN_SET);
#define LED3_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_5
#define LED3_ON                    HAL_GPIO_WritePin(LED3_GPIO_Port ,LED3_Pin ,GPIO_PIN_RESET);
#define LED3_OFF                   HAL_GPIO_WritePin(LED3_GPIO_Port ,LED3_Pin ,GPIO_PIN_SET);

extern int KEY1_FLAG;
extern int KEY2_FLAG;
extern int KEY3_FLAG;
extern int KEY1_OLD_FLAG;
extern int KEY2_OLD_FLAG;
extern int KEY3_OLD_FLAG;
/* USER CODE END 0 */

TIM_HandleTypeDef htim2;

/* TIM2 init function */
void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 720-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 99;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
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

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    /* TIM2 interrupt Init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /* TIM2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == htim2.Instance) 
	{	
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0)//ctrl + C
		{
			KEY1_OLD_FLAG=KEY1_FLAG;
			KEY1_FLAG=1;
		}
		else
		{
			KEY1_OLD_FLAG=KEY1_FLAG;
			KEY1_FLAG=0;
		}
		
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0)//ctrl + V
		{
			KEY2_OLD_FLAG=KEY2_FLAG;
			KEY2_FLAG=1;
		}
		else
		{
			KEY2_OLD_FLAG=KEY2_FLAG;
			KEY2_FLAG=0;
		}
		
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == 0)//DELETE
		{
			KEY3_OLD_FLAG=KEY3_FLAG;
			KEY3_FLAG=1;
		}
		else
		{
			KEY3_OLD_FLAG=KEY3_FLAG;
			KEY3_FLAG=0;
		}
		
	}
}
/* USER CODE END 1 */
