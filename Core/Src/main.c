/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#include "lap_time.h"
#include "RPM.h"
#include "UART1.h"
#include "Speed.h"
#include "can_Rx.h"
#include "warnning_message.h"
#include "Throttle.h"
#include "BL.h"


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


TIM_HandleTypeDef htim3;

//UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


	uint8_t *RX_message;


uint32_t delay=0;
  uint32_t zeroFlag;
	uint32_t highFlag;   
	
	uint32_t zero;
	uint32_t high;  
	uint8_t pic[]="vis t7,0";
	uint8_t picdel[]="vis t7,1";
	uint32_t first1=0;


void start_stop_button(void)
{
	
	
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==1){
					zeroFlag=0;
			}
			//falling edge
			else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0 && zeroFlag==0){
				zeroFlag=1;
				highFlag=0;
				if(first1==0)
				{
					first1=1;
					HAL_TIM_Base_Start_IT(&htim3);
				}
				else
				{
					Gap_best_last();
					Gap_last_last();
					
					BEST_LAP();
					LAST_LAP();
					laps++;
					LAPs();
					sec=0;	
          min=0;
          mil=0;
				}
				
			}
			//rising edge
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==1 && highFlag==0){
					highFlag=1;
			}
		
	
}

void reset_button(void)
{
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)==1){
					zero=0;
			}
			//falling edge
			else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)==0 && zero==0){
			  zero=1;
				high=0; 
        sec=0;	
        min=0;
        mil=0;
        last_sec=0;
        last_min=0;
				last_mil=0;
				rest_all();
			}
			//rising edge
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)==1 && high==0){			
				high=1;
			}

}

void StartStop(uint8_t SSS)
{
	uint8_t Cmd_End1[3]={0xFF,0xFF,0xFF};
	uint8_t SSSON[]="p4.pic=20";
	uint8_t SSSOFF[]="p4.pic=21";
		if(SSS==1)
		{
			HAL_UART_Transmit(&huart1,SSSON,9,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
		}else{
			HAL_UART_Transmit(&huart1,SSSOFF,9,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
		}
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
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Init(&huart1);
	 
	
	//uint16_t value;
  
	 HAL_UART_Receive(&huart1,RX_message,1,1000);

	
	rest_hmi();
	CAN_Config_filter();
	HAL_CAN_ActivateNotification(&hcan,CAN_IT_RX_FIFO0_MSG_PENDING);
	HAL_CAN_Start(&hcan);
	
	//HAL_UART_Transmit(&huart1,picdel,8,1000);
	//HAL_UART_Transmit(&huart1,Cmd_End,3,100);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t draw[5]="cirs ";
	uint8_t Red[3]="RED";
	uint8_t black[5]="BLACK";
	uint8_t buf4=',';
	uint8_t buf5=' ';
	uint8_t buf6[2]="2,";
	uint8_t buf_val[4];
	uint32_t temp;
	
  while (1)
  {
		
		StartStop(0);
		
		RPM(6000);
		throttle_position(100);
		BL(100);
		
//		for(int i=0;i<300;i=i+4){
//			
//			temp=i;
//			buf_val[3]=(temp%10)+48;
//			temp=temp/10;
//			buf_val[2]=(temp%10)+48;
//			temp=temp/10;
//			buf_val[1]=(temp%10)+48;
//			temp=temp/10;
//			buf_val[0]=(temp%10)+48;
//		 
//			HAL_UART_Transmit(&huart1,draw,5,1000);
//			//HAL_UART_Transmit(&huart1,&buf5,1,1000);
//			HAL_UART_Transmit(&huart1,&buf_val[0],1,1000);
//			HAL_UART_Transmit(&huart1,&buf_val[1],1,1000);
//	  	HAL_UART_Transmit(&huart1,&buf_val[2],1,1000);
//	  	HAL_UART_Transmit(&huart1,&buf_val[3],1,1000);
//			HAL_UART_Transmit(&huart1,&buf4,1,1000);
//			HAL_UART_Transmit(&huart1,&buf_val[0],1,1000);
//			HAL_UART_Transmit(&huart1,&buf_val[1],1,1000);
//	  	HAL_UART_Transmit(&huart1,&buf_val[2],1,1000);
//	  	HAL_UART_Transmit(&huart1,&buf_val[3],1,1000);
//			HAL_UART_Transmit(&huart1,&buf4,1,1000);
//			HAL_UART_Transmit(&huart1,buf6,2,1000);
//			HAL_UART_Transmit(&huart1,Red,3,1000);
//			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
//			HAL_Delay(100);
//			
//			HAL_UART_Transmit(&huart1,draw,5,1000);
//			//HAL_UART_Transmit(&huart1,&buf5,1,1000);
//			HAL_UART_Transmit(&huart1,&buf_val[0],1,1000);
//			HAL_UART_Transmit(&huart1,&buf_val[1],1,1000);
//	  	HAL_UART_Transmit(&huart1,&buf_val[2],1,1000);
//	  	HAL_UART_Transmit(&huart1,&buf_val[3],1,1000);
//			HAL_UART_Transmit(&huart1,&buf4,1,1000);
//			HAL_UART_Transmit(&huart1,&buf_val[0],1,1000);
//			HAL_UART_Transmit(&huart1,&buf_val[1],1,1000);
//	  	HAL_UART_Transmit(&huart1,&buf_val[2],1,1000);
//	  	HAL_UART_Transmit(&huart1,&buf_val[3],1,1000);
//			HAL_UART_Transmit(&huart1,&buf4,1,1000);
//			HAL_UART_Transmit(&huart1,buf6,2,1000);
//			HAL_UART_Transmit(&huart1,black,5,1000);
//			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
//			}
//			
}
	
		  
		
		  
		
//		for(int i=0;i<=100;i++)
//		{
//			RPM(i);
//		}
	
//					if(sec==1)
//					{
//						HAL_UART_Transmit(&huart1,pic,8,1000);
//						HAL_UART_Transmit(&huart1,Cmd_End,3,100);
//						
//					}else if(sec==4)
//					{
//								HAL_UART_Transmit(&huart1,picdel,8,1000);
//								HAL_UART_Transmit(&huart1,Cmd_End,3,100);
//					}
		
////////////		start_stop_button();
////////////		reset_button();

		
			
//reset Alllllllll/////////////////////////////////////////////////
			
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
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
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 4;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_15TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 7200-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 10-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

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
  huart1.Init.BaudRate = 921600;
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

  /*Configure GPIO pins : PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{ 
	  if(htim==&htim3){
			 LAP_Time(); 

				if(StartWarnningV==1)
				{
					StartWarnning();
				}
			
	  if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0)
	  {
		   if(reset3sec==3)
		 {
		   rest_all();
			 reset3sec=0;
			 delay++;
		 }
	  }
			 
		}
}


volatile CAN_RxHeaderTypeDef CANRxHeader;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	uint8_t ReceivedCANMessage[8];
	if(HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&CANRxHeader,ReceivedCANMessage)==HAL_OK)
	{
	
	}
	
	//Endurance Autocross
	if(*RX_message==0x30 || *RX_message==0x31)
	{
				//ECU RPM, Temp, Throttle
				if(CANRxHeader.StdId==0x50)
				{
					//RPM calculations 
					uint8_t RPM_ECU[2];
					RPM_ECU[0]=ReceivedCANMessage[0];
					RPM_ECU[1]=ReceivedCANMessage[1];
					uint64_t rpm= ((RPM_ECU[0]<<8) | RPM_ECU[1]);
					RPM(rpm);
					
					//Battery Level Calculations
					uint32_t Battery_level=ReceivedCANMessage[2];
					BL(Battery_level);
					
					//Temp Calculations
					uint8_t temp[2];
					temp[0]=ReceivedCANMessage[3];
					temp[1]=ReceivedCANMessage[4];
					
					//throttle Position Calculations
					uint8_t throttle[2];
					throttle[0]=ReceivedCANMessage[5];
					throttle[1]=ReceivedCANMessage[6];
					uint32_t throttleVar= ((throttle[0]<<8) | throttle[1]);
					throttle_position(throttleVar);
					
					
					
				}
				//DAQ IMU Euler Angle
				else if (CANRxHeader.StdId==0x51)
				{
						
				}
				//DAQ IMU ACC
				else if (CANRxHeader.StdId==0x52)
				{
				
				}	
				//Steering, break switch, Speed
				else if (CANRxHeader.StdId==0x53)
				{
					uint8_t Steering[2];
					Steering[0]=ReceivedCANMessage[0];
					Steering[1]=ReceivedCANMessage[1];
					uint8_t Break_switch=ReceivedCANMessage[2];
					uint8_t Speed[2];
					Speed[0]=ReceivedCANMessage[3];
					Speed[1]=ReceivedCANMessage[4];
					
					uint32_t speedVar=((Speed[0]<<8)|Speed[1]);
					speed(speedVar);
					
				}
				//Wheel RPM
				else if (CANRxHeader.StdId==0x54)
				{
				
				}
				//4 travel 
				else if (CANRxHeader.StdId==0x55)
				{
				
				}
				//Symbol SSE
				else if (CANRxHeader.StdId==0x70)
				{
						uint8_t SSS=ReceivedCANMessage[0];
						StartStop(SSS);
						
				}
				//WM SSE
				else if (CANRxHeader.StdId==0x71)
				{
							uint8_t Cmd_End1[3]={0xFF,0xFF,0xFF};
							uint8_t WM_SSE[]="p5.pic=24";
							uint8_t picdel[]="vis p5,0";
							uint8_t pic[]="vis p5,1";
							//display Warnning				
							HAL_UART_Transmit(&huart1,pic,8,1000);
							HAL_UART_Transmit(&huart1,Cmd_End,3,100);
							HAL_UART_Transmit(&huart1,WM_SSE,9,1000);
							HAL_UART_Transmit(&huart1,Cmd_End,3,100);
							counter=0;
							StartWarnningV=1;
									
				}
				//WM ECU
				else if (CANRxHeader.StdId==0x72)
				{ 
							uint8_t Cmd_End1[3]={0xFF,0xFF,0xFF};
							uint8_t WM_ECU[]="p5.pic=23";
							uint8_t picdel[]="vis p5,0";
							uint8_t pic[]="vis p5,1";
							HAL_UART_Transmit(&huart1,pic,8,1000);
							HAL_UART_Transmit(&huart1,Cmd_End,3,100);
							HAL_UART_Transmit(&huart1,WM_ECU,9,1000);
							HAL_UART_Transmit(&huart1,Cmd_End,3,100);
							counter=0;
							StartWarnningV=1;
				}

	}
	//Acceleration 
	else if(*RX_message==0x32)
	{
			//ECU RPM, Temp, Throttle
				if(CANRxHeader.StdId==0x50)
				{
					
				}
				//DAQ IMU Euler Angle
				else if (CANRxHeader.StdId==0x51)
				{
						
				}
				//DAQ IMU ACC
				else if (CANRxHeader.StdId==0x52)
				{
				
				}	
				//Steering, break switch, Speed
				else if (CANRxHeader.StdId==0x53)
				{

				}
				//Wheel RPM
				else if (CANRxHeader.StdId==0x54)
				{
				
				}
				//4 travel 
				else if (CANRxHeader.StdId==0x55)
				{
				
				}
				//Symbol SSE
				else if (CANRxHeader.StdId==0x70)
				{
						
				}
				//WM SSE
				else if (CANRxHeader.StdId==0x71)
				{
									
				}
				//WM ECU
				else if (CANRxHeader.StdId==0x72)
				{ 

				}

	}
	//Skidpad
	else
	{
				//ECU RPM, Temp, Throttle
				if(CANRxHeader.StdId==0x50)
				{
					
				}
				//DAQ IMU Euler Angle
				else if (CANRxHeader.StdId==0x51)
				{
						
				}
				//DAQ IMU ACC
				else if (CANRxHeader.StdId==0x52)
				{
				
				}	
				//Steering, break switch, Speed
				else if (CANRxHeader.StdId==0x53)
				{

				}
				//Wheel RPM
				else if (CANRxHeader.StdId==0x54)
				{
				
				}
				//4 travel 
				else if (CANRxHeader.StdId==0x55)
				{
				
				}
				//Symbol SSE
				else if (CANRxHeader.StdId==0x70)
				{
						
				}
				//WM SSE
				else if (CANRxHeader.StdId==0x71)
				{
									
				}
				//WM ECU
				else if (CANRxHeader.StdId==0x72)
				{ 

				}
	}
	
	
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
