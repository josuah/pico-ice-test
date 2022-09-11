/* Send requests to a Wishbone B4 bus as master through SPI */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "hardware/gpio.h"
#include "pico-ice/flash.h"
#include "pico-ice/ice.h"
#include "tusb.h"

static void
cdc_task(void)
{
    uint8_t buf[64];
    uint32_t sz;

    if (!tud_cdc_n_available(0))
        return;

    sz = tud_cdc_n_read(0, buf, sizeof(buf));
    for (uint32_t i = 0; i < sz; i++)
        tud_cdc_n_write_char(0, toupper(buf[i]));
    tud_cdc_n_write_flush(0);
}

int
main(void)
{
    stdio_init_all();

    ice_flash_init();
    gpio_init(25);
    gpio_set_dir_out_masked(1 << 25);

    tusb_init();

    for (;;) {
        tud_task();
        cdc_task();
        gpio_put(25, true);
    }

    return 0;
}
