#include <stdio.h>
#include <string.h>
#include <usb.h>

#define USB_LED_OFF 0
#define USB_LED_ON 1

#define DEVICE_VENDOR_ID 0x16C0
#define DEVICE_PRODUCT_ID 0x05DC

void usage() {
  fprintf(stderr, "Usage: main on|off\n");
  exit(1);
}

struct usb_device *get_usb_device(int vendor_id, int product_id) {
  struct usb_bus *bus;
  struct usb_device *device;

  usb_init();
  usb_find_busses();
  usb_find_devices();

  for (bus = usb_get_busses(); bus; bus = bus->next)
    for (device = bus->devices; device; device = device->next)
      if (device->descriptor.idVendor == vendor_id &&
          device->descriptor.idProduct == product_id)
        return device;

  return NULL;
}

int main(int argc, char **argv) {
  int n = 0;
  char buffer[256];
  struct usb_device *device;
  struct usb_dev_handle *handle;

  if (argc != 2)
    usage();

  device = get_usb_device(DEVICE_VENDOR_ID, DEVICE_PRODUCT_ID);
  if (!device) {
    fprintf(stderr, "Could not find device.\n");
    exit(1);
  }

  handle = usb_open(device);
  if (!handle) {
    fprintf(stderr, "Could not open device.\n");
    exit(1);
  }

  printf("Success.\n");

  if (strcmp(argv[1], "on") == 0) {
    printf("Toggle: on\n");
    n = usb_control_msg(handle,
                        USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN,
                        USB_LED_ON, 0, 0, (char *)buffer, sizeof(buffer), 5000);
  } else if (strcmp(argv[1], "off") == 0) {
    printf("Toggle: off\n");
    n = usb_control_msg(handle,
                        USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN,
                        USB_LED_OFF, 0, 0, (char *)buffer, sizeof(buffer), 5000);
  } else {
    usb_close(handle);
    usage();
  }

  if (n < 0)
    fprintf(stderr, "Unknown USB error: %s\n", usb_strerror());

  usb_close(handle);
}
