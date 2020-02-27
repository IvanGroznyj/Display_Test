# Created by Makefile Builder by Ivan Khodyrev
# *** variables ***
compilator=avr-gcc
compilator_flags=-g -mmcu=atmega32
linker=avr-gcc
linker_flags=-g -mmcu=atmega32
debug_dir=Debug
source_dir=src
files=$(wildcard ./$(source_dir)/*.c)
objects=$(patsubst ./$(source_dir)/%.c, ./$(debug_dir)/%.o, $(files))
executable=display-test
# *** instructions ***
./$(debug_dir)/%.o: ./$(source_dir)/%.c
	$(compilator) $(compilator_flags) -Wall -Os -c $< -o $@

all: $(objects)
	$(linker) $(linker_flags) -o ./$(debug_dir)/$(executable).elf $(objects)
	avr-objcopy -j .text -j .data -O ihex ./$(debug_dir)/$(executable).elf ./$(debug_dir)/$(executable).hex

clean: 
	rm -rf $(debug_dir)/*

flash: 
	avrdude -p m32 -c usbasp -P usb -U flash:w:./$(debug_dir)/$(executable).hex
