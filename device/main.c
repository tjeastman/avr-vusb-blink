#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usbdrv.h"

#define USB_LED_OFF 0
#define USB_LED_ON 1

USB_PUBLIC uchar usbFunctionSetup(uchar data[8])
{
  usbRequest_t *rq = (void *)data;

  switch (rq->bRequest) {
  case USB_LED_ON:
    // set pins on port B to HIGH to turn the LED on
    PORTB = 0xFF;
    break;
  case USB_LED_OFF:
    // set pins on port B to LOW to turn the LED off
    PORTB = 0x00;
    break;
  }

  return(0);
}

int main (void)
{
  uchar i;

  // set the data direction register to make all pins on port B output pins
  DDRB = 0b11111111;
  PORTB = 0x00;

  wdt_enable(WDTO_1S); // enable 1s watchdog timer

  usbInit();

  usbDeviceDisconnect(); // enforce re-enumeration
  for (i = 0; i < 250; ++i) {
    wdt_reset(); // reset the watchdog timer
    _delay_ms(2);
  }
  usbDeviceConnect();

  sei(); // enable interrupts after re-enumeration

  while (1) {
    wdt_reset(); // reset the watchdog timer
    usbPoll();
  }

  return(0);
}
