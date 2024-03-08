/*
 * Preset.cpp
 *
 *  Created on: 8 mar 2024
 *      Author: qwert
 */

#include "Preset.h"
//#include <iostream>

Preset::Preset()
{
	for (int i = 0; i < NUM_OF_PARAMS; i++)
	{
		parameters[i] = 127;
	}
}

void Preset::PrintPreset()
{
//	std::cout << "\t Parameters:" << std::endl;
//	std::cout << "\t";
	for (int i = 0; i < NUM_OF_PARAMS; i++)
	{
//		std::cout << "\t" << parameters[i];
	}
//	std::cout << "\n";
}

void Preset::SavePreset()
{

	for (int i = 0; i < NUM_OF_PARAMS; i++)
	{
//		std::cout<< std::endl << "Enter parameter" << std::endl;
//		std::cin >> parameters[i];
	}

}

std::string Preset::getPresetString()
{
	std::string PresetLine;
	for (auto param:parameters)
	{
		PresetLine += std::to_string(param);
		PresetLine += " ";
	}
	return PresetLine;

}



PresetsHandle::PresetsHandle() : PresetList({new Preset, new Preset, new Preset, new Preset, new Preset})
{
	CurrentPresetPtr = &PresetList.front();
//	std::cout << "skonstruowano presets handle" << std::endl;
}

PresetsHandle::~PresetsHandle()
{

}

PresetsHandle& PresetsHandle::getInstance()
{
	static PresetsHandle singleton;
	return singleton;
}

void PresetsHandle::NextPreset()
{
	if (*CurrentPresetPtr != PresetList.back())
		CurrentPresetPtr++;
	else
		CurrentPresetPtr = &(PresetList.front());

//	std::cout << "Going to next preset:" << std::endl;
//	std::cout << (*CurrentPresetPtr)->getPresetString() << std::endl;
}

void PresetsHandle::PrintAllPresets()
{
//	std::cout << "LIST OF PRESETS:" << std::endl;
	for (const auto p:PresetList)
	{
//		std::cout << "Preset " << "NUM" << ":" << std::endl;
//		p->PrintPreset();
	}
}

Preset* PresetsHandle::getCurrentPreset()
{
	return *CurrentPresetPtr;
}

void PresetsHandle::SaveAllPresetsToFile()
{
	/*
	std::ofstream PresetsFile("presets.txt");
	// Write to the file
	for (auto p : PresetList)
	{
		PresetsFile << p->getPresetString()<<std::endl;
	}


	// Close the file
	PresetsFile.close();
	*/
}

void PresetsHandle::SaveCurrentPreset()
{
	(*CurrentPresetPtr)->SavePreset();
}
