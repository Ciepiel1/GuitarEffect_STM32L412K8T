/*
 * State.cpp
 *
 *  Created on: 8 mar 2024
 *      Author: qwert
 */

#include "State.h"
//#include <iostream>

void IdleOn::SingleClick(Menu* Menu)
{
	Menu->setState(IdleOff::getInstance());
}

void IdleOn::LongClick(Menu* Menu)
{
	Menu->setState(PresetMode::getInstance());
}

State& IdleOn::getInstance()
{
	static IdleOn singleton;
	return singleton;
}

void IdleOn::PrintState()
{
//	std::cout << "You're in the IdleOn state" << std::endl;
}

void IdleOn::SetLED()
{
	//LED::SetColor(RED);
}




void IdleOff::SingleClick(Menu* Menu)
{
	Menu->setState(IdleOn::getInstance());
}

void IdleOff::LongClick(Menu* Menu)
{
	Menu->setState(PresetMode::getInstance());
}

State& IdleOff::getInstance()
{
	static IdleOff singleton;
	return singleton;
}

void IdleOff::PrintState()
{
	//std::cout << "You're in the IdleOff state" << std::endl;
}

void IdleOff::SetLED()
{
	//LED::SetColor(RED);
}



PresetMode::PresetMode()
{
	presets_ptr = &PresetsHandle::getInstance();
	//PresetMode::setPresetsPtr(&PresetsHandle::getInstance());

}
PresetMode::~PresetMode()
{

}
void PresetMode::SingleClick(Menu* Menu)
{
	presets_ptr->NextPreset();
}

void PresetMode::LongClick(Menu* Menu)
{
	Menu->setState(EditPreset::getInstance());
}

void PresetMode::DoubleClick(Menu* Menu)
{
	presets_ptr->SaveAllPresetsToFile();
	Menu->setState(IdleOn::getInstance());
}

State& PresetMode::getInstance()
{
	static PresetMode singleton;
	return singleton;
}

void PresetMode::PrintState()
{
//	std::cout << "You're in the PresetMode state" << std::endl;
//	std::cout << "Current preset is:" << std::endl;
//	presets_ptr->getCurrentPreset()->PrintPreset();

//	presets_ptr->PrintAllPresets();
}

void PresetMode::setPresetsPtr(PresetsHandle* ptr)
{
	presets_ptr = ptr;
}

void PresetMode::SetLED()
{
	//LED::SetColor(RED);
}




EditPreset::EditPreset()
{
	presets_ptr = &PresetsHandle::getInstance();
	//EditPreset::setPresetsPtr(&PresetsHandle::getInstance());
}


EditPreset::~EditPreset()
{

}
void EditPreset::SingleClick(Menu* Menu)
{

}

void EditPreset::LongClick(Menu* Menu)
{
	presets_ptr->SaveCurrentPreset();
	Menu->setState(PresetMode::getInstance());
}

void EditPreset::DoubleClick(Menu* Menu)
{
	Menu->setState(PresetMode::getInstance());
}



State& EditPreset::getInstance()
{
	static EditPreset singleton;
	return singleton;
}

void EditPreset::PrintState()
{
//	std::cout << "You're in the EditPreset state" << std::endl;
}

void EditPreset::setPresetsPtr(PresetsHandle* ptr)
{
	presets_ptr = ptr;
}

void EditPreset::SetLED()
{
	//LED::SetColor(RED);
}
