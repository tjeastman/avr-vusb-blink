CC = avr-gcc
F_CPU = 16000000L
CFLAGS = -DF_CPU=$(F_CPU) -mmcu=atmega328p -Os

all: main.hex

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

main.elf: main.o usbdrv/usbdrvasm.o usbdrv/usbdrv.o usbdrv/oddebug.o
	$(CC) -mmcu=atmega328p -o main.elf usbdrv/usbdrv.o usbdrv/oddebug.o usbdrv/usbdrvasm.o main.o

usbdrv/usbdrvasm.o: usbdrv/usbdrvasm.S
	$(CC) $(CFLAGS) -c -x assembler-with-cpp -o usbdrv/usbdrvasm.o usbdrv/usbdrvasm.S

usbdrv/usbdrv.o: usbdrv/usbdrv.c usbdrv/usbconfig.h
	$(CC) $(CFLAGS) -c -o usbdrv/usbdrv.o usbdrv/usbdrv.c

usbdrv/oddebug.o: usbdrv/oddebug.c
	$(CC) $(CFLAGS) -c -o usbdrv/oddebug.o usbdrv/oddebug.c

main.o: main.c
	$(CC) $(CFLAGS) -c -Iusbdrv main.c

flash: main.hex
	avrdude -p m328p -c usbtiny -P usb -U flash:w:main.hex

clean:
	rm main.hex main.elf main.o usbdrv/usbdrvasm.o usbdrv/usbdrv.o usbdrv/oddebug.o
