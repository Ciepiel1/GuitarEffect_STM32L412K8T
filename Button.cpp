/*
 * Button.cpp
 *
 *  Created on: Feb 27, 2024
 *      Author: qwert
 */

#include "Button.h"
#include "tim.h"
uint8_t Button::Debounce()
{
	uint8_t ret = DISABLE;
	if(!this->isDebouncing)
	{
		state = HAL_GPIO_ReadPin(FTSW_IN_GPIO_Port, FTSW_IN_Pin);
		Debounce_time_counter = 0;
		HAL_TIM_Base_Start_IT(&htim6);
		this->isDebouncing = true;
	}

	if(Debounce_time_counter == 20)
	{
		if(state == HAL_GPIO_ReadPin(FTSW_IN_GPIO_Port, FTSW_IN_Pin))
		{
			isDebouncing = false;
			ret = ENABLE;
		}
		else
		{
			isDebouncing = false;
			ret =  DISABLE;
		}
		HAL_TIM_Base_Stop_IT(&htim6);
	}
	return ret;
}
