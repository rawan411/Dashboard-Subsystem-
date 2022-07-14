#include "Throttle.h"




void throttle_position(uint32_t val){
//END Command
uint8_t Cmd_End1[3]={0xFF,0xFF,0xFF};

	uint8_t color[8]="j0.ppic=";
	uint8_t value[7]="j0.val=";
	
	uint8_t buf_val[4];
	uint8_t green[2]="11";
	uint8_t red[2]="12";
	uint8_t yellow[2]="13";
	
	uint32_t value_slider=val/10;
	uint8_t throttle_slider[4];

	uint32_t temp;
	temp=value_slider;
	throttle_slider[3]=(temp%10)+48;
	temp=temp/10;
	throttle_slider[2]=(temp%10)+48;
	temp=temp/10;
  throttle_slider[1]=(temp%10)+48;
	temp=temp/10;
	throttle_slider[0]=(temp%10)+48;
	
	
	//value
			HAL_UART_Transmit(&huart1,value,7,1000);
 			HAL_UART_Transmit(&huart1,&throttle_slider[0],1,1000);
			HAL_UART_Transmit(&huart1,&throttle_slider[1],1,1000);
	  	HAL_UART_Transmit(&huart1,&throttle_slider[2],1,1000);
	  	HAL_UART_Transmit(&huart1,&throttle_slider[3],1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End1,3,100);
			
			
	if(value_slider<30){
			//color
		  HAL_UART_Transmit(&huart1,color,8,1000);
 			HAL_UART_Transmit(&huart1,&green[0],1,1000);
			HAL_UART_Transmit(&huart1,&green[1],1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End1,3,100);
	}else if(value_slider>=30 && value_slider<60){
			//color
		  HAL_UART_Transmit(&huart1,color,8,1000);
 			HAL_UART_Transmit(&huart1,&yellow[0],1,1000);
			HAL_UART_Transmit(&huart1,&yellow[1],1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End1,3,100);
		
	}else{
				//color
		  HAL_UART_Transmit(&huart1,color,8,1000);
 			HAL_UART_Transmit(&huart1,&red[0],1,1000);
			HAL_UART_Transmit(&huart1,&red[1],1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End1,3,100);
		
	}

}