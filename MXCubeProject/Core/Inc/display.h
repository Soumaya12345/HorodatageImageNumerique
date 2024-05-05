/*
A STM32 Library for 8 Digits 7-Seg display by DFRobot
Based on the VK16K33 IC Driver.

File: display.h
Author: Henrique Lefundes
Created on 02/04/2024 20:06
*/

#include <stdint.h>

// Change for your I2C 
#define DISPLAY_I2C &hi2c3

// Anode/Cathode Common LEDs
#define isCathode 1

// May change depending on your model, check DFRobot documentation
#define SLAVE_ADDR 0xE0
//                 ^^^^
//             CHANGE THIS ADDR

// Setup Commands (pg. 23 documentation VK16K33)
// 0 0 1 0 X X X S
// S = 0 -> Off
// S = 1 -> On
#define VK16K33_ON 0x21
#define VK16K33_OFF 0x20

// Data Commands (pg. 24 documentation VK16K33)
// 1 0 0 0 X B1 B0 D
// D = 0 -> Display off
// D = 1 -> Display on
// B1 B0 | Blinking Frequency
// 0  0  | Off 
// 0  1  | 2Hz
// 1  0  | 1Hz
// 1  1  | 0.5Hz

#define DISPLAY_ON 0x81
#define DISPLAY_OFF 0x80
#define DISPLAY_BLINK_OFF 0x81
#define DISPLAY_BLINK_05HZ 0x87
#define DISPLAY_BLINK_1HZ 0x85
#define DISPLAY_BLINK_2HZ 0x83

// Dimming commands (pg. 25 documentation VK16K33)
// 1 1 1 0 P3 P2 P1 P0
// E       (0x-0xF)
// To change it just add something between 0x0 and 0xF
// Set brightness to 15 (max value) -> DISPLAY_BRIGHTNESS | 0xF; 
#define DISPLAY_BRIGHTNESS 0xE0

// Lookup Table for anode common
#if (isCathode == 1)
    #define PRINT_0 0x3F
    #define PRINT_1 0x06
    #define PRINT_2 0x5B
    #define PRINT_3 0x4F
    #define PRINT_4 0x66
    #define PRINT_5 0x6D
    #define PRINT_6 0x7D
    #define PRINT_7 0x07
    #define PRINT_8 0x7F
    #define PRINT_9 0x67
#else
    #define PRINT_0 0xC0
    #define PRINT_1 0xF9
    #define PRINT_2 0xA4
    #define PRINT_3 0xB0
    #define PRINT_4 0x99
    #define PRINT_5 0x92
    #define PRINT_6 0x82
    #define PRINT_7 0xF8
    #define PRINT_8 0x80
    #define PRINT_9 0x90
#endif 

void DISPLAY_Init();
void DISPLAY_WriteCMD(uint8_t cmd);
void DISPLAY_WriteData(uint8_t reg, uint8_t data);
void DISPLAY_Hour(int hour);
void DISPLAY_Minutes(int minutes);
void DISPLAY_Seconds(int seconds);
void DISPLAY_Milli(int milli);
void DISPLAY_Print(int number);
void DISPLAY_Point(uint8_t reg);
