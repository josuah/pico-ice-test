/* Send requests to a Wishbone B4 bus as master through SPI */

#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "pico-ice/flash.h"
#include <stdio.h>
#include <string.h>

void
print_page(uint8_t const *page)
{
	for (size_t i = 0; i < FLASH_PAGE_SIZE; i++) {
		printf(" %02X", page[i]);
		if ((i + 1) % 32 == 0)
			printf("\n");
	}
}

int
main(void)
{
	uint8_t page[FLASH_PAGE_SIZE] = {0};

	stdio_init_all();

	gpio_init(25);
	gpio_set_dir_out_masked(1 << 25);
	gpio_put(25, true);

	spi_init(spi_default, 1000 * 1000);
	gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
	gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
	gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
	gpio_init(PICO_DEFAULT_SPI_CSN_PIN);
	gpio_set_dir(PICO_DEFAULT_SPI_CSN_PIN, GPIO_OUT);
	gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);

	memset(page, 0xFF, sizeof page);

	flash_program_page(spi_default, PICO_DEFAULT_SPI_CSN_PIN, 0x000000, page);
	for (;;) {
		flash_read(spi_default, PICO_DEFAULT_SPI_CSN_PIN, 0x000000, page, FLASH_PAGE_SIZE);
		print_page(page);
	}

	return 0;
}
