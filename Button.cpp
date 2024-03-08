/*
 * Button.cpp
 *
 *  Created on: Feb 27, 2024
 *      Author: qwert
 */

#include "Button.h"
#include "Pin.h"

	Button::Button(GPIO_TypeDef* GPIO_Port, uint16_t Num) : ButtonPin(GPIO_Port, Num)
	{

	}

	uint16_t Button::GetPinNum() const
	{
		return ButtonPin.GetNum();
	}


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

	void Button::MainLoopClickingRoutine()
	{
		if(this->GetDebouncedState() == Confirmed_HIGH && this->GetClickState() == idle)
			  {
			this->SetClickState(first_pressed);
				  this->Click_timer = 0;
				  HAL_TIM_Base_Start_IT(this->Timer_ptr);
			  }
			  else if(this->GetDebouncedState() == Confirmed_LOW && this->GetClickState() == first_pressed)
			  {
				  this->SetClickState(first_released);
			  }
			  else if(this->GetClickState() == first_released && this->GetDebouncedState() == Confirmed_HIGH)
			  {
				  HAL_TIM_Base_Stop_IT(this->Timer_ptr);
				  this->SetClickState(DOUBLE_CLICK);
				  //perform DoubleClick
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1000-200);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1000); //green
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000); //red

					this->SetClickState(handled);
			  }
			  else if(this->GetClickState() == LONG_CLICK)
			  {
				  //perform LongClick
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1000);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1000-200); //green
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000); //red
					this->SetClickState(handled);
			  }
			  else if(this->GetClickState() == SINGLE_CLICK)
			  {
				  //perform SingleClick
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1000);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1000); //green
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000-200); //red
					this->SetClickState(handled);
			  }
			  else if(this->GetClickState() == handled && this->GetDebouncedState() == Confirmed_LOW)
			  {
				  this->SetClickState(idle);
			  }
	}




	void Button::DebouncingRoutine()
	{
		this->Debounce_timer++;
		if(this->Debounce_timer >= DEBOUNCE_TIME)
		{
			if(this->GetPinState() == ButtonPin.Read())
			{
				this->SetDebouncedState(this->GetPinState() ? Confirmed_HIGH : Confirmed_LOW);
			}

			//HAL_TIM_Base_Stop_IT(MainButton.Debounce_timer_ptr);
			this->isDebouncing = false;

		}
	}

	void Button::ClickTimingRoutine()
	{
		this->Click_timer++;
		if(this->GetClickState() == first_pressed && this->Click_timer >= LONG_CLICK_TIME)
		{
			HAL_TIM_Base_Stop_IT(this->Timer_ptr);
			this->SetClickState(LONG_CLICK);
		}
		else if(this->GetClickState() == first_released && this->Click_timer >= DOUBLE_CLICK_TIME)
		{
			HAL_TIM_Base_Stop_IT(this->Timer_ptr);
			this->SetClickState(SINGLE_CLICK);
		}
	}


	void Button::StartDebouncing()
	{
		if(!this->isDebouncing)
		{
			this->SetPinState(this->ButtonPin.Read());
			//MainButton.SetPinState(HAL_GPIO_ReadPin(FTSW_IN_GPIO_Port, FTSW_IN_Pin));
			this->Debounce_timer = 0;
			this->isDebouncing = true;
			HAL_TIM_Base_Start_IT(this->Timer_ptr);
		}
	}

