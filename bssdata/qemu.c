#include "qemu.h"
#include "int.h"

void pl011_uart_write_char(char value)
{
	volatile uint32_t* paddr = (volatile uint32_t*)(PL011_UART_BASE + PL011_UARTFR);

	/* Wait until the serial buffer is empty */
	while (*paddr & PL011_UARTFR_TXFF);

	/* Put value into the serial buffer */
	paddr = (volatile uint32_t*)(PL011_UART_BASE + PL011_UARTDR);
	*paddr = value;
}

void pl011_uart_write_string(const char * str)
{
	while (*str) pl011_uart_write_char(*str++);
}

void pl011_uart_write_hex(uint32_t value)
{
	char* hex = "0123456789ABCDEF";

	pl011_uart_write_char(*(hex + ((value >> 28) & 0xF)));
	pl011_uart_write_char(*(hex + ((value >> 24) & 0xF)));
	pl011_uart_write_char(*(hex + ((value >> 20) & 0xF)));
	pl011_uart_write_char(*(hex + ((value >> 16) & 0xF)));
	pl011_uart_write_char(*(hex + ((value >> 12) & 0xF)));
	pl011_uart_write_char(*(hex + ((value >> 8) & 0xF)));
	pl011_uart_write_char(*(hex + ((value >> 4) & 0xF)));
	pl011_uart_write_char(*(hex + (value & 0xF)));
	pl011_uart_write_char(' ');
}

void pl050_init(void)
{
	volatile uint32_t* paddr = (volatile uint32_t*)(PL050_KMI_KB_BASE + PL050_KMICR);
	*paddr = PL050_KMICR_KMIEN; // Enable keyboard
}
