//
// Created by acer-zgy on 2023/11/10.
//

#ifndef STM32_LEARN01_GUI_H
#define STM32_LEARN01_GUI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Lcd.h"
#include "font.h"

void LCD_ShowChar(uint16_t x, uint16_t y, char chr);

void LCD_ShowString(uint16_t x, uint16_t y, char* p);

void lcd_printf(uint16_t x, uint16_t y, const char* format, ...);

#ifdef __cplusplus
}
#endif


#endif //STM32_LEARN01_GUI_H
