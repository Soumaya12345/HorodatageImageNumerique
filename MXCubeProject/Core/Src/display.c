/*
A STM32 Library for 8 Digits 7-Seg display by DFRobot
Based on the VK16K33 IC Driver.

File: display.c
Author: Henrique Lefundes
Created on 02/04/2024 20:06
*/

#include <i2c.h>
#include "display.h"

const uint8_t PRINT_VALUE[] = {PRINT_0, PRINT_1, PRINT_2, PRINT_3, PRINT_4, PRINT_5,
                        PRINT_6, PRINT_7, PRINT_8, PRINT_9};

void DISPLAY_SendCMD(uint8_t cmd){
    // This function is given by the STM32 HAL Library
	HAL_StatusTypeDef status;
    uint32_t tickstart = HAL_GetTick();
    uint32_t delta = 0;

    status = HAL_I2C_Master_Transmit(DISPLAY_I2C, SLAVE_ADDR, &cmd, 1, 100);
    /*
	do {
	} while(status == HAL_BUSY);

    if (status == HAL_OK) {
	tickstart = HAL_GetTick();
	// wait for transfer completion
		while ((HAL_I2C_GetState(DISPLAY_I2C) != HAL_I2C_STATE_READY) && (delta < I2C_TIMEOUT_TICK)) {
			delta = (HAL_GetTick() - tickstart);
			if (HAL_I2C_GetError(DISPLAY_I2C) != HAL_I2C_ERROR_NONE) {
			  break;
			}
		}
    }
    */
}

void DISPLAY_WriteData(uint8_t reg, uint8_t data){
    // For more details about why reg*2 see pg. 10 documentation VK16K33
	HAL_StatusTypeDef status;
	uint8_t message[2]; // We sent 2 8 bits messages
    message[0] = reg*2; // The first message is the cmd/addr, in this case the position
    message[1] = data; // The second is the data, in this case is the number to be shown

    status = HAL_I2C_Master_Transmit(DISPLAY_I2C, SLAVE_ADDR, message, 2, 100);
	/*
    int i = 0;
    do {
    	i++;
    } while(status == HAL_BUSY);
    i = 0;
    if (status == HAL_OK) {
		while ((HAL_I2C_GetState(DISPLAY_I2C) != HAL_I2C_STATE_READY) || (i < 5)) {
			if (HAL_I2C_GetError(DISPLAY_I2C) != HAL_I2C_ERROR_NONE) {
			  break;
			}
			i++;
		}
    }
    __NOP();
	 */
}

void DISPLAY_Clear(){
    // Should show 01234567 on Display
    for(uint8_t addr = 0; addr < 8; addr++) {
        DISPLAY_WriteData(addr, PRINT_VALUE[0]);
    }
}

void DISPLAY_Init(){
    DISPLAY_SendCMD(VK16K33_ON);
    DISPLAY_SendCMD(DISPLAY_ON);
    DISPLAY_SendCMD(DISPLAY_BLINK_OFF);
    DISPLAY_SendCMD(DISPLAY_BRIGHTNESS | 0xF);
    DISPLAY_Clear();
}

// A simplified version that only displays positive number
void DISPLAY_Print(int number){
    // Creates a vector to save all the digits of the decimal number
    int digits[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    // Supposing that number is a positive number
    if ((number < 0) | (number > 99999999)) {
        number = 0;
    }  

    // Logic to get every digit of the integer number
    for(int digit = 7; digit >= 0; digit--) {
        digits[digit] = number % 10;
        number /= 10;
    }

    // Send all the commands
    for(uint8_t addr = 0; addr < 8; addr++) {
        DISPLAY_WriteData(addr, PRINT_VALUE[digits[addr]]);
    }
}

void DISPLAY_Hour(int hour){
	int digit_1 = hour % 10;
	hour /= 10;
	int digit_2 = hour % 10;
	DISPLAY_WriteData(0x01, PRINT_VALUE[digit_1]);
	DISPLAY_WriteData(0x00, PRINT_VALUE[digit_2]);
}

void DISPLAY_Minutes(int minutes){
	int digit_1 = minutes % 10;
	minutes /= 10;
	int digit_2 = minutes % 10;
	DISPLAY_WriteData(0x03, PRINT_VALUE[digit_1]);
	DISPLAY_WriteData(0x02, PRINT_VALUE[digit_2]);
}

void DISPLAY_Seconds(int seconds){
	int digit_1 = seconds % 10;
	seconds /= 10;
	int digit_2 = seconds % 10;
	DISPLAY_WriteData(0x05, PRINT_VALUE[digit_1]);
	DISPLAY_WriteData(0x04, PRINT_VALUE[digit_2]);
}

void DISPLAY_Milli(int milli){
	int digit_1 = milli % 10;
	milli /= 10;
	int digit_2 = milli % 10;
	DISPLAY_WriteData(0x07, PRINT_VALUE[digit_1]);
	DISPLAY_WriteData(0x06, PRINT_VALUE[digit_2]);
}

void DISPLAY_Point(uint8_t reg){
	DISPLAY_WriteData(reg, 0x80);
}
