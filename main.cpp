#include "LCD.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <unistd.h>
int main(int argc, char* argv[]){
	
	if( argc != 4 &&  argc != 3 && argc != 2 && isatty(fileno(stdin))){
		std::cerr << "You must use the following syntax:" << std::endl;
		std::cerr << "rpiscreen [i2cAddress] line1 [line2]" << std::endl;
		return 1;	
	}
	int addr;
	try{
		if(argc == 4){
			addr = std::stoi(argv[1]);
		}else{
			addr = 39;
		}
		if(!(addr > 0 && addr < 128)){
			std::cerr << "The address is out of range it must be between 1-127" << std::endl;
	                return 1;
		}
	}catch(const std::invalid_argument& e){
		std::cerr << "The address must be a number" << std::endl;
		return 1;
	}catch(const std::out_of_range& e){
		std::cerr << "The address is out of range it must be between 1-127" << std::endl;
		return 1;
	}


	
	LCD lcd;
	lcd.begin(addr,16,2);
	lcd.clear();	

	if(!isatty(fileno(stdin))){
		std::string line;
		int i = 0;
		while(std::getline(std::cin,line)){
			if(i == 0){
				lcd.print(line,LCD_LINE_1);
			}else if(i == 1){
				lcd.print(line,LCD_LINE_2);
			}else{
				break;
			}
			i++;	
		}
	}else if(argc == 4){
		lcd.print(argv[2],LCD_LINE_1);
		lcd.print(argv[3],LCD_LINE_2);
	}else if(argc == 3){
		lcd.print(argv[1],LCD_LINE_1);
                lcd.print(argv[2],LCD_LINE_2);
	}else if(argc == 2){
		lcd.print(argv[1],LCD_LINE_1);
	}
	return 0;
}
