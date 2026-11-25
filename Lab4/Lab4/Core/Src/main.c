/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include <string.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
    void (*pTask)(void);
    uint32_t Delay;
    uint32_t Period;
    uint8_t  RunMe;
    uint32_t TaskID;
    uint32_t TriggerTime;
} sTask;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SCH_MAX_TASKS   10
#define NO_TASK_ID      0

#define ERROR_SCH_TOO_MANY_TASKS            1
#define ERROR_SCH_CANNOT_DELETE_TASK        2
#define RETURN_NORMAL                       0
#define RETURN_ERROR                        1
#define SCH_REPORT_ERRORS
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
IWDG_HandleTypeDef hiwdg;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
sTask SCH_tasks_G[SCH_MAX_TASKS];
static uint32_t current_task_id = 1;
static volatile uint32_t system_time_ms = 0;
uint32_t current_task_trigger_time = 0;

uint8_t Error_code_G = 0;
static uint8_t Last_error_code_G = 0;
static uint32_t Error_tick_count_G = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_IWDG_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void SCH_Init(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint32_t SCH_Add_Task(void (*pFunction)(void), uint32_t DELAY, uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint32_t taskID);

void SCH_Report_Status(void);
void SCH_Go_To_Sleep(void);

uint32_t get_time(void);
void Print_Time_Screen(char* message);

void Callback_LED_05s(void);
void Callback_LED_10s(void);
void Callback_LED_15s(void);
void Callback_LED_20s(void);
void Callback_LED_25s(void);
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
  MX_IWDG_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
   SCH_Init();

   // Đăng ký 5 Task chạy định kỳ (1 tick = 10ms)
   SCH_Add_Task(Callback_LED_05s, 50, 50);   // 50 ticks  = 500ms
   SCH_Add_Task(Callback_LED_10s, 100, 100); // 100 ticks = 1000ms
   SCH_Add_Task(Callback_LED_15s, 150, 150); // 150 ticks = 1500ms
   SCH_Add_Task(Callback_LED_20s, 200, 200); // 200 ticks = 2000ms
   SCH_Add_Task(Callback_LED_25s, 250, 250); // 250 ticks = 2500ms

   // Kích hoạt ngắt Timer 2
   HAL_TIM_Base_Start_IT(&htim2);
   /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  SCH_Dispatch_Tasks();
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

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
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
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
  huart2.Init.BaudRate = 115200;
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_5s_Pin|LED_10s_Pin|LED_15s_Pin|LED_20s_Pin
                          |LED_25s_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_5s_Pin LED_10s_Pin LED_15s_Pin LED_20s_Pin
                           LED_25s_Pin */
  GPIO_InitStruct.Pin = LED_5s_Pin|LED_10s_Pin|LED_15s_Pin|LED_20s_Pin
                          |LED_25s_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 10);
    return ch;
}

uint32_t get_time(void) {
    return system_time_ms;
}

void Print_Time_Screen(char* message) {
    printf("[%lu ms] %s\r\n", current_task_trigger_time, message); 
}

void SCH_Init(void) {
    for (uint8_t i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask  = 0;
        SCH_tasks_G[i].Delay  = 0;
        SCH_tasks_G[i].Period = 0;
        SCH_tasks_G[i].RunMe  = 0;
        SCH_tasks_G[i].TaskID = NO_TASK_ID;
    }
    Error_code_G = 0;
}

#define ENTER_CRITICAL()  uint32_t primask_ = __get_PRIMASK(); __disable_irq()
#define EXIT_CRITICAL()   __set_PRIMASK(primask_)

void SCH_Update(void) {
    HAL_IWDG_Refresh(&hiwdg);
    system_time_ms += 10;

    uint8_t i = 0;
    while (i < SCH_MAX_TASKS && SCH_tasks_G[i].pTask != 0 && SCH_tasks_G[i].Delay == 0) {
        i++;
    }

    if (i < SCH_MAX_TASKS && SCH_tasks_G[i].pTask != 0) {
        SCH_tasks_G[i].Delay--;
    }

    for (uint8_t j = 0; j < SCH_MAX_TASKS && SCH_tasks_G[j].pTask != 0 && SCH_tasks_G[j].Delay == 0; j++) {
        if (SCH_tasks_G[j].RunMe == 0) {
            SCH_tasks_G[j].RunMe = 1;
            SCH_tasks_G[j].TriggerTime = system_time_ms;
        }
    }
}

static uint32_t SCH_Insert(void (*pFunction)(void), uint32_t DELAY, uint32_t PERIOD, uint32_t id) {
    uint8_t Index = 0;

    if (SCH_tasks_G[SCH_MAX_TASKS - 1].pTask != 0) {
        Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
        return NO_TASK_ID;
    }

    while ((Index < SCH_MAX_TASKS) && (SCH_tasks_G[Index].pTask != 0)) {
        if (SCH_tasks_G[Index].Delay > 0) {
            if (DELAY >= SCH_tasks_G[Index].Delay) {
                DELAY -= SCH_tasks_G[Index].Delay;
            } else {
                break;
            }
        }
        Index++;
    }

    for (uint8_t i = SCH_MAX_TASKS - 1; i > Index; i--) {
        SCH_tasks_G[i] = SCH_tasks_G[i - 1];
    }

    SCH_tasks_G[Index].pTask       = pFunction;
    SCH_tasks_G[Index].Delay       = DELAY;
    SCH_tasks_G[Index].Period      = PERIOD;
    SCH_tasks_G[Index].RunMe       = 0;
    SCH_tasks_G[Index].TaskID      = id;
    SCH_tasks_G[Index].TriggerTime = 0;

    if (Index + 1 < SCH_MAX_TASKS && SCH_tasks_G[Index + 1].pTask != 0) {
        SCH_tasks_G[Index + 1].Delay -= DELAY;
    }

    return id;
}

uint32_t SCH_Add_Task(void (*pFunction)(void), uint32_t DELAY, uint32_t PERIOD) {
    ENTER_CRITICAL();
    uint32_t id = SCH_Insert(pFunction, DELAY, PERIOD, current_task_id);
    if (id != NO_TASK_ID) {
        current_task_id++;
    }
    EXIT_CRITICAL();
    return id;
}

void SCH_Dispatch_Tasks(void) {
    uint8_t ran = 0;

    if (SCH_tasks_G[0].RunMe > 0) {
        ran = 1;
        sTask tempTask = SCH_tasks_G[0];
        current_task_trigger_time = tempTask.TriggerTime;
        (*tempTask.pTask)();

        ENTER_CRITICAL();
        for (uint8_t i = 0; i < SCH_MAX_TASKS - 1; i++) {
            SCH_tasks_G[i] = SCH_tasks_G[i + 1];
        }
        SCH_tasks_G[SCH_MAX_TASKS - 1].pTask  = 0;
        SCH_tasks_G[SCH_MAX_TASKS - 1].Delay  = 0;
        SCH_tasks_G[SCH_MAX_TASKS - 1].Period = 0;
        SCH_tasks_G[SCH_MAX_TASKS - 1].RunMe  = 0;
        SCH_tasks_G[SCH_MAX_TASKS - 1].TaskID = NO_TASK_ID;

        if (tempTask.Period > 0) {
            uint32_t next_due  = tempTask.TriggerTime + tempTask.Period * 10;
            int32_t  delay_ms  = (int32_t)(next_due - system_time_ms);
            uint32_t delay_tk  = (delay_ms > 0) ? ((uint32_t)delay_ms / 10) : 1;
            if (delay_tk == 0) delay_tk = 1;
            SCH_Insert(tempTask.pTask, delay_tk, tempTask.Period, tempTask.TaskID);
        }
        EXIT_CRITICAL();
    }

    SCH_Report_Status();
    if (!ran) {
        SCH_Go_To_Sleep();
    }
}

uint8_t SCH_Delete_Task(uint32_t taskID) {
    uint8_t Index = 0;
    uint8_t Return_code = RETURN_ERROR;

    if (taskID == NO_TASK_ID) return RETURN_ERROR;

    ENTER_CRITICAL();
    for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
        if (SCH_tasks_G[Index].TaskID == taskID) {
            Return_code = RETURN_NORMAL;
            break;
        }
    }

    if (Return_code == RETURN_NORMAL) {
        if (Index + 1 < SCH_MAX_TASKS && SCH_tasks_G[Index + 1].pTask != 0) {
            SCH_tasks_G[Index + 1].Delay += SCH_tasks_G[Index].Delay;
        }

        for (uint8_t i = Index; i < SCH_MAX_TASKS - 1; i++) {
            SCH_tasks_G[i] = SCH_tasks_G[i + 1];
        }

        SCH_tasks_G[SCH_MAX_TASKS - 1].pTask  = 0;
        SCH_tasks_G[SCH_MAX_TASKS - 1].Delay  = 0;
        SCH_tasks_G[SCH_MAX_TASKS - 1].Period = 0;
        SCH_tasks_G[SCH_MAX_TASKS - 1].RunMe  = 0;
        SCH_tasks_G[SCH_MAX_TASKS - 1].TaskID = NO_TASK_ID;
    } else {
        Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
    }
    EXIT_CRITICAL();

    return Return_code;
}

void SCH_Go_To_Sleep(void) {
    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

void SCH_Report_Status(void) {
#ifdef SCH_REPORT_ERRORS
    if (Error_code_G != Last_error_code_G) {
        Last_error_code_G = Error_code_G;
        if (Error_code_G != 0) {
            Error_tick_count_G = 60000;
        } else {
            Error_tick_count_G = 0;
        }
    } else {
        if (Error_tick_count_G != 0) {
            if (--Error_tick_count_G == 0) {
                Error_code_G = 0;
            }
        }
    }
#endif
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        SCH_Update();
    }
}

void Callback_LED_05s(void) {
    HAL_GPIO_TogglePin(GPIOA, LED_5s_Pin);
    Print_Time_Screen("Task 0.5s Run");
}

void Callback_LED_10s(void) {
    HAL_GPIO_TogglePin(GPIOA, LED_10s_Pin);
    Print_Time_Screen("Task 1.0s Run");
}

void Callback_LED_15s(void) {
    HAL_GPIO_TogglePin(GPIOA, LED_15s_Pin);
    Print_Time_Screen("Task 1.5s Run");
}

void Callback_LED_20s(void) {
    HAL_GPIO_TogglePin(GPIOA, LED_20s_Pin);
    Print_Time_Screen("Task 2.0s Run");
}

void Callback_LED_25s(void) {
    HAL_GPIO_TogglePin(GPIOA, LED_25s_Pin);
    Print_Time_Screen("Task 2.5s Run");
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
