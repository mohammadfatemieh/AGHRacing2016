#include "mxconstants.h"
#include "stm32f4xx_hal.h"
#include "delay_timer6.h"

extern SPI_HandleTypeDef hspi1;

void gearDisplay_init(){

	HAL_GPIO_WritePin(GearDisplay_ChipSelect_GPIO_Port, GearDisplay_ChipSelect_Pin, GPIO_PIN_RESET);

	uint8_t val = 0b00000000;

	HAL_SPI_Transmit(&hspi1, &val, 1, 1);
	HAL_SPI_Transmit(&hspi1, &val, 1, 1);
	DelayMicroseconds(1);
	HAL_GPIO_WritePin(GearDisplay_ChipSelect_GPIO_Port, GearDisplay_ChipSelect_Pin, GPIO_PIN_SET);
	DelayMicroseconds(1);
	HAL_GPIO_WritePin(GearDisplay_ChipSelect_GPIO_Port, GearDisplay_ChipSelect_Pin, GPIO_PIN_RESET);
	DelayMicroseconds(1);
}

uint8_t digits[] = {
		0b00111111,	//0
		0b00000110,	//1
		0b01011011,	//2
		0b01001111,	//3
		0b01100110,	//4
		0b01101101,	//5
		0b01111101,	//6
		0b00000111,	//7
		0b01111111,	//8
		0b01101111 	//9
};

uint8_t dot_mask = (0b10000000);

void gearDisplay_displayDigit(uint8_t digit, uint8_t dot){
	uint8_t val = digits[digit%10];
	if (dot){
		val |= dot_mask;
	}
	HAL_SPI_Transmit(&hspi1, &val, 1, 1);
	HAL_SPI_Transmit(&hspi1, &val, 1, 1);
	DelayMicroseconds(1);
	HAL_GPIO_WritePin(GearDisplay_ChipSelect_GPIO_Port, GearDisplay_ChipSelect_Pin, GPIO_PIN_SET);
	DelayMicroseconds(1);
	HAL_GPIO_WritePin(GearDisplay_ChipSelect_GPIO_Port, GearDisplay_ChipSelect_Pin, GPIO_PIN_RESET);
	DelayMicroseconds(1);
}

void gearDisplay_offDisplay(uint8_t dot){

	uint8_t val = 0b00000000;
	if (dot){
		val |= dot_mask;
	}

	HAL_SPI_Transmit(&hspi1, &val, 1, 1);
	HAL_SPI_Transmit(&hspi1, &val, 1, 1);
	DelayMicroseconds(1);
	HAL_GPIO_WritePin(GearDisplay_ChipSelect_GPIO_Port, GearDisplay_ChipSelect_Pin, GPIO_PIN_SET);
	DelayMicroseconds(1);
	HAL_GPIO_WritePin(GearDisplay_ChipSelect_GPIO_Port, GearDisplay_ChipSelect_Pin, GPIO_PIN_RESET);
	DelayMicroseconds(1);
}
