CC=avr-gcc
CCFLAGS=-g -mmcu=atmega32
HEXFLAGS=-j .text -j .data -O ihex

EXECUTABLE=Display-Test
SOURCECODE=src
DEBUGDIR=Debug
FILES=$(wildcard ./$(SOURCECODE)/*.c)
OBJECTS=$(patsubst ./$(SOURCECODE)/%.c, ./$(DEBUGDIR)/%.o, $(FILES))

./$(DEBUGDIR)/%.o: ./$(SOURCECODE)/%.c
	${CC} ${CCFLAGS} -Wall -Os -c $< -o $@

all: $(OBJECTS)
	${CC} ${CCFLAGS} -o ./$(DEBUGDIR)/${EXECUTABLE}.elf ${OBJECTS}
	avr-objcopy -j .text -j .data -O ihex ./$(DEBUGDIR)/${EXECUTABLE}.elf ./$(DEBUGDIR)/${EXECUTABLE}.hex
	
flash:
	avrdude -p m32 -c usbasp -P usb -U flash:w:./$(DEBUGDIR)/${EXECUTABLE}.hex

clean:
	rm -rf ./$(DEBUGDIR)/*.o ./$(DEBUGDIR)/$(EXECUTABLE).*
	
docs:
	doxygen
	firefox html/index.html