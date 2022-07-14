#ifndef __BL__
#define __BL__

#include "stm32f1xx_hal.h"
#include "UART1.h"
#include "warnning_message.h"



/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

void BL(uint32_t val);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern uint8_t Cmd_End1[3];
#endif