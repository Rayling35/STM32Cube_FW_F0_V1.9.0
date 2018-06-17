/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f0xx_hal.h"
#include "device.h"
#include "rn8209g_driver.h"
#include "sensor_common_api.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *rn8209g = rn8209g_device_binding();
	sensor_init(rn8209g);
	printf("All device init\r\n");
	
	while(1) {
		sensor_sample_fetch(rn8209g);
		HAL_Delay(2000);
	}
}
