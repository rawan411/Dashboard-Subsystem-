#ifndef __CAN__
#define __CAN__

#include "stm32f1xx_hal.h"
#include "UART1.h"



/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

void CAN_Config_filter();

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern CAN_FilterTypeDef filter;
#endif