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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "queue.h"
#include <stdio.h>
#include <string.h>
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
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

TIM_HandleTypeDef htim1;

/* Definitions for breakTask */
osThreadId_t breakTaskHandle;
const osThreadAttr_t breakTask_attributes = {
    .name = "breakTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityLow,
};
/* Definitions for throttleTask */
osThreadId_t throttleTaskHandle;
const osThreadAttr_t throttleTask_attributes = {
    .name = "throttleTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityLow,
};
/* Definitions for gearTask */
osThreadId_t gearTaskHandle;
const osThreadAttr_t gearTask_attributes = {
    .name = "gearTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityLow,
};
/* Definitions for processingTask */
osThreadId_t processingTaskHandle;
const osThreadAttr_t processingTask_attributes = {
    .name = "processingTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityLow,
};
/* Definitions for displayTask */
osThreadId_t displayTaskHandle;
const osThreadAttr_t displayTask_attributes = {
    .name = "displayTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityLow,
};
/* Definitions for BrakeQueue */
osMessageQueueId_t BrakeQueueHandle;
const osMessageQueueAttr_t BrakeQueue_attributes = {
    .name = "BrakeQueue"};
/* Definitions for ThrottleQueue */
osMessageQueueId_t ThrottleQueueHandle;
const osMessageQueueAttr_t ThrottleQueue_attributes = {
    .name = "ThrottleQueue"};
/* Definitions for GearQueue */
osMessageQueueId_t GearQueueHandle;
const osMessageQueueAttr_t GearQueue_attributes = {
    .name = "GearQueue"};
/* Definitions for SpeedQueue */
osMessageQueueId_t SpeedQueueHandle;
const osMessageQueueAttr_t SpeedQueue_attributes = {
    .name = "SpeedQueue"};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC2_Init(void);
static void MX_TIM1_Init(void);
void StartBreakTask(void *argument);
void StartThrottleTask(void *argument);
void StartGearTask(void *argument);
void StartProcessingTask(void *argument);
void StartDisplayTask(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void sendCommandLCD(unsigned char cData)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);

    GPIOA->ODR = cData;

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_Delay(0.001);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
}

void sendDataLCD(unsigned char cData)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);

    GPIOA->ODR = cData;

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_Delay(0.001);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
}

void configLCD()
{
    sendCommandLCD(0x38); // Configuration option Two Lines 5x7 characters 8bit Data
    sendCommandLCD(0x0B); // Turns display off
    sendCommandLCD(0x0C); // Turns display on
    sendCommandLCD(0x01); // Clear display
}

void printLCD(char *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        sendDataLCD(*(arr + i));
    }
}

int decreaseVelocity(int currValue, int minusVal)
{
    if (currValue - minusVal < 0)
    {
        return 0;
    }
    return currValue - minusVal;
}

int increaseVelocity(int currValue, int plusVal, int maxVal)
{
    if (currValue + plusVal > maxVal)
    {
        return maxVal;
    }
    return currValue + plusVal;
}

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
    MX_ADC2_Init();
    MX_TIM1_Init();
    /* USER CODE BEGIN 2 */

    /* USER CODE END 2 */

    /* Init scheduler */
    osKernelInitialize();

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* Create the queue(s) */
    /* creation of BrakeQueue */
    BrakeQueueHandle = osMessageQueueNew(16, sizeof(uint16_t), &BrakeQueue_attributes);

    /* creation of ThrottleQueue */
    ThrottleQueueHandle = osMessageQueueNew(16, sizeof(uint16_t), &ThrottleQueue_attributes);

    /* creation of GearQueue */
    GearQueueHandle = osMessageQueueNew(16, sizeof(uint16_t), &GearQueue_attributes);

    /* creation of SpeedQueue */
    SpeedQueueHandle = osMessageQueueNew(32, sizeof(uint32_t), &SpeedQueue_attributes);

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of breakTask */
    breakTaskHandle = osThreadNew(StartBreakTask, NULL, &breakTask_attributes);

    /* creation of throttleTask */
    throttleTaskHandle = osThreadNew(StartThrottleTask, NULL, &throttleTask_attributes);

    /* creation of gearTask */
    gearTaskHandle = osThreadNew(StartGearTask, NULL, &gearTask_attributes);

    /* creation of processingTask */
    processingTaskHandle = osThreadNew(StartProcessingTask, NULL, &processingTask_attributes);

    /* creation of displayTask */
    displayTaskHandle = osThreadNew(StartDisplayTask, NULL, &displayTask_attributes);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */

    /* Start scheduler */
    osKernelStart();

    /* We should never get here as control is now taken by the scheduler */
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /*	  sendCommandLCD(0x01); // Clear display
              sendCommandLCD(0x85);
              HAL_ADC_Start(&hadc1);
              HAL_ADC_PollForConversion(&hadc1, 300);
              int result = HAL_ADC_GetValue(&hadc1);
              char buffer[50];
              result = (result * 100)/MAX_ADC;
              sprintf(buffer, "%d", result);
              printLCD(buffer, strlen(buffer));

              sendCommandLCD(0xC3);

              HAL_ADC_Start(&hadc2);
              HAL_ADC_PollForConversion(&hadc2, 300);
              result = HAL_ADC_GetValue(&hadc2);
              result = (result * 100)/MAX_ADC;
              sprintf(buffer, "%d", result);
              printLCD(buffer, strlen(buffer));

              sendDataLCD(0x20); // Space

              if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)) {
                  sendDataLCD('0' + 1);
              }else{
                  sendDataLCD('0' + 0);
              }
              if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)) {
                  sendDataLCD('0' + 1);
              }else{
                  sendDataLCD('0' + 0);
              }
              */
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
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief ADC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC1_Init(void)
{

    /* USER CODE BEGIN ADC1_Init 0 */

    /* USER CODE END ADC1_Init 0 */

    ADC_ChannelConfTypeDef sConfig = {0};

    /* USER CODE BEGIN ADC1_Init 1 */

    /* USER CODE END ADC1_Init 1 */

    /** Common config
     */
    hadc1.Instance = ADC1;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Regular Channel
     */
    sConfig.Channel = ADC_CHANNEL_8;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN ADC1_Init 2 */

    /* USER CODE END ADC1_Init 2 */
}

/**
 * @brief ADC2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC2_Init(void)
{

    /* USER CODE BEGIN ADC2_Init 0 */

    /* USER CODE END ADC2_Init 0 */

    ADC_ChannelConfTypeDef sConfig = {0};

    /* USER CODE BEGIN ADC2_Init 1 */

    /* USER CODE END ADC2_Init 1 */

    /** Common config
     */
    hadc2.Instance = ADC2;
    hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc2.Init.ContinuousConvMode = DISABLE;
    hadc2.Init.DiscontinuousConvMode = DISABLE;
    hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc2.Init.NbrOfConversion = 1;
    if (HAL_ADC_Init(&hadc2) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Regular Channel
     */
    sConfig.Channel = ADC_CHANNEL_9;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN ADC2_Init 2 */

    /* USER CODE END ADC2_Init 2 */
}

/**
 * @brief TIM1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM1_Init(void)
{

    /* USER CODE BEGIN TIM1_Init 0 */

    /* USER CODE END TIM1_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    /* USER CODE BEGIN TIM1_Init 1 */

    /* USER CODE END TIM1_Init 1 */
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 72 - 1;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 100 - 1;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM1_Init 2 */

    /* USER CODE END TIM1_Init 2 */
    HAL_TIM_MspPostInit(&htim1);
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
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, PA0_Pin | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_RESET);

    /*Configure GPIO pins : PA0_Pin PA1 PA2 PA3
                             PA4 PA5 PA6 PA7 */
    GPIO_InitStruct.Pin = PA0_Pin | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PB3 PB4 */
    GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : PB5 PB6 PB7 */
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartBreakTask */
/**
 * @brief  Function implementing the breakTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartBreakTask */
void StartBreakTask(void *argument)
{
    /* USER CODE BEGIN 5 */
    int MAX_ADC = 4035;
    int result;
    /* Infinite loop */
    for (;;)
    {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 0);
        result = HAL_ADC_GetValue(&hadc1);
        result = (result * 100) / MAX_ADC;
        if (result < 15)
            result = 0;
        xQueueSendToBack(BrakeQueueHandle, (void *)&result, 0);
        osDelay(10);
    }
    /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartThrottleTask */
/**
 * @brief Function implementing the throttleTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartThrottleTask */
void StartThrottleTask(void *argument)
{
    /* USER CODE BEGIN StartThrottleTask */
    int MAX_ADC = 4035;
    int result;
    /* Infinite loop */
    for (;;)
    {
        HAL_ADC_Start(&hadc2);
        HAL_ADC_PollForConversion(&hadc2, 0);
        result = HAL_ADC_GetValue(&hadc2);
        result = (result * 100) / MAX_ADC;
        if (result < 15)
            result = 0;
        xQueueSendToBack(ThrottleQueueHandle, (void *)&result, 0);
        osDelay(10);
    }
    /* USER CODE END StartThrottleTask */
}

/* USER CODE BEGIN Header_StartGearTask */
/**
 * @brief Function implementing the gearTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartGearTask */
void StartGearTask(void *argument)
{
    /* USER CODE BEGIN StartGearTask */
    /* Infinite loop */
    for (;;)
    {
        int option; // Parking
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3))
        {
            option = 0;
        }
        else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))
        {
            option = 2;
        }
        else
        {
            option = 1;
        }
        xQueueSendToBack(GearQueueHandle, &option, 0);
        osDelay(50);
    }
    /* USER CODE END StartGearTask */
}

/* USER CODE BEGIN Header_StartProcessingTask */
/**
 * @brief Function implementing the processingTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartProcessingTask */
void StartProcessingTask(void *argument)
{
    /* USER CODE BEGIN StartProcessingTask */
    /* Infinite loop */
    int desiredSpeed = 0;
    int averageBrakePerc = 0;
    int averageThrotPerc = 0;
    int requestedGear = 0;
    for (;;)
    {
        int tempBrake = 0;
        int acumBrake = 0;
        int contBrake = 0;
        while ((xQueueReceive(BrakeQueueHandle, &(tempBrake), 0) == pdPASS))
        {
            acumBrake += tempBrake;
            contBrake++;
        }
        if (contBrake == 0 || acumBrake == 0)
        {
            averageBrakePerc = 0;
        }
        else
        {
            averageBrakePerc = acumBrake / contBrake;
        }

        int tempThrot = 0;
        int acumThrot = 0;
        int contThrot = 0;
        while ((xQueueReceive(ThrottleQueueHandle, &(tempThrot), 0) == pdPASS))
        {
            acumThrot += tempThrot;
            contThrot++;
        }
        if (contThrot == 0 || acumThrot == 0)
        {
            averageThrotPerc = 0;
        }
        else
        {
            averageThrotPerc = acumThrot / contThrot;
        }

        int valueGear = 0;
        int contGear = 0;
        while ((xQueueReceive(GearQueueHandle, &(valueGear), 0) == pdPASS))
        {
            contGear++;
        }
        if (contGear == 0)
        {
            requestedGear = 0;
        }
        else
        {
            requestedGear = valueGear;
        }

        if (requestedGear == 0)
        {
            desiredSpeed = decreaseVelocity(desiredSpeed, 400);
        }
        else if (!(averageBrakePerc > 0 && averageThrotPerc > 0))
        {
            int maxAcc = 0;
            int maxSpeed = 0;
            if (requestedGear == 1)
            {
                maxSpeed = 80000;
                maxAcc = 1600;
            }
            else
            {
                maxSpeed = 200000;
                maxAcc = 2400;
            }
            if (averageThrotPerc > 0)
            {
                desiredSpeed = increaseVelocity(desiredSpeed, (averageThrotPerc * maxAcc) / 100, maxSpeed);
            }
            else if (averageBrakePerc > 0)
            {
                desiredSpeed = decreaseVelocity(desiredSpeed, (averageBrakePerc * 3200) / 100);
            }
        }
        int *newSpeed = &desiredSpeed;
        xQueueSendToBack(SpeedQueueHandle, newSpeed, 0);

        osDelay(100);
    }
    /* USER CODE END StartProcessingTask */
}

/* USER CODE BEGIN Header_StartDisplayTask */
/**
 * @brief Function implementing the displayTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDisplayTask */
void StartDisplayTask(void *argument)
{
    /* USER CODE BEGIN StartDisplayTask */
    /* Infinite loop */
    configLCD();
    char buffer[50];
    int averageDesiredSpeed = 0;
    for (;;)
    {
        int tempSpeed = 0;
        int acumSpeed = 0;
        int contSpeed = 0;
        while ((xQueueReceive(SpeedQueueHandle, &(tempSpeed), 0) == pdPASS))
        {
            acumSpeed += tempSpeed;
            contSpeed++;
        }
        if (contSpeed == 0 || acumSpeed == 0)
        {
            averageDesiredSpeed = 0;
        }
        else
        {
            averageDesiredSpeed = acumSpeed / contSpeed;
        }
        sendCommandLCD(0x80);
        sprintf(buffer, "Speed = %03d km/hr", averageDesiredSpeed / 1000);
        printLCD(buffer, strlen(buffer));
        TIM1->CCR1 = (averageDesiredSpeed * 100) / 200000;
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        osDelay(500);
    }
    /* USER CODE END StartDisplayTask */
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM2 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* USER CODE BEGIN Callback 0 */

    /* USER CODE END Callback 0 */
    if (htim->Instance == TIM2)
    {
        HAL_IncTick();
    }
    /* USER CODE BEGIN Callback 1 */

    /* USER CODE END Callback 1 */
}

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
