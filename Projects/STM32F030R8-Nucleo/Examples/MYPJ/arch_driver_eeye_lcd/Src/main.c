/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f0xx_hal.h"
#include "device.h"
#include "eeye_lcd_driver.h"
#include "api_lcd_common.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *Eeye_lcd = eeye_lcd_device_binding();
	struct lcd_value Voltage;
	struct lcd_value Current;
	struct lcd_value Power;
	struct lcd_value Consumption;
	struct lcd_value Pf;
	struct lcd_value Temperature;
	
	lcd_init(Eeye_lcd);
	printf("All device init finish\r\n");
	
	lcd_set_all(Eeye_lcd);
	HAL_Delay(1000);
	lcd_clean_all(Eeye_lcd);
	HAL_Delay(1000);
	
	while(1) {
		/*---1---*/
		Voltage.value_integer = 6666;
		Voltage.value_decimal = 8;
		Voltage.e_display_mode = DISPLAY_NORMAL;
		
		Current.value_integer = 6666;
		Current.value_decimal = 88;
		Current.e_display_mode = DISPLAY_NORMAL;
		
		Power.value_integer = 66666;
		Power.value_decimal = 8;
		Power.flag_symbol_K = 0;
		Power.e_display_mode = DISPLAY_NORMAL;
		
		Consumption.value_integer = 66666;
		Consumption.value_decimal = 8;
		Consumption.flag_symbol_K = 0;
		Consumption.e_display_mode = DISPLAY_NORMAL;
		
		Pf.value_integer = 666;
		Pf.value_decimal = 96;
		Pf.e_display_mode = DISPLAY_NORMAL;
		
		Temperature.value_integer = 6666;
		Temperature.value_decimal = 8;
		Temperature.flag_symbol_C = 0;
		Temperature.flag_symbol_F = 0;
		Temperature.e_display_mode = DISPLAY_NORMAL;
		
		lcd_value_send(Eeye_lcd, LCD_EEYE_VOLTAGE, &Voltage);
		lcd_value_send(Eeye_lcd, LCD_EEYE_CURRENT, &Current);
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		lcd_value_send(Eeye_lcd, LCD_EEYE_PF, &Pf);
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		
		HAL_Delay(5000);
		
		/*---2---*/
		Voltage.value_integer = 888;
		Voltage.value_decimal = 8;
		Voltage.e_display_mode = DISPLAY_NORMAL;
		
		Current.value_integer = 88;
		Current.value_decimal = 88;
		Current.e_display_mode = DISPLAY_NORMAL;
		
		Power.value_integer = 8888;
		Power.value_decimal = 8;
		Power.flag_symbol_K = 1;
		Power.e_display_mode = DISPLAY_NORMAL;
		
		Consumption.value_integer = 8888;
		Consumption.value_decimal = 8;
		Consumption.flag_symbol_K = 1;
		Consumption.e_display_mode = DISPLAY_NORMAL;
		
		Pf.value_integer = 8;
		Pf.value_decimal = 88;
		Pf.e_display_mode = DISPLAY_NORMAL;
		
		Temperature.value_integer = 888;
		Temperature.value_decimal = 8;
		Temperature.flag_symbol_C = 1;
		Temperature.flag_symbol_F = 1;
		Temperature.e_display_mode = DISPLAY_NORMAL;
		
		lcd_value_send(Eeye_lcd, LCD_EEYE_VOLTAGE, &Voltage);
		lcd_value_send(Eeye_lcd, LCD_EEYE_CURRENT, &Current);
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		lcd_value_send(Eeye_lcd, LCD_EEYE_PF, &Pf);
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		
		HAL_Delay(5000);
		
		/*---3---*/
		Voltage.e_display_mode     = DISPLAY_MASK_TEXT;
		Current.e_display_mode     = DISPLAY_MASK_TEXT;
		Power.e_display_mode       = DISPLAY_MASK_TEXT;
		Consumption.e_display_mode = DISPLAY_MASK_TEXT;
		Pf.e_display_mode          = DISPLAY_MASK_TEXT;
		Temperature.e_display_mode = DISPLAY_MASK_TEXT;
		
		lcd_value_send(Eeye_lcd, LCD_EEYE_VOLTAGE, &Voltage);
		lcd_value_send(Eeye_lcd, LCD_EEYE_CURRENT, &Current);
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		lcd_value_send(Eeye_lcd, LCD_EEYE_PF, &Pf);
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		
		HAL_Delay(5000);
		
		/*---4---*/
		Voltage.e_display_mode     = DISPLAY_MASK_NUMBER;
		Current.e_display_mode     = DISPLAY_MASK_NUMBER;
		Consumption.e_display_mode = DISPLAY_MASK_NUMBER;
		Power.e_display_mode       = DISPLAY_MASK_NUMBER;
		Pf.e_display_mode          = DISPLAY_MASK_NUMBER;
		Temperature.e_display_mode = DISPLAY_MASK_NUMBER;
		
		lcd_value_send(Eeye_lcd, LCD_EEYE_VOLTAGE, &Voltage);
		HAL_Delay(1000);
		lcd_value_send(Eeye_lcd, LCD_EEYE_CURRENT, &Current);
		HAL_Delay(1000);
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		HAL_Delay(1000);
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		HAL_Delay(1000);
		lcd_value_send(Eeye_lcd, LCD_EEYE_PF, &Pf);
		HAL_Delay(1000);
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		HAL_Delay(1000);
		
		/*---5---*/
		Voltage.e_display_mode     = DISPLAY_MASK_NUMBER_TEXT;
		Current.e_display_mode     = DISPLAY_MASK_NUMBER_TEXT;
		Consumption.e_display_mode = DISPLAY_MASK_NUMBER_TEXT;
		Power.e_display_mode       = DISPLAY_MASK_NUMBER_TEXT;
		Pf.e_display_mode          = DISPLAY_MASK_NUMBER_TEXT;
		Temperature.e_display_mode = DISPLAY_MASK_NUMBER_TEXT;
		
		lcd_value_send(Eeye_lcd, LCD_EEYE_VOLTAGE, &Voltage);
		HAL_Delay(1000);
		lcd_value_send(Eeye_lcd, LCD_EEYE_CURRENT, &Current);
		HAL_Delay(1000);
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		HAL_Delay(1000);
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		HAL_Delay(1000);
		lcd_value_send(Eeye_lcd, LCD_EEYE_PF, &Pf);
		HAL_Delay(1000);
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		HAL_Delay(1000);
		
		/*---6---*/
		Voltage.value_integer = 0;
		Voltage.e_display_mode = DISPLAY_ONLY_NUMBER_4;
		lcd_value_send(Eeye_lcd, LCD_EEYE_VOLTAGE, &Voltage);
		HAL_Delay(1000);
		
		Voltage.value_integer = 10;
		Voltage.e_display_mode = DISPLAY_ONLY_NUMBER_4;
		lcd_value_send(Eeye_lcd, LCD_EEYE_VOLTAGE, &Voltage);
		Voltage.value_integer = 0;
		Voltage.e_display_mode = DISPLAY_ONLY_NUMBER_3;
		lcd_value_send(Eeye_lcd, LCD_EEYE_VOLTAGE, &Voltage);
		HAL_Delay(1000);
		
		Voltage.value_integer = 10;
		Voltage.e_display_mode = DISPLAY_ONLY_NUMBER_3;
		lcd_value_send(Eeye_lcd, LCD_EEYE_VOLTAGE, &Voltage);
		Voltage.value_integer = 0;
		Voltage.e_display_mode = DISPLAY_ONLY_NUMBER_2;
		lcd_value_send(Eeye_lcd, LCD_EEYE_VOLTAGE, &Voltage);
		HAL_Delay(1000);
		
		Voltage.value_integer = 10;
		Voltage.e_display_mode = DISPLAY_ONLY_NUMBER_2;
		lcd_value_send(Eeye_lcd, LCD_EEYE_VOLTAGE, &Voltage);
		Voltage.value_integer = 0;
		Voltage.e_display_mode = DISPLAY_ONLY_NUMBER_1;
		lcd_value_send(Eeye_lcd, LCD_EEYE_VOLTAGE, &Voltage);
		HAL_Delay(1000);
		
		Voltage.value_integer = 10;
		Voltage.e_display_mode = DISPLAY_ONLY_NUMBER_1;
		lcd_value_send(Eeye_lcd, LCD_EEYE_VOLTAGE, &Voltage);
		Current.value_integer = 0;
		Current.e_display_mode = DISPLAY_ONLY_NUMBER_4;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CURRENT, &Current);
		HAL_Delay(1000);
		
		Current.value_integer = 10;
		Current.e_display_mode = DISPLAY_ONLY_NUMBER_4;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CURRENT, &Current);
		Current.value_integer = 0;
		Current.e_display_mode = DISPLAY_ONLY_NUMBER_3;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CURRENT, &Current);
		HAL_Delay(1000);
		
		Current.value_integer = 10;
		Current.e_display_mode = DISPLAY_ONLY_NUMBER_3;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CURRENT, &Current);
		Current.value_integer = 0;
		Current.e_display_mode = DISPLAY_ONLY_NUMBER_2;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CURRENT, &Current);
		HAL_Delay(1000);
		
		Current.value_integer = 10;
		Current.e_display_mode = DISPLAY_ONLY_NUMBER_2;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CURRENT, &Current);
		Current.value_integer = 0;
		Current.e_display_mode = DISPLAY_ONLY_NUMBER_1;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CURRENT, &Current);
		HAL_Delay(1000);
		
		Current.value_integer = 10;
		Current.e_display_mode = DISPLAY_ONLY_NUMBER_1;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CURRENT, &Current);
		Power.value_integer = 0;
		Power.e_display_mode = DISPLAY_ONLY_NUMBER_5;
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		HAL_Delay(1000);
		
		Power.value_integer = 10;
		Power.e_display_mode = DISPLAY_ONLY_NUMBER_5;
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		Power.value_integer = 0;
		Power.e_display_mode = DISPLAY_ONLY_NUMBER_4;
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		HAL_Delay(1000);
		
		Power.value_integer = 10;
		Power.e_display_mode = DISPLAY_ONLY_NUMBER_4;
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		Power.value_integer = 0;
		Power.e_display_mode = DISPLAY_ONLY_NUMBER_3;
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		HAL_Delay(1000);
		
		Power.value_integer = 10;
		Power.e_display_mode = DISPLAY_ONLY_NUMBER_3;
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		Power.value_integer = 0;
		Power.e_display_mode = DISPLAY_ONLY_NUMBER_2;
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		HAL_Delay(1000);
		
		Power.value_integer = 10;
		Power.e_display_mode = DISPLAY_ONLY_NUMBER_2;
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		Power.value_integer = 0;
		Power.e_display_mode = DISPLAY_ONLY_NUMBER_1;
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		HAL_Delay(1000);
		
		Power.value_integer = 10;
		Power.e_display_mode = DISPLAY_ONLY_NUMBER_1;
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		Power.flag_symbol_K = 1;
		Power.e_display_mode = DISPLAY_ONLY_SYMBOL_K;
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		HAL_Delay(1000);
		
		Power.flag_symbol_K = 0;
		Power.e_display_mode = DISPLAY_ONLY_SYMBOL_K;
		lcd_value_send(Eeye_lcd, LCD_EEYE_POWER, &Power);
		Consumption.value_integer = 0;
		Consumption.e_display_mode = DISPLAY_ONLY_NUMBER_5;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		HAL_Delay(1000);
		
		Consumption.value_integer = 10;
		Consumption.e_display_mode = DISPLAY_ONLY_NUMBER_5;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		Consumption.value_integer = 0;
		Consumption.e_display_mode = DISPLAY_ONLY_NUMBER_4;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		HAL_Delay(1000);
		
		Consumption.value_integer = 10;
		Consumption.e_display_mode = DISPLAY_ONLY_NUMBER_4;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		Consumption.value_integer = 0;
		Consumption.e_display_mode = DISPLAY_ONLY_NUMBER_3;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		HAL_Delay(1000);
		
		Consumption.value_integer = 10;
		Consumption.e_display_mode = DISPLAY_ONLY_NUMBER_3;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		Consumption.value_integer = 0;
		Consumption.e_display_mode = DISPLAY_ONLY_NUMBER_2;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		HAL_Delay(1000);
		
		Consumption.value_integer = 10;
		Consumption.e_display_mode = DISPLAY_ONLY_NUMBER_2;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		Consumption.value_integer = 0;
		Consumption.e_display_mode = DISPLAY_ONLY_NUMBER_1;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		HAL_Delay(1000);
		
		Consumption.value_integer = 10;
		Consumption.e_display_mode = DISPLAY_ONLY_NUMBER_1;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		Consumption.flag_symbol_K = 1;
		Consumption.e_display_mode = DISPLAY_ONLY_SYMBOL_K;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		HAL_Delay(1000);
		
		Consumption.flag_symbol_K = 0;
		Consumption.e_display_mode = DISPLAY_ONLY_SYMBOL_K;
		lcd_value_send(Eeye_lcd, LCD_EEYE_CONSUMPTION, &Consumption);
		Pf.value_integer = 0;
		Pf.e_display_mode = DISPLAY_ONLY_NUMBER_3;
		lcd_value_send(Eeye_lcd, LCD_EEYE_PF, &Pf);
		HAL_Delay(1000);
		
		Pf.value_integer = 10;
		Pf.e_display_mode = DISPLAY_ONLY_NUMBER_3;
		lcd_value_send(Eeye_lcd, LCD_EEYE_PF, &Pf);
		Pf.value_integer = 0;
		Pf.e_display_mode = DISPLAY_ONLY_NUMBER_2;
		lcd_value_send(Eeye_lcd, LCD_EEYE_PF, &Pf);
		HAL_Delay(1000);
		
		Pf.value_integer = 10;
		Pf.e_display_mode = DISPLAY_ONLY_NUMBER_2;
		lcd_value_send(Eeye_lcd, LCD_EEYE_PF, &Pf);
		Pf.value_integer = 0;
		Pf.e_display_mode = DISPLAY_ONLY_NUMBER_1;
		lcd_value_send(Eeye_lcd, LCD_EEYE_PF, &Pf);
		HAL_Delay(1000);
		
		Pf.value_integer = 10;
		Pf.e_display_mode = DISPLAY_ONLY_NUMBER_1;
		lcd_value_send(Eeye_lcd, LCD_EEYE_PF, &Pf);
		Temperature.value_integer = 0;
		Temperature.e_display_mode = DISPLAY_ONLY_NUMBER_4;
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		HAL_Delay(1000);
		
		Temperature.value_integer = 10;
		Temperature.e_display_mode = DISPLAY_ONLY_NUMBER_4;
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		Temperature.value_integer = 0;
		Temperature.e_display_mode = DISPLAY_ONLY_NUMBER_3;
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		HAL_Delay(1000);
		
		Temperature.value_integer = 10;
		Temperature.e_display_mode = DISPLAY_ONLY_NUMBER_3;
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		Temperature.value_integer = 0;
		Temperature.e_display_mode = DISPLAY_ONLY_NUMBER_2;
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		HAL_Delay(1000);
		
		Temperature.value_integer = 10;
		Temperature.e_display_mode = DISPLAY_ONLY_NUMBER_2;
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		Temperature.value_integer = 0;
		Temperature.e_display_mode = DISPLAY_ONLY_NUMBER_1;
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		HAL_Delay(1000);
		
		Temperature.value_integer = 10;
		Temperature.e_display_mode = DISPLAY_ONLY_NUMBER_1;
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		Temperature.value_integer = 1;
		Temperature.e_display_mode = DISPLAY_ONLY_SYMBOL_C;
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		HAL_Delay(1000);
		
		Temperature.value_integer = 0;
		Temperature.e_display_mode = DISPLAY_ONLY_SYMBOL_C;
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		Temperature.value_integer = 1;
		Temperature.e_display_mode = DISPLAY_ONLY_SYMBOL_F;
		lcd_value_send(Eeye_lcd, LCD_EEYE_TEMPERATURE, &Temperature);
		HAL_Delay(1000);
	}
}
