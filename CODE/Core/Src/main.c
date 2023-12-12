/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_hid.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
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

int KEY1_FLAG=0;
int KEY2_FLAG=0;
int KEY3_FLAG=0;
int KEY1_OLD_FLAG=0;
int KEY2_OLD_FLAG=0;
int KEY3_OLD_FLAG=0;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern USBD_HandleTypeDef hUsbDeviceFS;


/*
 * buffer[0] - bit0: Left CTRL
 *           -bit1: Left SHIFT
 *           -bit2: Left ALT
 *           -bit3: Left GUI
 *           -bit4: Right CTRL
 *           -bit5: Right SHIFT
 *           -bit6: Right ALT
 *           -bit7: Right GUI 
 * buffer[1] - Padding = Always 0x00
 * buffer[2] - Key 1
 * buffer[3] - Key 2
 * buffer[4] - Key 3
 * buffer[5] - Key 4
 * buffer[6] - Key 5
 * buffer[7] - Key 6
 */
uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_USB_DEVICE_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  
	   if(KEY1_FLAG == 1&&KEY1_OLD_FLAG==0)//ctrl + C
    {  
      buffer[0] = 0x01; //L CTRL
      buffer[2] = 0x06; //C
      USBD_HID_SendReport(&hUsbDeviceFS, buffer, 8); //send
	HAL_GPIO_WritePin(LED1_GPIO_Port ,LED1_Pin ,GPIO_PIN_RESET);
//      HAL_Delay(15); //delay
	}
      if(KEY1_FLAG == 0&&KEY1_OLD_FLAG==1)//ctrl + C
	{
      buffer[0] = 0x00;
      buffer[2] = 0x00;
      USBD_HID_SendReport(&hUsbDeviceFS, buffer, 8);
 //     HAL_Delay(15);
    HAL_GPIO_WritePin(LED1_GPIO_Port ,LED1_Pin ,GPIO_PIN_SET);
 //     while(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0)
  //    HAL_Delay(15);
    }
	
	 if(KEY2_FLAG == 1&&KEY2_OLD_FLAG==0)//CTRL + V
    {  
      buffer[0] = 0x01; //L CTRL
      buffer[2] = 0x19; //C
      USBD_HID_SendReport(&hUsbDeviceFS, buffer, 8); //send
	HAL_GPIO_WritePin(LED2_GPIO_Port ,LED2_Pin ,GPIO_PIN_RESET);
//     HAL_Delay(15); //delay
	}
	if(KEY2_FLAG == 0&&KEY2_OLD_FLAG==1)//CTRL + V
	{
      buffer[0] = 0x00;
      buffer[2] = 0x00;
      USBD_HID_SendReport(&hUsbDeviceFS, buffer, 8);
 //     HAL_Delay(15);
    HAL_GPIO_WritePin(LED2_GPIO_Port ,LED2_Pin ,GPIO_PIN_SET);
 //     while(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0)
  //    HAL_Delay(15);
    }
	
	if(KEY3_FLAG == 1 && KEY3_OLD_FLAG==0)//backspace
    {  
      buffer[0] = 0x00; //
      buffer[2] = 0x2A; //backspace
      USBD_HID_SendReport(&hUsbDeviceFS, buffer, 8); //send
	HAL_GPIO_WritePin(LED3_GPIO_Port ,LED3_Pin ,GPIO_PIN_RESET);	
//      HAL_Delay(15); //delay
	}
     if(KEY3_FLAG == 0&&KEY3_OLD_FLAG==1)//backspace
	 {
      buffer[0] = 0x00;
      buffer[2] = 0x00;
      USBD_HID_SendReport(&hUsbDeviceFS, buffer, 8);
//      HAL_Delay(15);
     HAL_GPIO_WritePin(LED3_GPIO_Port ,LED3_Pin ,GPIO_PIN_SET);
//      while(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == 0)
//      HAL_Delay(15);
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

