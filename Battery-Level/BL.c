#include "BL.h"


void BL(uint32_t val)
{
	uint8_t value[7]="x0.val=";
	uint8_t Cmd_End1[3]={0xFF,0xFF,0xFF};
	uint8_t picdel[]="vis p2,0";
	uint8_t pic[]="vis p2,1";
	uint8_t WM_SSE[]="p5.pic=6";
	
	uint8_t picdel1[]="vis p5,0";
	uint8_t pic1[]="vis p5,1";
	
	uint8_t BL_buf[4];
	uint32_t temp=val;
	BL_buf[3]=(temp%10)+48;
	temp=temp/10;
	BL_buf[2]=(temp%10)+48;
	temp=temp/10;
  BL_buf[1]=(temp%10)+48;
	temp=temp/10;
	BL_buf[0]=(temp%10)+48;
	
			//Digital
			HAL_UART_Transmit(&huart1,value,7,1000);
 			HAL_UART_Transmit(&huart1,&BL_buf[0],1,1000);
			HAL_UART_Transmit(&huart1,&BL_buf[1],1,1000);
	  	HAL_UART_Transmit(&huart1,&BL_buf[2],1,1000);
	  	HAL_UART_Transmit(&huart1,&BL_buf[3],1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End1,3,100);
	
	if(val <= 100)
	{	
				HAL_UART_Transmit(&huart1,pic,8,1000);
				HAL_UART_Transmit(&huart1,Cmd_End1,3,100);
		    counter=0;
				StartWarnningV=1;
				//display Warnning				
				HAL_UART_Transmit(&huart1,pic1,8,1000);
		  	HAL_UART_Transmit(&huart1,Cmd_End1,3,100);
				HAL_UART_Transmit(&huart1,WM_SSE,9,1000);
		  	HAL_UART_Transmit(&huart1,Cmd_End1,3,100);
		
	}
	else{
				HAL_UART_Transmit(&huart1,picdel,8,1000);
				HAL_UART_Transmit(&huart1,Cmd_End1,3,100);
	}
		
}