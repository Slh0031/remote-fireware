/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask_ledHandle;
osThreadId Task_buzzerHandle;
osThreadId myTask_Date_pacHandle;
osThreadId myTask_adcHandle;
osThreadId myTask_ic_rgbHandle;
osThreadId myTask_oled_guiHandle;
osThreadId myTask_keyHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void Task_led(void const * argument);
void myTask_buzzer(void const * argument);
void Task_Date_pack(void const * argument);
void Task_adc(void const * argument);
void Task_ic_rgb(void const * argument);
void Task_oled_gui(void const * argument);
void Task_key(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask_led */
  osThreadDef(myTask_led, Task_led, osPriorityIdle, 0, 128);
  myTask_ledHandle = osThreadCreate(osThread(myTask_led), NULL);

  /* definition and creation of Task_buzzer */
  osThreadDef(Task_buzzer, myTask_buzzer, osPriorityIdle, 0, 128);
  Task_buzzerHandle = osThreadCreate(osThread(Task_buzzer), NULL);

  /* definition and creation of myTask_Date_pac */
  osThreadDef(myTask_Date_pac, Task_Date_pack, osPriorityIdle, 0, 128);
  myTask_Date_pacHandle = osThreadCreate(osThread(myTask_Date_pac), NULL);

  /* definition and creation of myTask_adc */
  osThreadDef(myTask_adc, Task_adc, osPriorityIdle, 0, 128);
  myTask_adcHandle = osThreadCreate(osThread(myTask_adc), NULL);

  /* definition and creation of myTask_ic_rgb */
  osThreadDef(myTask_ic_rgb, Task_ic_rgb, osPriorityIdle, 0, 128);
  myTask_ic_rgbHandle = osThreadCreate(osThread(myTask_ic_rgb), NULL);

  /* definition and creation of myTask_oled_gui */
  osThreadDef(myTask_oled_gui, Task_oled_gui, osPriorityIdle, 0, 128);
  myTask_oled_guiHandle = osThreadCreate(osThread(myTask_oled_gui), NULL);

  /* definition and creation of myTask_key */
  osThreadDef(myTask_key, Task_key, osPriorityIdle, 0, 128);
  myTask_keyHandle = osThreadCreate(osThread(myTask_key), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Task_led */
/**
* @brief Function implementing the myTask_led thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_led */
__weak void Task_led(void const * argument)
{
  /* USER CODE BEGIN Task_led */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Task_led */
}

/* USER CODE BEGIN Header_myTask_buzzer */
/**
* @brief Function implementing the Task_buzzer thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_myTask_buzzer */
__weak void myTask_buzzer(void const * argument)
{
  /* USER CODE BEGIN myTask_buzzer */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END myTask_buzzer */
}

/* USER CODE BEGIN Header_Task_Date_pack */
/**
* @brief Function implementing the myTask_Date_pac thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_Date_pack */
__weak void Task_Date_pack(void const * argument)
{
  /* USER CODE BEGIN Task_Date_pack */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Task_Date_pack */
}

/* USER CODE BEGIN Header_Task_adc */
/**
* @brief Function implementing the myTask_adc thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_adc */
__weak void Task_adc(void const * argument)
{
  /* USER CODE BEGIN Task_adc */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Task_adc */
}

/* USER CODE BEGIN Header_Task_ic_rgb */
/**
* @brief Function implementing the myTask_ic_rgb thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_ic_rgb */
__weak void Task_ic_rgb(void const * argument)
{
  /* USER CODE BEGIN Task_ic_rgb */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Task_ic_rgb */
}

/* USER CODE BEGIN Header_Task_oled_gui */
/**
* @brief Function implementing the myTask_oled_gui thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_oled_gui */
__weak void Task_oled_gui(void const * argument)
{
  /* USER CODE BEGIN Task_oled_gui */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Task_oled_gui */
}

/* USER CODE BEGIN Header_Task_key */
/**
* @brief Function implementing the myTask_key thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_key */
__weak void Task_key(void const * argument)
{
  /* USER CODE BEGIN Task_key */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Task_key */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

