//
// Created by martin on 1/27/17.
//
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <cstring>
#include "lcd.h"
#include <iostream>

void LCD::begin(uint8_t addr, uint8_t lcd_cols, uint8_t lcd_rows) {
    cols = lcd_cols;
    i2cHandle = open("/dev/i2c-1",O_RDWR);
    ioctl(i2cHandle,I2C_SLAVE,addr);

    lcd_byte(0x33,LCD_CMD);
    lcd_byte(0x32,LCD_CMD);
    lcd_byte(0x06,LCD_CMD);
    lcd_byte(0x0C,LCD_CMD);
    lcd_byte(0x28,LCD_CMD);
    lcd_byte(0x01,LCD_CMD);


    usleep(500);
}

void LCD::lcd_byte(uint8_t bits, bool mode) {
    char txBuffer[1];
    memset(txBuffer, 0, sizeof(txBuffer));
    txBuffer[0] = mode | (bits & 0xF0) | LCD_BACKLIGHT;
    write(i2cHandle,txBuffer,1);
    lcd_toggle_enable(txBuffer[0]);


    txBuffer[0] = mode | ((bits<<4) & 0xF0) | LCD_BACKLIGHT;
    write(i2cHandle,txBuffer,1);
    lcd_toggle_enable(txBuffer[0]);

}

void LCD::lcd_toggle_enable(uint8_t bits) {
    char txBuffer[1];
    memset(txBuffer, 0, sizeof(txBuffer));


    usleep(500);
    txBuffer[0] = (bits | ENABLE);
    write(i2cHandle,txBuffer,1);

    usleep(500);
    txBuffer[0] = (bits & ~ENABLE);
    write(i2cHandle,txBuffer,1);

    usleep(500);

}

void LCD::clear() {
    lcd_byte(0x01,1);
}

void LCD::print(std::string str, uint8_t pos) {
    lcd_byte(pos,LCD_CMD);

    if(str.length() > cols){
        str = str.substr(0,cols);
    }
    for(uint8_t i(0); i < str.length(); i++){
        lcd_byte(uint8_t(str[i]),LCD_CHR);
    }
    if(str.length() < cols){
        int remaining(cols - str.length());
        //We add the remaining spaces if needed
       	usleep(50);
	for(int i(0); i < remaining; i++){
            lcd_byte(0x20,LCD_CHR);
        }

    }

}

