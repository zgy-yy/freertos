//
// Created by acer-zgy on 2023/11/13.
//

#ifndef LCD_H
#define LCD_H
#include "stm32f1xx.h"

#define X_MAX_PIXEL            128
#define Y_MAX_PIXEL            160

#define RED    0xf800
#define GREEN    0x07e0
#define BLUE    0x001f
#define WHITE    0xffff
#define BLACK    0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D    //»ÒÉ«0 3165 00110 001011 00101
#define GRAY1   0x8410        //»ÒÉ«1      00000 000000 00000
#define GRAY2   0x4208        //»ÒÉ«2  1111111111011111


void Lcd_init();

void Lcd_Clear(uint16_t Color);

void LCD_WriteData_16Bit(uint16_t Data);

void Lcd_SetRegion(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end);
#endif //LCD_H
