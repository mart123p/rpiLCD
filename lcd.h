/**
 * @file
 * @author Martin Pouliot
 * @version 0.1dev
 * @section DESCRIPTION
 * 
 * This class takes care of displaying text on the LCD attached to the Raspberry Pi, It is pretty basic as it only includes 3 methods. 
 */
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
    /**
     * Initialises the lcd screen and the I2C interface. We are using device 1 since it is the I2C pins on the Raspberry Pi. However this might change if we change the version of the Raspberry pi.
     * @param addr A byte for the I2C address
     * @param lcd_cols A byte for the number of columns that the screen has
     * @param lcd_rows A byte for the number of rows that the screen has
     */
    void begin(uint8_t addr, uint8_t lcd_cols, uint8_t lcd_rows);

    /**
     * Erases the content of the screen
     */
    void clear();

    /**
     * Prints a message to the screen.
     * @param str The message to print to the screen
     * @param pos Where do we print our message. Accepted values(LCD_LINE_1,LCD_LINE_2,LCD_LINE_3,LCD_LINE_4)
     */
    void print(std::string str, uint8_t pos);

private:
    void lcd_byte(uint8_t bits, bool mode);
    void lcd_toggle_enable(uint8_t bits);
    int i2cHandle;
    uint8_t cols;
};


#endif //PILCD_LCD_H

