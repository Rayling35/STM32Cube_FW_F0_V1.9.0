/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f0xx_hal.h"
#include "device.h"
#include "max31855_driver.h"
#include "api_sensor_common.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *Max31855 = max31855_device_binding();
	struct sensor_value Temp;
	sensor_init(Max31855);
	printf("All device init finish\r\n");
	
	while(1) {
		sensor_sample_fetch(Max31855);
		
		sensor_value_get(Max31855, SENSOR_MAX31855_TEMPERATURE_THERMOCOUPLE, &Temp);
		printf("MAX31855 thermocouple = %d.%d\r\n", Temp.value_integer, Temp.value_decimal);
		
		sensor_value_get(Max31855, SENSOR_MAX31855_TEMPERATURE_JUNCTION, &Temp);
		printf("MAX31855 junction = %d.%d\r\n", Temp.value_integer, Temp.value_decimal);
		
		HAL_Delay(100);
	}
}
