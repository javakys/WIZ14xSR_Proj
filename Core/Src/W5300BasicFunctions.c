/*
 * W5300BasicFunctions.c
 *
 *  Created on: 2021. 4. 8.
 *      Author: javakys
 */

#include "main.h"
#include "W5300BasicFunctions.h"

void Reset_W5300()
{
	HAL_GPIO_WritePin(RESET_W5300_GPIO_Port, RESET_W5300_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(RESET_W5300_GPIO_Port, RESET_W5300_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
}

void W5300_write(uint32_t addr, iodata_t wd)
{
	*((uint16_t*)(addr << 1)) = wd;
}

iodata_t W5300_read(uint32_t addr)
{
	return *((uint16_t*)(addr << 1));
}

