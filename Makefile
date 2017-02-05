all:
	mkdir -p bin
	arm-linux-g++ -std=c++11 main.cpp lcd.h lcd.cpp -o bin/rpiscreen
	arm-linux-g++ -std=c++11 -c -Wall -Werror -fPIC lcd.cpp
	arm-linux-g++ -shared -o bin/liblcd.so lcd.o
	rm *.o 
