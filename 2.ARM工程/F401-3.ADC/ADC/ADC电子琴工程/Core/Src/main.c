/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
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
#include "adc.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

void display(int star_x, int num, int mode)
{
  OLED_Rect1(0, 0, 127, 63);
  OLED_Circle(25, 32, 20);
  OLED_Circle(25, 32, 3);
  Draw_Point(25, 32, 20, num / 40);
  if (mode == 1)
  {
    OLED_Bitmap(star_x - 8 * 3, 30, codea_g[7], 8, 16); /*A*/
  }
  else
  {
    OLED_Bitmap(star_x - 8 * 3, 30, codea_g[0], 8, 16); /*a*/
  }
  if (mode == 2)
  {
    OLED_Bitmap(star_x - 8 * 2, 30, codea_g[3 + 7], 8, 16); /*d*/
  }
  else
  {
    OLED_Bitmap(star_x - 8 * 2, 30, codea_g[3], 8, 16); /*d*/
  }
  if (mode == 4)
  {
    OLED_Bitmap(star_x - 8, 30, codea_g[2 + 7], 8, 16); /*c*/
  }
  else
  {
    OLED_Bitmap(star_x - 8, 30, codea_g[2], 8, 16); /*c*/
  }
  OLED_Bitmap(star_x + 8 * 3, 30, code0_9[num % 10], 8, 16);
  OLED_Bitmap(star_x + 8 * 2, 30, code0_9[num / 10 % 10], 8, 16);
  OLED_Bitmap(star_x + 8, 30, code0_9[num / 100 % 10], 8, 16);
  OLED_Bitmap(star_x, 30, code0_9[num / 1000 % 10], 8, 16);
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
unsigned int Tone[] = {
    // /*do*/ 275, /*ra*/ 244, /*mi*/ 218, /*fa*/ 206, /*suo*/ 184, /*la*/ 184, /*si*/ 163};
    /*do*/274,  /*ra*/244,  /*mi*/218,  /*fa*/206, /*suo*/183, /*la*/163, /*si*/ 145};

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
  MX_ADC1_Init();
  MX_SPI2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  int star_x = 72, Memory = 0;
  // HAL_ADC_Start(&hadc1);
  HAL_ADC_Start_IT(&hadc1);
  HAL_TIM_Base_Start_IT(&htim3);
  // int tmp;
  InitGraph();
  // Resize(bmp,63,64);
  // OLED_FILL(Sbmp);
  OLED_Rect1(0, 0, 127, 63);
  OLED_Circle(25, 32, 20);
  OLED_Circle(25, 32, 3);
  OLED_UpdateScreen();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  unsigned int i = 0;
  int mode = 1;
  TIM3->PSC = 1000;
  while (1)
  {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    HAL_Delay(5);
    // HAL_ADC_PollForConversion(&hadc1, 100);
    // i=(a1/4096)*100;
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 0)
    {
      mode = 1;
    }
    else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 0)
    {
      mode = 2;
    }
    else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0)
    {
      mode = 4;
    }
    i = result;
    if (i / 100 == 15)
    {
      TIM3->CNT = 0;
      TIM3->ARR = Tone[0] / mode;
    }
    else if (i / 100 >= 18 && i / 100 <= 19)
    {
      TIM3->CNT = 0;
      TIM3->ARR = Tone[1] / mode;
    }
    else if (i / 100 >= 22 && i / 100 <= 23)
    {
      TIM3->CNT = 0;
      TIM3->ARR = Tone[2] / mode;
    }
    else if (i / 100 >= 26 && i / 100 <= 26)
    {
      TIM3->CNT = 0;
      TIM3->ARR = Tone[3] / mode;
    }
    else if (i / 100 >= 29 && i / 100 <= 30)
    {
      TIM3->CNT = 0;
      TIM3->ARR = Tone[4] / mode;
    }
    else if (i / 100 >= 33 && i / 100 <= 34)
    {
      TIM3->CNT = 0;
      TIM3->ARR = Tone[5] / mode;
    }
    else if (i / 100 >= 36 && i / 100 <= 37)
    {
      TIM3->CNT = 0;
      TIM3->ARR = Tone[6] / mode;
    }
    else
    {
      TIM3->CNT = 0;
      TIM3->ARR = 0;
    }
    OLED_ClearScreen();
    display(star_x, i, mode);
    OLED_UpdateScreen();
    /*do
    {
      if (Memory < i)
      {
        Memory+=40;
        OLED_ClearScreen();
        display(star_x, Memory);
        OLED_UpdateScreen();
      }
      else if (Memory > i)
      {
        Memory-=40;
        OLED_ClearScreen();
        display(star_x, Memory);
        OLED_UpdateScreen();
      }
      i = result;
      HAL_Delay(5);
    } while (!(Memory > i - 40 && Memory < i + 40));
    Memory = i;*/
    // if (i < 80)
    // {
    //   HAL_Delay(30);
    //   continue;
    // }
    // for (; Memory < i && Memory < 4000; Memory += 25,i=result)
    // {
    //   OLED_ClearScreen();
    //   display(star_x, Memory);
    //   OLED_UpdateScreen();
    // }
    // if (Memory > i - 40 && Memory < i + 40)
    // {
    //   Memory = i;
    // }
    // for (; Memory > i && Memory > 0; Memory -= 25,i=result)
    // {
    //   OLED_ClearScreen();
    //   display(star_x, Memory);
    //   OLED_UpdateScreen();
    // }
    // Memory = i;
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

  /** Configure the main internal regulator output voltage
   */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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

#ifdef USE_FULL_ASSERT
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
