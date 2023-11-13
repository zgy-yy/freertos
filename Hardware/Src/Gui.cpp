//
// Created by acer-zgy on 2023/11/10.
//

#include <cstdarg>
#include "Gui.h"
#include "stdio.h"


/**
 * @brief	显示asic 字符
 *
 * @param   x,y		起始坐标
 * @param   chr		显示的字符
 * @param   size	大小 16/24/32
 *
 * @return  void
 */

uint16_t POINT_COLOR = BLUE;    // 字体
uint16_t BACK_COLOR = WHITE;    // 背景

void LCD_ShowChar(uint16_t x, uint16_t y, char chr) {
    uint8_t size = 16;
    uint16_t c_ind = chr - ' ';
    if ((x > (X_MAX_PIXEL - size / 2)) || (y > (Y_MAX_PIXEL - size))) return;

    Lcd_SetRegion(x, y, x + size / 2 - 1, y + size - 1);//(x,y,x+8-1,y+16-1)

    for (int i = 0; i < 16; ++i) {
        uint16_t ch = asc2_16x16[c_ind][i];
        for (int j = 0; j < 16 / 2; ++j) {
            uint16_t color = BACK_COLOR;
            if (ch & 0x80)
                color = POINT_COLOR;
            LCD_WriteData_16Bit(color);
            ch <<= 1;

        }
    }
}

/**

 *
 * @param   x,y		起点坐标
 * @param   width	字符显示宽度
 * @param   height	高度
 * @param   size	字体大小
 * @param   p		字符串首地址
 *
 * @return  void
 */
void LCD_ShowString(uint16_t x, uint16_t y, char *p) {
    uint8_t size = 16;
    uint16_t start_x = x;
    uint16_t start_y = y;

    while ((*p <= '~') && (*p >= ' ')) //判断是否非法
    {
        LCD_ShowChar(start_x, start_y, *p);
        start_x += size / 2;
        if (start_x >= X_MAX_PIXEL) {
            start_x = x;
            start_y += size;
        }
        p++;
    }
}

void lcd_printf(uint16_t x, uint16_t y, const char *format, ...) {
    va_list args;
    va_start(args, format);

    uint8_t size = 16;
    uint16_t start_x = x;
    uint16_t start_y = y;

    char temp[16] = {0};
    while (*format != '\0') {
        if (*format == '%') {
            format++; // 移动到占位符的下一个字符

            if (*format == 'd') {
                int value = va_arg(args, int);
                sprintf(temp, "%d", value);
                LCD_ShowString(start_x, start_y, temp);
            } else if (*format == 'f') {
                double value = va_arg(args, double);
                sprintf(temp, "%f", value);
                LCD_ShowString(start_x, start_y, temp);
            } else if (*format == 's') {
                char *value = va_arg(args, char*);
                sprintf(temp, "%s", value);
                LCD_ShowString(start_x, start_y, temp);
            } else if (*format == 'c') {
                int value = va_arg(args, int);
                sprintf(temp, "%c", value);
                LCD_ShowString(start_x, start_y, temp);
            } else {
                printf("Unsupported format specifier: %c", *format);
            }
//            start_x += strlen(temp) * size / 2;
        } else {
            LCD_ShowChar(start_x, start_y, *format);
            start_x += size / 2;
        }

        if (start_x >= X_MAX_PIXEL) {
            start_x = x;
            start_y += size;
        }
        format++; // 移动到下一个字符
    }

    va_end(args);
}