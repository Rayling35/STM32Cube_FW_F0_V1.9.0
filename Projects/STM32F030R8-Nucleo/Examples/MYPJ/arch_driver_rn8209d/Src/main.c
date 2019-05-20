/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f0xx_hal.h"
#include "device.h"
#include "rn8209d_driver.h"
#include "api_sensor_common.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *Rn8209d = rn8209d_device_binding();
	struct sensor_value Rn8209d_data;
	sensor_init(Rn8209d);
	printf("All device init\r\n");
	
	while(1) {
		sensor_sample_fetch(Rn8209d);
		sensor_value_get(Rn8209d, SENSOR_RN8209D_CONSUMPTION, &Rn8209d_data);
		if(Rn8209d_data.value_integer > 12) {
			sensor_data_clear(Rn8209d, SENSOR_RN8209D_CONSUMPTION);
		}
		HAL_Delay(1000);
	}
}
