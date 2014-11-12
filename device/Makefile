CC = avr-gcc
F_CPU = 16000000L
CFLAGS = -DF_CPU=$(F_CPU) -mmcu=atmega328p -Os -c

all: main.hex

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

main.elf: main.o usbdrv/usbdrvasm.o usbdrv/usbdrv.o
	$(CC) -mmcu=atmega328p -o main.elf usbdrv/usbdrv.o usbdrv/usbdrvasm.o main.o

usbdrv/usbdrvasm.o: usbdrv/usbdrvasm.S
	$(CC) $(CFLAGS) -x assembler-with-cpp -o usbdrv/usbdrvasm.o usbdrv/usbdrvasm.S

usbdrv/usbdrv.o: usbdrv/usbdrv.c usbdrv/usbconfig.h
	$(CC) $(CFLAGS) -o usbdrv/usbdrv.o usbdrv/usbdrv.c

main.o: main.c
	$(CC) $(CFLAGS) -Iusbdrv main.c

flash: main.hex
	avrdude -p m328p -c usbtiny -P usb -U flash:w:main.hex

clean:
	rm main.hex main.elf main.o usbdrv/usbdrvasm.o usbdrv/usbdrv.o
