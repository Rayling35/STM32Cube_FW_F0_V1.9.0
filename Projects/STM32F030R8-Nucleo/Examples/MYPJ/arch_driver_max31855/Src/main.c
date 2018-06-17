/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f0xx_hal.h"
#include "device.h"
#include "max31855_driver.h"
#include "sensor_common_api.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *max31855 = max31855_device_binding();
	struct sensor_value temperature;
	sensor_init(max31855);
	printf("All device init finish\r\n");
	
	while(1) {
		sensor_sample_fetch(max31855);
		
		sensor_value_get(max31855, SENSOR_MAX31855_TEMPERATURE_THERMOCOUPLE, &temperature);
		printf("MAX31855 thermocouple = %d.%d\r\n", temperature.integer, temperature.decimal);
		
		sensor_value_get(max31855, SENSOR_MAX31855_TEMPERATURE_JUNCTION, &temperature);
		printf("MAX31855 junction = %d.%d\r\n", temperature.integer, temperature.decimal);
		
		HAL_Delay(100);
	}
}
