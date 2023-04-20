avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o knightRider.o knightRider.c
wait
avr-gcc -mmcu=atmega328p knightRider.o -o knightRider.elf
wait
avr-objcopy -O ihex -R .eeprom knightRider.elf knightRider.hex
wait
avrdude -v v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:knightRider.hex:i