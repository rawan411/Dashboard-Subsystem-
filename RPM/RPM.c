#include "RPM.h"

//END Command
uint8_t Cmd_End1[3]={0xFF,0xFF,0xFF};

void RPM(uint64_t val){
	uint8_t color[8]="j3.ppic=";
	uint8_t value[7]="j3.val=";
	
	
	uint8_t RPM_digital[7]="n3.val=";
	uint8_t buf_val[8];
	uint8_t green[2]="14";
	uint8_t red[2]="15";
	uint8_t yellow[2]="16";
	
	uint32_t value_slider=val/150;
	uint8_t RPM_slider[4];
	uint64_t temp;
	temp=val;
	buf_val[7]=(temp%10)+48;
	temp=temp/10;
	buf_val[6]=(temp%10)+48;
	temp=temp/10;
	buf_val[5]=(temp%10)+48;
	temp=temp/10;
	buf_val[4]=(temp%10)+48;
	temp=temp/10;
	buf_val[3]=(temp%10)+48;
	temp=temp/10;
	buf_val[2]=(temp%10)+48;
	temp=temp/10;
  buf_val[1]=(temp%10)+48;
	temp=temp/10;
	buf_val[0]=(temp%10)+48;
	
	
	
	temp=value_slider;
	RPM_slider[3]=(temp%10)+48;
	temp=temp/10;
	RPM_slider[2]=(temp%10)+48;
	temp=temp/10;
  RPM_slider[1]=(temp%10)+48;
	temp=temp/10;
	RPM_slider[0]=(temp%10)+48;
	
	    //Digital
			HAL_UART_Transmit(&huart1,RPM_digital,7,1000);
 			HAL_UART_Transmit(&huart1,&buf_val[0],1,1000);
			HAL_UART_Transmit(&huart1,&buf_val[1],1,1000);
	  	HAL_UART_Transmit(&huart1,&buf_val[2],1,1000);
	  	HAL_UART_Transmit(&huart1,&buf_val[3],1,1000);
			HAL_UART_Transmit(&huart1,&buf_val[4],1,1000);
			HAL_UART_Transmit(&huart1,&buf_val[5],1,1000);
	  	HAL_UART_Transmit(&huart1,&buf_val[6],1,1000);
	  	HAL_UART_Transmit(&huart1,&buf_val[7],1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End1,3,100);
	
	
			//value
			HAL_UART_Transmit(&huart1,value,7,1000);
 			HAL_UART_Transmit(&huart1,&RPM_slider[0],1,1000);
			HAL_UART_Transmit(&huart1,&RPM_slider[1],1,1000);
	  	HAL_UART_Transmit(&huart1,&RPM_slider[2],1,1000);
	  	HAL_UART_Transmit(&huart1,&RPM_slider[3],1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End1,3,100);
			
			
	if(val<6000){
			//color
		  HAL_UART_Transmit(&huart1,color,8,1000);
 			HAL_UART_Transmit(&huart1,&green[0],1,1000);
			HAL_UART_Transmit(&huart1,&green[1],1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End1,3,100);
	}else if(val>=6000 && val<10000){
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