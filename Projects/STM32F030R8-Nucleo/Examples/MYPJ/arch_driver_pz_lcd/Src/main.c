/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f0xx_hal.h"
#include "device.h"
#include "pz_lcd_driver.h"
#include "api_lcd_common.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *Pz_lcd = pz_lcd_device_binding();
	struct lcd_value Voltage;
	struct lcd_value Current;
	struct lcd_value Power;
	struct lcd_value Consumption;
	
	lcd_init(Pz_lcd);
	printf("All device init finish\r\n");
	
	lcd_set_all(Pz_lcd);
	lcd_clean_all(Pz_lcd);
	
	while(1) {
		Voltage.value_integer = 10010;
		Voltage.value_decimal = 93;
		Voltage.e_display_level = DISPLAY_NORMAL;
		Current.value_integer = 10010;
		Current.value_decimal = 93;
		Current.e_display_level = DISPLAY_NORMAL;
		Power.value_integer = 10010;
		Power.value_decimal = 9;
		Power.flag_symbol_K = 0;
		Power.e_display_level = DISPLAY_NORMAL;
		Consumption.value_integer = 10010;
		Consumption.flag_symbol_K = 0;
		Consumption.e_display_level = DISPLAY_NORMAL;
		
		lcd_value_send(Pz_lcd, LCD_PZ_VOLTAGE, &Voltage);
		lcd_value_send(Pz_lcd, LCD_PZ_CURRENT, &Current);
		lcd_value_send(Pz_lcd, LCD_PZ_POWER, &Power);
		lcd_value_send(Pz_lcd, LCD_PZ_CONSUMPTION, &Consumption);
		HAL_Delay(1000);
		
		
		Voltage.value_integer = 10;
		Voltage.value_decimal = 00;
		Voltage.e_display_level = DISPLAY_MASK_TEXT;
		Current.value_integer = 10;
		Current.value_decimal = 00;
		Current.e_display_level = DISPLAY_MASK_TEXT;
		Power.value_integer = 10;
		Power.value_decimal = 0;
		Power.flag_symbol_K = 1;
		Power.e_display_level = DISPLAY_MASK_TEXT;
		Consumption.value_integer = 10;
		Consumption.flag_symbol_K = 1;
		
		Consumption.e_display_level = DISPLAY_MASK_TEXT;
		lcd_value_send(Pz_lcd, LCD_PZ_VOLTAGE, &Voltage);
		lcd_value_send(Pz_lcd, LCD_PZ_CURRENT, &Current);
		lcd_value_send(Pz_lcd, LCD_PZ_POWER, &Power);
		lcd_value_send(Pz_lcd, LCD_PZ_CONSUMPTION, &Consumption);
		HAL_Delay(1000);
		
		
		Voltage.e_display_level = DISPLAY_MASK_NUMBER_TEXT;
		lcd_value_send(Pz_lcd, LCD_PZ_VOLTAGE, &Voltage);
		HAL_Delay(1000);
		
		Current.e_display_level = DISPLAY_MASK_NUMBER_TEXT;
		lcd_value_send(Pz_lcd, LCD_PZ_CURRENT, &Current);
		HAL_Delay(1000);
		
		Consumption.e_display_level = DISPLAY_MASK_NUMBER_TEXT;
		lcd_value_send(Pz_lcd, LCD_PZ_CONSUMPTION, &Consumption);
		HAL_Delay(1000);
		
		Power.e_display_level = DISPLAY_MASK_NUMBER_TEXT;
		lcd_value_send(Pz_lcd, LCD_PZ_POWER, &Power);
		HAL_Delay(1000);
		
		
		Voltage.e_display_level = DISPLAY_MASK_NUMBER;
		lcd_value_send(Pz_lcd, LCD_PZ_VOLTAGE, &Voltage);
		HAL_Delay(1000);
		
		Current.e_display_level = DISPLAY_MASK_NUMBER;
		lcd_value_send(Pz_lcd, LCD_PZ_CURRENT, &Current);
		HAL_Delay(1000);
		
		Consumption.e_display_level = DISPLAY_MASK_NUMBER;
		lcd_value_send(Pz_lcd, LCD_PZ_CONSUMPTION, &Consumption);
		HAL_Delay(1000);
		
		Power.e_display_level = DISPLAY_MASK_NUMBER;
		lcd_value_send(Pz_lcd, LCD_PZ_POWER, &Power);
		HAL_Delay(1000);
	}
}
