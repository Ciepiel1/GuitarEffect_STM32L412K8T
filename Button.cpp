/*
 * Button.cpp
 *
 *  Created on: Feb 27, 2024
 *      Author: qwert
 */

#include "Button.h"


	GPIO_PinState Button::GetPinState()
	{
		return this->PinState;
	}

	void Button::SetPinState(GPIO_PinState P_State)
	{
		this->PinState = P_State;
	}

	ButtonState Button::GetDebouncedState()
	{
		return this->DebouncedState;
	}
	void Button::SetDebouncedState(ButtonState B_State)
	{
		this->DebouncedState = B_State;
	}

	ButtonClickState Button::GetClickState()
	{
		return this->ClickState;
	}
	void Button::SetClickState(ButtonClickState C_State)
	{
		this->ClickState = C_State;
	}




