avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o tresLeds.o tresLeds.c
wait
avr-gcc -mmcu=atmega328p tresLeds.o -o tresLeds.elf
wait
avr-objcopy -O ihex -R .eeprom tresLeds.elf tresLeds.hex
wait
avrdude -v v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:tresLeds.hex:i