#include "can_Rx.h"
#include "stm32f1xx_hal.h"


CAN_FilterTypeDef filter;
void CAN_Config_filter()
{
	filter.FilterActivation=CAN_FILTER_ENABLE;
	filter.FilterFIFOAssignment=CAN_FilterFIFO0;
	filter.FilterScale=CAN_FILTERSCALE_32BIT;
	filter.FilterMode=CAN_FILTERMODE_IDMASK;
	filter.FilterMaskIdLow=0;
	filter.FilterMaskIdHigh=0;
	filter.FilterIdHigh=0;
	filter.FilterIdLow=0;
	filter.FilterBank=0;
	filter.SlaveStartFilterBank=0;
	HAL_CAN_ConfigFilter(&hcan,&filter);
}

