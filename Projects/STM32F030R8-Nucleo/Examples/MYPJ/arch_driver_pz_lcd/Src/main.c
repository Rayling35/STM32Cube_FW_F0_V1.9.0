/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f0xx_hal.h"
#include "device.h"
#include "pz_lcd_driver.h"
#include "lcd_common_api.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *pz_lcd = pz_lcd_device_binding();
	struct lcd_value voltage;
	struct lcd_value current;
	struct lcd_value power;
	struct lcd_value consumption;
	
	lcd_init(pz_lcd);
	printf("All device init finish\r\n");
	
	lcd_set_all(pz_lcd);
	HAL_Delay(500);
	lcd_clean_all(pz_lcd);
	HAL_Delay(500);
	
	voltage.integer = 110;
	voltage.decimal = 0;
	
	current.integer = 13;
	current.decimal = 94;
	
	power.integer = 1533;
	power.decimal = 4;
	
	consumption.integer = 8549;
	consumption.decimal = 0;
	
	lcd_value_send(pz_lcd, LCD_PZ_VOLTAGE, &voltage);
	lcd_value_send(pz_lcd, LCD_PZ_CURRENT, &current);
	lcd_value_send(pz_lcd, LCD_PZ_POWER, &power);
	lcd_value_send(pz_lcd, LCD_PZ_CONSUMPTION, &consumption);
	
	while(1) {
	}
}
