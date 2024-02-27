/*
 * Button.cpp
 *
 *  Created on: Feb 27, 2024
 *      Author: qwert
 */

#include "Button.h"

uint8_t Button::Debounce()
{

	uint8_t ret = DISABLE;

	state = HAL_GPIO_ReadPin(FTSW_IN_GPIO_Port, FTSW_IN_Pin);
	Debounce_timer = 0;
	this->isDebouncing = true;
	HAL_TIM_Base_Start_IT(timer_ptr);


	while(Debounce_timer<20)
	{

	}


	if(state == HAL_GPIO_ReadPin(FTSW_IN_GPIO_Port, FTSW_IN_Pin))
	{
		isDebouncing = false;
		ret = ENABLE;
	}
	else
	{
		isDebouncing = false;
		ret =  DISABLE;
		HAL_TIM_Base_Stop_IT(timer_ptr);
	}


	return ret;
}

GPIO_PinState Button::CheckState()
{
	return state;
}

uint32_t Button::GetClickTime()
{
	return Click_timer;
}

void Button::Tick()
{
	Click_timer++;
	Debounce_timer++;
}
