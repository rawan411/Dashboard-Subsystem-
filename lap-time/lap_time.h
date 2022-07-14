
#ifndef LAP_TIME
#define LAP_TIME

#include "stm32f1xx_hal.h"
#include "UART1.h"

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

void LAP_Time(void);

void LAST_LAP(void);

void BEST_LAP(void);

void rest_all(void);

void rest_hmi(void);

void LAPs(void);

void Gap_last_last(void);

void Gap_best_last(void);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern uint16_t mil;	
extern uint16_t sec;
extern uint16_t min;
extern uint8_t Cmd_End[3];



extern uint8_t mil_char[3];
extern uint8_t sec_char[2];
extern uint8_t min_char[2];
extern uint8_t buf3;
extern uint8_t buf4;
extern uint8_t buf5;

//LAST LAP
extern uint16_t last_mil;
extern uint16_t last_sec;
extern uint16_t last_min;

//best lap
extern uint16_t best_mil;
extern uint16_t best_sec;
extern uint16_t best_min;



extern uint32_t first;
extern uint32_t reset3sec;
 
//best lap
extern uint8_t flag;

//laps
extern uint16_t laps;
#endif
