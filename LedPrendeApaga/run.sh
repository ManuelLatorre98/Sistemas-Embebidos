avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
wait
avr-gcc -mmcu=atmega328p main.o -o main.elf
wait
avr-objcopy -O ihex -R .eeprom main.elf main.hex
wait
avrdude -v v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:main.hex:i