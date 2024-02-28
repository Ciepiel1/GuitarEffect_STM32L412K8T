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

	PinState = HAL_GPIO_ReadPin(FTSW_IN_GPIO_Port, FTSW_IN_Pin);
	Debounce_timer = 0;
	this->isDebouncing = true;
	HAL_TIM_Base_Start_IT(timer_ptr);


	while(Debounce_timer<DEBOUNCE_TIME)
	{

	}


	if(PinState == HAL_GPIO_ReadPin(FTSW_IN_GPIO_Port, FTSW_IN_Pin))
	{
		isDebouncing = false;
		ret = ENABLE;
		//if(!PinState) HAL_TIM_Base_Stop_IT(timer_ptr);
	}
	else
	{
		isDebouncing = false;
		ret =  DISABLE;
		HAL_TIM_Base_Stop_IT(timer_ptr);
	}


	return ret;
}

GPIO_PinState Button::CheckPinState()
{
	return PinState;
}

ButtonState Button::CheckButtonState()
{
	return B_State;
}

void Button::UpdateButtonState(ButtonState state)
{
	B_State = state;
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

void Button::Reset()   //function stopping and reseting timers after click is recognized
{
	HAL_TIM_Base_Stop_IT(timer_ptr);
	Click_timer = 0;
	UpdateButtonState(idle);
	Debounce_timer = 30;   //workaround to stop Debouncing while loop - i can do better
}
