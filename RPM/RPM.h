#ifndef __RPM__
#define __RPM__

#include "stm32f1xx_hal.h"
#include "UART1.h"



/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

void RPM(uint64_t val);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern uint8_t Cmd_End1[3];
#endif