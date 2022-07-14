#ifndef WARNNING_MESSAGE
#define WARNNING_MESSAGE

#include "stm32f1xx_hal.h"
#include "UART1.h"

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

void StartWarnning(void);


void StopWarnning(void);


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern uint16_t counter;	
extern uint8_t StartWarnningV;

#endif
