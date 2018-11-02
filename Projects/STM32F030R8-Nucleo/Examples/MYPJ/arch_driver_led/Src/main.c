/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f0xx_hal.h"
#include "device.h"
#include "breathing_led_driver.h"
#include "api_led_common.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *Breathing_led = breathing_led_device_binding();
	led_init(Breathing_led);
	printf("All device init\r\n");
	
	uint8_t brightness;
	
	while(1) {
		for(brightness = 0; brightness <= 100; brightness++) {
			led_breathing(Breathing_led, brightness);
			HAL_Delay(20);
		}
		for(brightness = 100; brightness > 0; brightness--) {
			led_breathing(Breathing_led, brightness);
			HAL_Delay(20);
		}
	}
}
