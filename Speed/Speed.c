#include "Speed.h"

uint8_t Cmd_End2[3]={0xFF,0xFF,0xFF};

void speed(uint32_t val)
{
			uint8_t value[7]="n0.val=";
			uint8_t buf_val[4];
		
			uint32_t temp;
			temp=val;
			buf_val[3]=(temp%10)+48;
			temp=temp/10;
			buf_val[2]=(temp%10)+48;
			temp=temp/10;
			buf_val[1]=(temp%10)+48;
			temp=temp/10;
			buf_val[0]=(temp%10)+48;
	
	
			HAL_UART_Transmit(&huart1,value,7,1000);
 			HAL_UART_Transmit(&huart1,&buf_val[0],1,1000);
			HAL_UART_Transmit(&huart1,&buf_val[1],1,1000);
	  	HAL_UART_Transmit(&huart1,&buf_val[2],1,1000);
	  	HAL_UART_Transmit(&huart1,&buf_val[3],1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End2,3,100);

}