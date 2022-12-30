/*
 * LED_Control.c
 *
 *  Created on: Dec 25, 2022
 *      Author: codek
 */

#include "main.h"

void BlinkAmberLED(void)
{
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
}

void BlinkGreenLED(void)
{
	HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
}

void BlinkBlueLED(void)
{
	HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);
}

void SetRedLED(void)
{
	HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
}

void ClearRedLED(void)
{
	HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
}
