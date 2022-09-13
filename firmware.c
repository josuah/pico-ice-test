#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "pico_ice/ice.h"

int
main(void)
{
    stdio_init_all();
    ice_init_fpga_clock(8);
    return 0;
}
