#include <stdio.h>
#include <usb.h>

int main(int argc, char **argv) {
  struct usb_bus *bus;
  struct usb_device *device;

  usb_init();
  usb_find_busses();
  usb_find_devices();

  for(bus = usb_get_busses(); bus; bus = bus->next) {
    for(device = bus->devices; device; device = device->next) {
      printf("vendor = %d, product = %d\n",
             device->descriptor.idVendor,
             device->descriptor.idProduct);
    }
  }
}
