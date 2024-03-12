/*
 * Menu.cpp
 *
 *  Created on: 8 mar 2024
 *      Author: qwert
 */

#include "Menu.h"
#include "State.h"

Menu::Menu()
{
	CurrentState = &IdleOff::getInstance();
	//presets_ptr = ptr;
}

void Menu::setState(State& newState)
{
	CurrentState = &newState;
	CurrentState->SetLED();
}


void Menu::SingleClick()
{
	CurrentState->SingleClick(this);
}

void Menu::LongClick()
{
	CurrentState->LongClick(this);
}

void Menu::DoubleClick()
{
	CurrentState->DoubleClick(this);
}


