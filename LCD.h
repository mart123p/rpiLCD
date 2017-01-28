//
// Created by martin on 1/27/17.
//

#ifndef PILCD_LCD_H
#define PILCD_LCD_H
#define I2C_ADDR 0x27
#define LCD_CHR 1
#define LCD_CMD 0
#define LCD_LINE_1 0x80
#define LCD_LINE_2 0xC0
#define LCD_LINE_3 0x94
#define LCD_LINE_4 0xD4
#define LCD_BACKLIGHT 0x08
#define ENABLE 0b00000100

#include <cstdint>
#include <string>

class LCD {
public:
    void begin(uint8_t addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void clear();
    void print(std::string str, uint8_t pos);

private:
    void lcd_byte(uint8_t bits, bool mode);
    void lcd_toggle_enable(uint8_t bits);
    int i2cHandle;
    uint8_t cols;
};


#endif //PILCD_LCD_H

