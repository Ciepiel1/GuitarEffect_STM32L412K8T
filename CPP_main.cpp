/*
 * CPP_main.cpp
 *
 *  Created on: 27 lut 2024
 *      Author: qwert
 */

#include "main.h"
#include "adc.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "Button.h"
#include "CPP_main.h"

Button button(FTSW_IN_GPIO_Port, FTSW_IN_Pin);

int CPP_main()
{
	/* Initialization */

	  HAL_GPIO_WritePin(DP_CS_GPIO_Port, DP_CS_Pin, GPIO_PIN_SET);
	  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	  int r = 0;
	  int g = 0;
	  int b = 0;

	  uint8_t RDACADD = 0;
	  uint8_t SPI_Data = 0;
	  for(;r<400;r++)
	  {
		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000-r); //red
		  HAL_Delay(10);
	  }
	while (1)
	{
		SPI_Data = 0;
			HAL_GPIO_WritePin(DP_CS_GPIO_Port, DP_CS_Pin, GPIO_PIN_RESET);
			HAL_SPI_Transmit(&hspi1, &RDACADD, 1, 100);
			HAL_SPI_Transmit(&hspi1, &SPI_Data, 1, 100);
			HAL_GPIO_WritePin(DP_CS_GPIO_Port, DP_CS_Pin, GPIO_PIN_SET);

			for(;g<300;g++)
			{
			  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1000-g); //green
			  HAL_Delay(10);
			}

			  for(;b<200;b++)
			  {
				  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1000-b); //green
				  HAL_Delay(10);
			  }
			  for(;r>0;r--)
			  {
				  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000-r); //red
				  HAL_Delay(10);
			  }
			  SPI_Data = 255;
				HAL_GPIO_WritePin(DP_CS_GPIO_Port, DP_CS_Pin, GPIO_PIN_RESET);
				HAL_SPI_Transmit(&hspi1, &RDACADD, 1, 100);
				HAL_SPI_Transmit(&hspi1, &SPI_Data, 1, 100);
				HAL_GPIO_WritePin(DP_CS_GPIO_Port, DP_CS_Pin, GPIO_PIN_SET);
			  for(;g>0;g--)
			  {
				  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1000-g); //green
				  HAL_Delay(10);
			  }
			  for(;r<400;r++)
			  {
				  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000-r); //red
				  HAL_Delay(10);
			  }
			  for(;b>0;b--)
			  {
				  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1000-b); //green
				  HAL_Delay(10);
			  }

	}
}

/*Timer Interupts*/

/*
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim6)
	{
		HAL_GPIO_TogglePin(TEST_GPIO_Port,TEST_Pin);
	}
}
*/
