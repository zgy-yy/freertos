//
// Created by acer-zgy on 2023/11/13.
//

#include "lcd.h"

#include "cmsis_os2.h"

#include "spi.h"




#define LCD_CS            GPIO_PIN_12  //B12 --CS/CE
#define LCD_RS            GPIO_PIN_14    //B14  --RS/DC
#define LCD_RST        GPIO_PIN_5    //PB5  --RST

#define    LCD_CS_SET    HAL_GPIO_WritePin(GPIOB, LCD_CS, GPIO_PIN_SET)
#define    LCD_CS_CLR    HAL_GPIO_WritePin(GPIOB, LCD_CS, GPIO_PIN_RESET)

#define    LCD_RS_SET    HAL_GPIO_WritePin(GPIOB, LCD_RS, GPIO_PIN_SET)
#define    LCD_RS_CLR    HAL_GPIO_WritePin(GPIOB, LCD_RS, GPIO_PIN_RESET)

#define    LCD_RST_SET    HAL_GPIO_WritePin(GPIOB, LCD_RST, GPIO_PIN_SET)
#define    LCD_RST_CLR    HAL_GPIO_WritePin(GPIOB, LCD_RST, GPIO_PIN_RESET)

void lcd_gpio_init() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOB_CLK_ENABLE();



    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_14;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_5;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void Lcd_WriteIndex(uint8_t Index) {
    LCD_CS_CLR;
    LCD_RS_CLR;
    HAL_SPI_Transmit(&hspi2, &Index, 1, 0xffff);
    LCD_CS_SET;
}

void Lcd_WriteData(uint8_t Data) {
    LCD_CS_CLR;
    LCD_RS_SET;
    HAL_SPI_Transmit(&hspi2, &Data, 1, 0xffff);
    LCD_CS_SET;
}


void LCD_WriteData_16Bit(uint16_t Data) {
    LCD_CS_CLR;
    LCD_RS_SET;
    uint8_t h_data = Data >> 8;
    uint8_t l_data = Data;
    HAL_SPI_Transmit(&hspi2, &h_data, 1, 0xffff);
    HAL_SPI_Transmit(&hspi2, &l_data, 1, 0xffff);
    LCD_CS_SET;
}

void Lcd_WriteReg(uint8_t Index, uint8_t Data) {
    Lcd_WriteIndex(Index);
    Lcd_WriteData(Data);
}

void Lcd_Reset(void) {
    LCD_RST_CLR;
    HAL_Delay(100);
    LCD_RST_SET;
    HAL_Delay(50);
}

void Lcd_init() {
    MX_SPI2_Init();
    lcd_gpio_init();


    Lcd_Reset(); //Reset before LCD Init.

    //LCD Init For 1.44Inch LCD Panel with ST7735R.
    Lcd_WriteIndex(0x11); //Sleep exit
    HAL_Delay(120);

    //ST7735R Frame Rate
    Lcd_WriteIndex(0xB1);
    Lcd_WriteData(0x01);
    Lcd_WriteData(0x2C);
    Lcd_WriteData(0x2D);

    Lcd_WriteIndex(0xB2);
    Lcd_WriteData(0x01);
    Lcd_WriteData(0x2C);
    Lcd_WriteData(0x2D);

    Lcd_WriteIndex(0xB3);
    Lcd_WriteData(0x01);
    Lcd_WriteData(0x2C);
    Lcd_WriteData(0x2D);
    Lcd_WriteData(0x01);
    Lcd_WriteData(0x2C);
    Lcd_WriteData(0x2D);

    Lcd_WriteIndex(0xB4); //Column inversion
    Lcd_WriteData(0x07);

    //ST7735R Power Sequence
    Lcd_WriteIndex(0xC0);
    Lcd_WriteData(0xA2);
    Lcd_WriteData(0x02);
    Lcd_WriteData(0x84);
    Lcd_WriteIndex(0xC1);
    Lcd_WriteData(0xC5);

    Lcd_WriteIndex(0xC2);
    Lcd_WriteData(0x0A);
    Lcd_WriteData(0x00);

    Lcd_WriteIndex(0xC3);
    Lcd_WriteData(0x8A);
    Lcd_WriteData(0x2A);
    Lcd_WriteIndex(0xC4);
    Lcd_WriteData(0x8A);
    Lcd_WriteData(0xEE);

    Lcd_WriteIndex(0xC5); //VCOM
    Lcd_WriteData(0x0E);

    Lcd_WriteIndex(0x36); //MX, MY, RGB mode
    Lcd_WriteData(0xC0);

    //ST7735R Gamma Sequence
    Lcd_WriteIndex(0xe0);
    Lcd_WriteData(0x0f);
    Lcd_WriteData(0x1a);
    Lcd_WriteData(0x0f);
    Lcd_WriteData(0x18);
    Lcd_WriteData(0x2f);
    Lcd_WriteData(0x28);
    Lcd_WriteData(0x20);
    Lcd_WriteData(0x22);
    Lcd_WriteData(0x1f);
    Lcd_WriteData(0x1b);
    Lcd_WriteData(0x23);
    Lcd_WriteData(0x37);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x07);
    Lcd_WriteData(0x02);
    Lcd_WriteData(0x10);

    Lcd_WriteIndex(0xe1);
    Lcd_WriteData(0x0f);
    Lcd_WriteData(0x1b);
    Lcd_WriteData(0x0f);
    Lcd_WriteData(0x17);
    Lcd_WriteData(0x33);
    Lcd_WriteData(0x2c);
    Lcd_WriteData(0x29);
    Lcd_WriteData(0x2e);
    Lcd_WriteData(0x30);
    Lcd_WriteData(0x30);
    Lcd_WriteData(0x39);
    Lcd_WriteData(0x3f);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x07);
    Lcd_WriteData(0x03);
    Lcd_WriteData(0x10);

    Lcd_WriteIndex(0x2a);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x7f);

    Lcd_WriteIndex(0x2b);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x9f);

    Lcd_WriteIndex(0xF0); //Enable test command
    Lcd_WriteData(0x01);
    Lcd_WriteIndex(0xF6); //Disable ram power save mode
    Lcd_WriteData(0x00);

    Lcd_WriteIndex(0x3A); //65k mode
    Lcd_WriteData(0x05);


    Lcd_WriteIndex(0x29); //Display on
}

void Lcd_SetRegion(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end) {
    Lcd_WriteIndex(0x2a);
    Lcd_WriteData(0x00);
    Lcd_WriteData(x_start); //Lcd_WriteData(x_start+2);
    Lcd_WriteData(0x00);
    Lcd_WriteData(x_end);

    Lcd_WriteIndex(0x2b);
    Lcd_WriteData(0x00);
    Lcd_WriteData(y_start);
    Lcd_WriteData(0x00);
    Lcd_WriteData(y_end);

    Lcd_WriteIndex(0x2c);
}


void Lcd_SetXY(uint16_t x, uint16_t y) {
    Lcd_SetRegion(x, y, x, y);
}


void Lcd_DrawPoint(uint16_t x, uint16_t y, uint16_t Data) {
    Lcd_SetRegion(x, y, x + 1, y + 1);
    LCD_WriteData_16Bit(Data);
}


unsigned int Lcd_ReadPoint(uint16_t x, uint16_t y) {
    unsigned int Data;
    Lcd_SetXY(x, y);

    //Data=Lcd_ReadData();
    Lcd_WriteData(Data);
    return Data;
}

void Lcd_Clear(uint16_t Color) {
    unsigned int i, m;
    Lcd_SetRegion(0, 0, X_MAX_PIXEL - 1, Y_MAX_PIXEL - 1);
    Lcd_WriteIndex(0x2c);
    for (i = 0; i < X_MAX_PIXEL; i++)
        for (m = 0; m < Y_MAX_PIXEL; m++) {
            LCD_WriteData_16Bit(Color);
        }
}
