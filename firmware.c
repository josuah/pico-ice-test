#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "pico_ice/ice.h"

/* TinyUSB includes */
#include "bsp/board.h"
#include "tusb.h"

int
main(void)
{
    stdio_init_all();
    ice_init_defaults();

    for (;;) {
        ice_usb_task();
    }

    return 0;
}
