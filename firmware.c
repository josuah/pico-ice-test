/* Send requests to a Wishbone B4 bus as master through SPI */

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "pico-ice/flash.h"

int
main(void)
{
	uint8_t page[FLASH_PAGE_SIZE] = {0};

	stdio_init_all();

	spi_init(spi_default, 1000 * 1000);
	gpio_set_function(PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI);
	gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
	gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
	gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);

	flash_program_page(spi_flash, 0x000000, page);
	flash_read(spi_flash, 0x000000, page, sizeof page);

	return 0;
}
