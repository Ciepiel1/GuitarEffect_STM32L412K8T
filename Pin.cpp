/*
 * Pin.cpp
 *
 *  Created on: 7 mar 2024
 *      Author: qwert
 */

#include "Pin.h"

Pin::Pin(GPIO_TypeDef* GPIO_Port, uint16_t Num) : Port(GPIO_Port), PinNum(Num)
{

}

void Pin::Write(bool value) const
{
	HAL_GPIO_WritePin(Port, PinNum, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

GPIO_PinState Pin::Read() const
{
	return HAL_GPIO_ReadPin(Port, PinNum);
}

void Pin::Toggle() const
{
	HAL_GPIO_TogglePin(Port, PinNum);
}

uint16_t Pin::GetNum() const
{
	return PinNum;
}
