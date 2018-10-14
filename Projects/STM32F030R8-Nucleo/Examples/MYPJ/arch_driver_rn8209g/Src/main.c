/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f0xx_hal.h"
#include "device.h"
#include "rn8209g_driver.h"
#include "api_sensor_common.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *Rn8209g = rn8209g_device_binding();
	sensor_init(Rn8209g);
	printf("All device init\r\n");
	
	while(1) {
		sensor_sample_fetch(Rn8209g);
		HAL_Delay(1000);
	}
}
