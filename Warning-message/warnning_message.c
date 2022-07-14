
#include "warnning_message.h"


uint16_t counter;	
uint8_t StartWarnningV;

void StartWarnning(void)
{
		StartWarnningV=1;
		if(counter>=1000)
		{
				StopWarnning();
		}
		else{
			
			counter++;
		}

}


void StopWarnning(void)
{

				uint8_t Cmd_End1[3]={0xFF,0xFF,0xFF};
				uint8_t picdel[]="vis p5,0";
				uint8_t pic[]="vis p5,1";
				HAL_UART_Transmit(&huart1,picdel,8,1000);
				HAL_UART_Transmit(&huart1,Cmd_End1,3,100);
				StartWarnningV=0;

}