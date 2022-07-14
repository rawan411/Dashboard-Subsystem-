#include "lap_time.h"

uint16_t mil=0;	
uint16_t sec=0;
uint16_t min=0;
uint8_t Cmd_End[3]={0xFF,0xFF,0xFF};



uint8_t mil_char[3];
uint8_t sec_char[2];
uint8_t min_char[2];
uint8_t buf3='\"';
uint8_t buf4=':';
uint8_t buf5='.';

//LAST LAP
uint16_t last_mil;
uint16_t last_sec;
uint16_t last_min;

//best lap
uint16_t best_mil;
uint16_t best_sec;
uint16_t best_min;



uint32_t first=0;
uint32_t reset3sec=0;

//best lap
uint8_t flag=1;

//laps
uint16_t laps;
void LAP_Time(void){
	
	 uint8_t buf2[8]="t9.txt=\"";
	 
   uint32_t temp;
	 
	  mil=mil+1;
		if(mil>=1000){
		    mil=0;
			  sec++;
			  reset3sec++;
		}else if(sec>=60){
  			sec=0;
				min++;
		} 
			 temp=mil;
			 mil_char[2]=(temp%10)+48;
			 temp=temp/10;
			 mil_char[1]=(temp%10)+48;
			 temp=temp/10;
			 mil_char[0]=(temp%10)+48;
			 temp=sec;
			 sec_char[1]=(temp%10)+48;
			 temp=temp/10;
			 sec_char[0]=(temp%10)+48;
			 temp=min;
		 	 min_char[1]=(temp%10)+48;
			 temp=temp/10;
			 min_char[0]=(temp%10)+48;
			
      HAL_UART_Transmit(&huart1,buf2,8,1000);
			HAL_UART_Transmit(&huart1,&min_char[0],1,1000);
			HAL_UART_Transmit(&huart1,&min_char[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf4,1,1000);
			HAL_UART_Transmit(&huart1,&sec_char[0],1,1000);
			HAL_UART_Transmit(&huart1,&sec_char[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf5,1,1000);
	    HAL_UART_Transmit(&huart1,&mil_char[0],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char[1],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char[2],1,1000);
			HAL_UART_Transmit(&huart1,&buf3,1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			
			//start_stop_button();
}
void LAST_LAP(void){
			uint8_t buf2[9]="t10.txt=\"";
	    
			last_mil=mil;
	    last_sec=sec;
			last_min=min;
	
	    HAL_UART_Transmit(&huart1,buf2,9,1000);
	  	HAL_UART_Transmit(&huart1,&min_char[0],1,1000);
			HAL_UART_Transmit(&huart1,&min_char[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf4,1,1000);
			HAL_UART_Transmit(&huart1,&sec_char[0],1,1000);
			HAL_UART_Transmit(&huart1,&sec_char[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf5,1,1000);
	    HAL_UART_Transmit(&huart1,&mil_char[0],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char[1],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char[2],1,1000);
			HAL_UART_Transmit(&huart1,&buf3,1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);

}

void BEST_LAP(void){

	uint8_t best=0;
	uint8_t buf2[9]="t11.txt=\"";
	
	//first time
	if(flag)
	{
		  best=1;
	}else	if(min<best_min)
	{
		best=1;
	}else if((sec<best_sec)&&(min == best_min)){
		best=1;
	}else if((mil<best_mil)&&(min==best_min)&&(sec == best_sec)){
		best=1;
	}
	
	if(best){
		  best_mil=mil;
		  best_sec=sec;
		  best_min=min;
	  	HAL_UART_Transmit(&huart1,buf2,9,1000);
			HAL_UART_Transmit(&huart1,&min_char[0],1,1000);
			HAL_UART_Transmit(&huart1,&min_char[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf4,1,1000);
			HAL_UART_Transmit(&huart1,&sec_char[0],1,1000);
			HAL_UART_Transmit(&huart1,&sec_char[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf5,1,1000);
	    HAL_UART_Transmit(&huart1,&mil_char[0],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char[1],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char[2],1,1000);
			HAL_UART_Transmit(&huart1,&buf3,1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
	}
	flag=0;
}

void rest_all(void){
    uint8_t buf2[8]="t9.txt=\"";
	  uint8_t bu[9]="t10.txt=\"";
	  uint8_t b[9]="t11.txt=\"";
	
        sec=0;	
        min=0;
        mil=0;
        last_sec=0;
        last_min=0;
				last_mil=0;
	      flag=1;
      	first=0;
	
	
				uint8_t mil_char1[3];
				uint8_t sec_char1[2];
				uint8_t min_char1[2];
			//lap_time reset
	     uint16_t temp;
       temp=0;
			 mil_char1[2]=(temp%10)+48;
			 temp=temp/10;
			 mil_char1[1]=(temp%10)+48;
			 temp=temp/10;
			 mil_char1[0]=(temp%10)+48;
			 temp=0;
			 sec_char1[1]=(temp%10)+48;
			 temp=temp/10;
			 sec_char1[0]=(temp%10)+48;
			 temp=0;
		 	 min_char1[1]=(temp%10)+48;
			 temp=temp/10;
			 min_char1[0]=(temp%10)+48;
			
			
			
			HAL_UART_Transmit(&huart1,buf2,8,1000);
			HAL_UART_Transmit(&huart1,&min_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&min_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf4,1,1000);
			HAL_UART_Transmit(&huart1,&sec_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&sec_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf5,1,1000);
	    HAL_UART_Transmit(&huart1,&mil_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char1[2],1,1000);
			HAL_UART_Transmit(&huart1,&buf3,1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			
			//last lap
			HAL_UART_Transmit(&huart1,bu,9,1000);
			HAL_UART_Transmit(&huart1,&min_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&min_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf4,1,1000);
			HAL_UART_Transmit(&huart1,&sec_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&sec_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf5,1,1000);
	    HAL_UART_Transmit(&huart1,&mil_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char1[2],1,1000);
			HAL_UART_Transmit(&huart1,&buf3,1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			
			//best lap
			HAL_UART_Transmit(&huart1,b,9,1000);
 			HAL_UART_Transmit(&huart1,&min_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&min_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf4,1,1000);
			HAL_UART_Transmit(&huart1,&sec_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&sec_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf5,1,1000);
	    HAL_UART_Transmit(&huart1,&mil_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char1[2],1,1000);
			HAL_UART_Transmit(&huart1,&buf3,1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			
			uint8_t gap_last[14]="t6.txt=\"+0.00\"";
			HAL_UART_Transmit(&huart1,gap_last,14,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			
			uint8_t gap_best[14]="t5.txt=\"+0.00\"";
			HAL_UART_Transmit(&huart1,gap_best,14,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
}


void rest_hmi(void){
    uint8_t buf2[8]="t9.txt=\"";
	  uint8_t bu[9]="t10.txt=\"";
	  uint8_t b[9]="t11.txt=\"";
	
        sec=0;	
        min=0;
        mil=0;
        last_sec=0;
        last_min=0;
				last_mil=0;
	      flag=1;
      	first=0;
	
	
				uint8_t mil_char1[3];
				uint8_t sec_char1[2];
				uint8_t min_char1[2];
			//lap_time reset
	     uint16_t temp;
       temp=0;
			 mil_char1[2]=(temp%10)+48;
			 temp=temp/10;
			 mil_char1[1]=(temp%10)+48;
			 temp=temp/10;
			 mil_char1[0]=(temp%10)+48;
			 temp=0;
			 sec_char1[1]=(temp%10)+48;
			 temp=temp/10;
			 sec_char1[0]=(temp%10)+48;
			 temp=0;
		 	 min_char1[1]=(temp%10)+48;
			 temp=temp/10;
			 min_char1[0]=(temp%10)+48;
			
			
			
			HAL_UART_Transmit(&huart1,buf2,8,1000);
			HAL_UART_Transmit(&huart1,&min_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&min_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf4,1,1000);
			HAL_UART_Transmit(&huart1,&sec_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&sec_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf5,1,1000);
	    HAL_UART_Transmit(&huart1,&mil_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char1[2],1,1000);
			HAL_UART_Transmit(&huart1,&buf3,1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			
			//last lap
			HAL_UART_Transmit(&huart1,bu,9,1000);
			HAL_UART_Transmit(&huart1,&min_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&min_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf4,1,1000);
			HAL_UART_Transmit(&huart1,&sec_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&sec_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf5,1,1000);
	    HAL_UART_Transmit(&huart1,&mil_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char1[2],1,1000);
			HAL_UART_Transmit(&huart1,&buf3,1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			
			//best lap
			HAL_UART_Transmit(&huart1,b,9,1000);
 			HAL_UART_Transmit(&huart1,&min_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&min_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf4,1,1000);
			HAL_UART_Transmit(&huart1,&sec_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&sec_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf5,1,1000);
	    HAL_UART_Transmit(&huart1,&mil_char1[0],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char1[1],1,1000);
			HAL_UART_Transmit(&huart1,&mil_char1[2],1,1000);
			HAL_UART_Transmit(&huart1,&buf3,1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			
			uint8_t gap_last[14]="t6.txt=\"+0.00\"";
			HAL_UART_Transmit(&huart1,gap_last,14,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			
			uint8_t gap_best[14]="t5.txt=\"+0.00\"";
			HAL_UART_Transmit(&huart1,gap_best,14,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			
			uint8_t gaps[8]="n2.val=0";
			HAL_UART_Transmit(&huart1,gaps,8,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
}


void LAPs(void){
			uint8_t buf[7]="n2.val=";
			uint8_t laps_char[2];
	
	    uint16_t temp=laps;
			 laps_char[1]=(temp%10)+48;
			 temp=temp/10;
			 laps_char[0]=(temp%10)+48;
			
			
			HAL_UART_Transmit(&huart1,buf,7,1000);
	    HAL_UART_Transmit(&huart1,&laps_char[0],1,1000);
			HAL_UART_Transmit(&huart1,&laps_char[1],1,1000);
	
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
}

void Gap_last_last(void){

	 int16_t gap_min;
	 int16_t gap_sec;
	 int32_t gap_mil;

	uint8_t milgapchar[3];
	uint8_t secgapchar[2];
	uint8_t mingapchar[2];
	
	 uint8_t sign;
	 uint8_t buf[8]="t6.txt=\"";
	
	
	gap_min=min-last_min;
	gap_sec=sec-last_sec;
	gap_mil=mil-last_mil;

	int32_t milSecs;
	
	milSecs=gap_min*(60*1000)+gap_sec*1000+gap_mil;
	if(milSecs<0)
	{
		sign=0x2B;
		milSecs=milSecs*(-1);
	}
	else
	{
		sign = 0x2D;
	}
	
	gap_sec=milSecs/1000;
	gap_min=gap_sec/60;
	gap_sec=gap_sec-gap_min*60;
	gap_mil=milSecs-gap_min*(60*1000)-gap_sec*1000;
	
	uint16_t temp;
	
	HAL_UART_Transmit(&huart1,buf,8,1000);
	HAL_UART_Transmit(&huart1,&sign,1,1000);
	
	if(gap_min!=0)
	{
		temp=gap_min;
	  mingapchar[1]=(temp%10)+48;
		temp=temp/10;
		mingapchar[0]=(temp%10)+48;
	
		HAL_UART_Transmit(&huart1,&mingapchar[0],1,1000);
		HAL_UART_Transmit(&huart1,&mingapchar[1],1,1000);
		HAL_UART_Transmit(&huart1,&buf4,1,1000);
	}
	
	
		temp=gap_sec;
	  secgapchar[1]=(temp%10)+48;
		temp=temp/10;
		secgapchar[0]=(temp%10)+48;
	
	if(secgapchar[0]!='0')
	{
			HAL_UART_Transmit(&huart1,&secgapchar[0],1,1000);
	}
	
			
	  temp=gap_mil;
	  milgapchar[2]=(temp%10)+48;
		temp=temp/10;
		milgapchar[1]=(temp%10)+48;
	  temp=temp/10;
		milgapchar[0]=(temp%10)+48;
	
			
			HAL_UART_Transmit(&huart1,&secgapchar[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf5,1,1000);
	
		
	    HAL_UART_Transmit(&huart1,&milgapchar[0],1,1000);
			HAL_UART_Transmit(&huart1,&milgapchar[1],1,1000);
			HAL_UART_Transmit(&huart1,&milgapchar[2],1,1000);
			HAL_UART_Transmit(&huart1,&buf3,1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
	
}

void Gap_best_last(void)
{
	int16_t gap_min;
	 int16_t gap_sec;
	 int32_t gap_mil;

	uint8_t milgapchar[3];
	uint8_t secgapchar[2];
	uint8_t mingapchar[2];
	
	 uint8_t sign;
	 uint8_t buf[8]="t5.txt=\"";
	
	
	gap_min=min-best_min;
	gap_sec=sec-best_sec;
	gap_mil=mil-best_mil;

	int32_t milSecs;
	
	milSecs=gap_min*(60*1000)+gap_sec*1000+gap_mil;
	if(milSecs<0)
	{
		sign=0x2B;
		milSecs=milSecs*(-1);
	}
	else
	{
		sign = 0x2D;
	}
	
	gap_sec=milSecs/1000;
	gap_min=gap_sec/60;
	gap_sec=gap_sec-gap_min*60;
	gap_mil=milSecs-gap_min*(60*1000)-gap_sec*1000;
	
	uint16_t temp;
	
	HAL_UART_Transmit(&huart1,buf,8,1000);
	HAL_UART_Transmit(&huart1,&sign,1,1000);
	
	if(gap_min!=0)
	{
		temp=gap_min;
	  mingapchar[1]=(temp%10)+48;
		temp=temp/10;
		mingapchar[0]=(temp%10)+48;
	
		HAL_UART_Transmit(&huart1,&mingapchar[0],1,1000);
		HAL_UART_Transmit(&huart1,&mingapchar[1],1,1000);
		HAL_UART_Transmit(&huart1,&buf4,1,1000);
	}
	
	
		temp=gap_sec;
	  secgapchar[1]=(temp%10)+48;
		temp=temp/10;
		secgapchar[0]=(temp%10)+48;
	if(secgapchar[0]!='0')
	{
			HAL_UART_Transmit(&huart1,&secgapchar[0],1,1000);
	}
			
	  temp=gap_mil;
	  milgapchar[2]=(temp%10)+48;
		temp=temp/10;
		milgapchar[1]=(temp%10)+48;
	  temp=temp/10;
		milgapchar[0]=(temp%10)+48;
	
		
			HAL_UART_Transmit(&huart1,&secgapchar[1],1,1000);
			HAL_UART_Transmit(&huart1,&buf5,1,1000);
	
		
	    HAL_UART_Transmit(&huart1,&milgapchar[0],1,1000);
			HAL_UART_Transmit(&huart1,&milgapchar[1],1,1000);
			HAL_UART_Transmit(&huart1,&milgapchar[2],1,1000);
			HAL_UART_Transmit(&huart1,&buf3,1,1000);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
			HAL_UART_Transmit(&huart1,Cmd_End,3,100);
	

}