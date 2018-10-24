/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "stm32f0xx_hal.h"
#include "uart_printf.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	printf("Printf Empty Example\r\n");
}
