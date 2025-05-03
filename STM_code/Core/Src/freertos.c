/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "usart.h"
//#include "servo_cfg.h"
#include "spi.h"
#include "queue.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SPI_DATA_SIZE   1
#define UART_DATA_SIZE  1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern uint8_t receive_uart2;
extern uint8_t SPI_receive ;
extern uint8_t USB_data;
uint8_t data_send_uart1;

uint8_t SPI_QUEUE_GET;
uint8_t previous_state_usb;
uint8_t previous_state_stop_condution;


uint8_t previous_state_uart1;

uint8_t previous_state_spi;



/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for myTask03 */
osThreadId_t myTask03Handle;
const osThreadAttr_t myTask03_attributes = {
  .name = "myTask03",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal6,
};
/* Definitions for myTask04 */
osThreadId_t myTask04Handle;
const osThreadAttr_t myTask04_attributes = {
  .name = "myTask04",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow3,
};
/* Definitions for SPI_DATA */
osMessageQueueId_t SPI_DATAHandle;
const osMessageQueueAttr_t SPI_DATA_attributes = {
  .name = "SPI_DATA"
};
/* Definitions for SPI_DATA_REC */
osSemaphoreId_t SPI_DATA_RECHandle;
const osSemaphoreAttr_t SPI_DATA_REC_attributes = {
  .name = "SPI_DATA_REC"
};
/* Definitions for UART_DATA_TR */
osSemaphoreId_t UART_DATA_TRHandle;
const osSemaphoreAttr_t UART_DATA_TR_attributes = {
  .name = "UART_DATA_TR"
};
/* Definitions for USB_DATA */
osSemaphoreId_t USB_DATAHandle;
const osSemaphoreAttr_t USB_DATA_attributes = {
  .name = "USB_DATA"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void servo_control(void *argument);
void handle_transmit(void *argument);
void handle_USB_data(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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

  /* Create the semaphores(s) */
  /* creation of SPI_DATA_REC */
  SPI_DATA_RECHandle = osSemaphoreNew(1, 1, &SPI_DATA_REC_attributes);

  /* creation of UART_DATA_TR */
  UART_DATA_TRHandle = osSemaphoreNew(1, 1, &UART_DATA_TR_attributes);

  /* creation of USB_DATA */
  USB_DATAHandle = osSemaphoreNew(1, 1, &USB_DATA_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of SPI_DATA */
  SPI_DATAHandle = osMessageQueueNew (10, sizeof(uint8_t), &SPI_DATA_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(servo_control, NULL, &myTask02_attributes);

  /* creation of myTask03 */
  myTask03Handle = osThreadNew(handle_transmit, NULL, &myTask03_attributes);

  /* creation of myTask04 */
  myTask04Handle = osThreadNew(handle_USB_data, NULL, &myTask04_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_servo_control */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_servo_control */
void servo_control(void *argument)
{
  /* USER CODE BEGIN servo_control */
	uint8_t ir_sensor_1 ;
	uint8_t ir_sensor_2 ;
  /* Infinite loop */
  for(;;)
  {
	  ir_sensor_1 = HAL_GPIO_ReadPin(GPIOA, IR_1_Pin);
	  ir_sensor_2 = HAL_GPIO_ReadPin(GPIOA, IR_2_Pin);

  	  if((ir_sensor_1 == GPIO_PIN_RESET) || (ir_sensor_2 == GPIO_PIN_RESET)){
  		  //servo_Motor_Start_angle_90(&servo);
  	  }else{
  		  //servo_Motor_Start_angle_N90(&servo);
  	  }
      osDelay(20);
  }
  /* USER CODE END servo_control */
}

/* USER CODE BEGIN Header_handle_transmit */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_handle_transmit */
void handle_transmit(void *argument)
{
  /* USER CODE BEGIN handle_transmit */
	uint8_t stop_condution = 'S';
  /* Infinite loop */
  for(;;)
  {
	  osSemaphoreAcquire(USB_DATAHandle, 100);
	  if(USB_data == 'R'){
		  if(previous_state_stop_condution != stop_condution){
			  HAL_UART_Transmit(&huart1, &stop_condution, UART_DATA_SIZE, 100);
			  previous_state_stop_condution = stop_condution;
		  }
	  }else{
		  osSemaphoreAcquire(SPI_DATA_RECHandle, 100);
		  osMessageQueueGet(SPI_DATAHandle,(void *)&SPI_QUEUE_GET,NULL,100);
		  osSemaphoreRelease(SPI_DATAHandle);
		  previous_state_stop_condution = SPI_QUEUE_GET;
		  if(previous_state_spi != SPI_QUEUE_GET){
			  previous_state_spi = SPI_QUEUE_GET;
			  HAL_UART_Transmit(&huart1, &SPI_QUEUE_GET, SPI_QUEUE_GET, 100);
		  }
	  }
	  osSemaphoreRelease(USB_DATAHandle);
    osDelay(20);
  }
  /* USER CODE END handle_transmit */
}

/* USER CODE BEGIN Header_handle_USB_data */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_handle_USB_data */
void handle_USB_data(void *argument)
{
  /* USER CODE BEGIN handle_USB_data */
  /* Infinite loop */
  for(;;)
  {
	  osSemaphoreAcquire(USB_DATAHandle, 100);
	  if(previous_state_usb != USB_data){
		  if(USB_data == 'R'){
			  data_send_uart1 = 'S';
		  }
		  previous_state_usb = USB_data;
	  }

	  osSemaphoreRelease(USB_DATAHandle);
    osDelay(5);
  }
  /* USER CODE END handle_USB_data */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(receive_uart2 == 15){
		HAL_NVIC_SystemReset();
	}else{
		HAL_UART_Receive_IT(&huart2,&receive_uart2,UART_DATA_SIZE);
	}

}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi){
	osSemaphoreAcquire(SPI_DATA_RECHandle, 100);
	HAL_SPI_Receive_IT(&hspi1, &SPI_receive, SPI_DATA_SIZE);
	osMessageQueuePut(SPI_DATAHandle,(void *)&SPI_receive, 0, 100);
	osSemaphoreRelease(SPI_DATAHandle);
	//xQueueSendToBackFromISR(SPI_DATAHandle,(void *)&SPI_receive,NULL);
}
/* USER CODE END Application */

