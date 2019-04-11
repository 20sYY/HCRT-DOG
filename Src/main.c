
#include "robocon.h"

#define START_TASK_PRIO		1		//任务优先级
#define START_STK_SIZE 		128  		//任务堆栈大小	
TaskHandle_t StartTask_Handler;		//任务句柄
void start_task(void *pvParameters);		//任务函数

#define MotorControl_TASK_PRIO		2		//任务优先级
#define MotorControl_STK_SIZE 		1024  //任务堆栈大小
TaskHandle_t MotorControlTask_Handler;		//任务句柄
void MotorControl_task(void *pvParameters);	//任务函数

#define Debug_TASK_PRIO		4		//任务优先级
#define Debug_STK_SIZE 		512  //任务堆栈大小	
TaskHandle_t DebugTask_Handler;		//任务句柄
void Debug_task(void *pvParameters);		//任务函数

#define PostureControl_TASK_PRIO		2		//任务优先级
#define PostureControl_STK_SIZE 		512 	 //任务堆栈大小	
TaskHandle_t PostureControlTask_Handler;		//任务句柄
void PostureControl_task(void *pvParameters);		//任务函数

#define TASK4_TASK_PRIO		4		//任务优先级
#define TASK4_STK_SIZE 		128 	 //任务堆栈大小	
TaskHandle_t Task4Task_Handler;		//任务句柄
void task4_task(void *pvParameters);		//任务函数

#define TASK5_TASK_PRIO		2		//任务优先级
#define TASK5_STK_SIZE 		512 	 //任务堆栈大小	
TaskHandle_t Task5Task_Handler;		//任务句柄
void task5_task(void *pvParameters);		//任务函数

void SystemClock_Config(void);

int main(void)
{
    HAL_Init();						//Hal库初始化
    SystemClock_Config();	//系统时钟初始化
    MX_GPIO_Init();				//GPIO初始化
    MX_CAN1_Init();				//CAN1接口初始化
    MX_SPI5_Init();				//spi5初始化
    MX_USART2_UART_Init();//usart2串口初始化
    TIM3_Init(10-1,9000-1);//定时器3初始化，定时器时钟为90M，分频系数为9000-1,所以定时器3的频率为90M/9000=10K，自动重装载为10-1，那么定时器周期就是1ms

    moto_param_init();		//电机PID参数初始化
    buzzer_init(500-1, 90-1);//蜂鸣器初始化
    led_configuration();	//流水灯 红绿灯初始化
    Servo_Init(20000-1,90-1);		//f=Tck/(psc+1)*(arr+1) 定时器时钟为90M  50Hz=180MHz/(3000*1200)   330HZ=180MHZ/(3000*182)
//		HAL_UART_Receive_DMA(&huart2, USART2RxBuf, USART2RXBUFSIZE);
//	mpu_device_init();
//	init_quaternion();
//		Servo1_DOWN;
//		Servo2_DOWN_POS;

    Servo1_TEST_POSITION;
    Servo2_TEST_POSITION;
		printf("system init\r\n");
    //创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄
    vTaskStartScheduler();          //开启任务调度

}

//开始任务任务函数
void start_task(void *pvParameters)
{

    taskENTER_CRITICAL();           //进入临界区
    //创建MotorControl_task		
    xTaskCreate((TaskFunction_t )MotorControl_task,
                (const char*    )"MotorControl_task",
                (uint16_t       )MotorControl_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )MotorControl_TASK_PRIO,
                (TaskHandle_t*  )&MotorControlTask_Handler);
    //创建Debug_task			
    xTaskCreate((TaskFunction_t )Debug_task,
                (const char*    )"Debug_task",
                (uint16_t       )Debug_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )Debug_TASK_PRIO,
                (TaskHandle_t*  )&DebugTask_Handler);
    //创建PostureControl_task
    xTaskCreate((TaskFunction_t )PostureControl_task,
                (const char*    )"PostureControl_task",
                (uint16_t       )PostureControl_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )PostureControl_TASK_PRIO,
                (TaskHandle_t*  )&PostureControlTask_Handler);
    //创建TASK4任务
    xTaskCreate((TaskFunction_t )task4_task,
                (const char*    )"task4_task",
                (uint16_t       )TASK4_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK4_TASK_PRIO,
                (TaskHandle_t*  )&Task4Task_Handler);
    //创建TASK5任务
    xTaskCreate((TaskFunction_t )task5_task,
                (const char*    )"task5_task",
                (uint16_t       )TASK5_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK5_TASK_PRIO,
                (TaskHandle_t*  )&Task5Task_Handler);

    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区

}
uint32_t Timetick1ms = 0;


void task5_task(void *pvParameters)
{

    for(;;) {

//	mpu_get_data();
//	imu_ahrs_update();
//	imu_attitude_update();
//	HAL_Delay(5);
//	printf(" Roll: %8.3lf    Pitch: %8.3lf    Yaw: %8.3lf\n", imu.rol, imu.pit, imu.yaw);
//	//HAL_UART_Transmit(&huart6, (uint8_t *)buf, (COUNTOF(buf)-1), 55);
//	HAL_Delay(5);
//
//	Servo_DOWN;
        vTaskDelay(100);
//		Servo_PEAK;

    }


//        printf("\r\ngiven_current%d given_current2=%d 温度1=%d 角度=%d\r\n ",moto_chassis[2].given_current,moto_chassis[3].given_current,moto_chassis[2].hall,moto_chassis[3].total_angle);
//        printf("\r\n t=%llu",time);
//        printf("\r\n x=%f y=%f",x,y);
    //  vTaskDelay(500);
}



void SystemClock_Config(void)
{

    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 6;
    RCC_OscInitStruct.PLL.PLLN = 180;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}


void Error_Handler(void)
{
    while(1)
    {
    }
    /* USER CODE END Error_Handler */
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
      ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */

}

#endif

/**
  * @}
  */

/**
  * @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
