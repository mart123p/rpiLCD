# rpiLCD
rpiLCD is a small library to control an LCM1602 from a Raspberry Pi. I found a small [python script](https://bitbucket.org/MattHawkinsUK/rpispy-misc/raw/master/python/lcd_i2c.py) from Matt Hawkins that I have ported in C++.

## Utility usage
* The pipe is working with this utility. It will keep the first two lines and the 16 first characters of each line.
* `rpiscreen [i2cAddress] line1 [line2]` The i2c address is in base 10 format. By default i2c address is set  to 39 or 0x27

## Installation
 ```
 git clone git@github.com:mart123p/rpiLCD.git
 cd rpiLCD/
 make
 sudo cp rpiscreen /usr/bin/
 enjoy :D
 ```
