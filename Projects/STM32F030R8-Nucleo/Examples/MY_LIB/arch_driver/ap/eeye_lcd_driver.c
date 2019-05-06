/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "device.h"
#include "ht1622_driver.h"
#include "api_seg7_common.h"
#include "eeye_lcd_driver.h"
#include "api_lcd_common.h"


//abcdefg
const uint8_t seg_no[11][7] = {
	{1,1,1,1,1,1,0}, //0 *(seg_no+0)+0, *(seg_no+0)+1, ....
	{0,1,1,0,0,0,0}, //1 *(seg_no+1)+0, *(seg_no+1)+1, ....
	{1,1,0,1,1,0,1}, //2 *(seg_no+2)+0, *(seg_no+2)+1, ....
	{1,1,1,1,0,0,1}, //3 *(seg_no+3)+0, *(seg_no+3)+1, ....
	{0,1,1,0,0,1,1}, //4 *(seg_no+4)+0, *(seg_no+4)+1, ....
	{1,0,1,1,0,1,1}, //5   seg_no[5]+0,   seg_no[5]+1, ....
	{1,0,1,1,1,1,1}, //6   seg_no[6]+0,   seg_no[6]+1, ....
	{1,1,1,0,0,0,0}, //7   seg_no[7]+0,   seg_no[7]+1, ....
	{1,1,1,1,1,1,1}, //8   seg_no[8]+0,   seg_no[8]+1, ....
	{1,1,1,1,0,1,1}, //9   seg_no[9]+0,   seg_no[9]+1, ....
	{0,0,0,0,0,0,0}, //" "
};

static void seg7(struct device *Dev, enum seg7_eeye e_seg7, uint8_t a, uint8_t b, uint8_t c,
	                                    uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t symbol)
{
	struct eeye_lcd_data *D_data = Dev->data;
	static uint8_t c12, c13, c14, c1, c2, c9, c3;
	static uint8_t e12, e13, e14, e1, e2, e9, e3;
	static uint8_t d12, d13, d14, d1, d2, d9, d3;
	
	if(e_seg7 == SEG_12) {
		c12 = c;
		e12 = e;
		d12 = d;
	}
	
	if(e_seg7 == SEG_13) {
		c13 = c;
		e13 = e;
		d13 = d;
	}
	
	if(e_seg7 == SEG_14) {
		c14 = c;
		e14 = e;
		d14 = d;
	}
	
	if(e_seg7 == SEG_1) {
		c1 = c;
		e1 = e;
		d1 = d;
	}
	
	if(e_seg7 == SEG_2) {
		c2 = c;
		e2 = e;
		d2 = d;
	}
	
	if(e_seg7 == SEG_9) {
		c9 = c;
		e9 = e;
		d9 = d;
	}
	
	if(e_seg7 == SEG_3) {
		c3 = c;
		e3 = e;
		d3 = d;
	}
	
	if(e_seg7 == SEG_17) {
		seg7_write_data_bit_4(D_data->Ht1622, SEG_12, c12, e12, d12, a);
		seg7_write_data_bit_4(D_data->Ht1622, SEG_13, c13, e13, d13, b);
		seg7_write_data_bit_4(D_data->Ht1622, SEG_14, c14, e14, d14, c);
		seg7_write_data_bit_4(D_data->Ht1622, SEG_1,  c1,  e1,  d1,  d);
		seg7_write_data_bit_4(D_data->Ht1622, SEG_2,  c2,  e2,  d2,  e);
		seg7_write_data_bit_4(D_data->Ht1622, SEG_9,  c9,  e9,  d9,  f);
		seg7_write_data_bit_4(D_data->Ht1622, SEG_3,  c3,  e3,  d3,  g);
	}else {
		seg7_write_data_bit_4(D_data->Ht1622, e_seg7+0, c, e, d, symbol);
		seg7_write_data_bit_4(D_data->Ht1622, e_seg7+1, a, b, f, g);
	}
}

static void seg_show(struct device *Dev, enum seg7_eeye e_seg7, uint8_t *number, uint8_t symbol)
{
	static uint8_t a, b, c, d, e, f, g;
	
	if(e_seg7 == SEG_17) {
		a = number[0];
		b = number[1];
		c = number[2];
		d = number[3];
		e = number[4];
		f = number[5];
		g = number[6];
	}
	
	if(e_seg7 == SEG_12) {
		symbol = a;
	}
	
	if(e_seg7 == SEG_13) {
		symbol = b;
	}
	
	if(e_seg7 == SEG_14) {
		symbol = c;
	}
	
	if(e_seg7 == SEG_1) {
		symbol = d;
	}
	
	if(e_seg7 == SEG_2) {
		symbol = e;
	}
	
	if(e_seg7 == SEG_9) {
		symbol = f;
	}
	
	if(e_seg7 == SEG_3) {
		symbol = g;
	}
	
	seg7(Dev, e_seg7, number[0], number[1], number[2], number[3], number[4], number[5], number[6], symbol);
}

static void temperature_calculate(uint8_t temperature[4], uint8_t *dot, struct lcd_value *Value)
{
	if(Value->value_integer > 999) {
		*dot = 0;
		temperature[3] = (Value->value_integer % 10000) / 1000;
		temperature[2] = (Value->value_integer % 1000) / 100;
		temperature[1] = (Value->value_integer % 100) / 10;
		temperature[0] = Value->value_integer % 10;
	}else {
		*dot = 1;
		if(Value->value_integer < 100) {
			temperature[3] = 10; //no display number
		}else {
			temperature[3] = (Value->value_integer % 1000) / 100;
		}
		if(Value->value_integer < 10) {
			temperature[2] = 10; //no display number
		}else {
			temperature[2] = (Value->value_integer % 100) / 10;
		}
		temperature[1] = Value->value_integer % 10;
		temperature[0] = Value->value_decimal % 10;
	}
}

static void pf_calculate(uint8_t pf[3], uint8_t *dot, struct lcd_value *Value)
{
	*dot = 1;
	pf[2] = Value->value_integer % 10;
	if(Value->value_decimal > 9) {
		pf[1] = (Value->value_decimal % 100) / 10;
		pf[0] = Value->value_decimal % 10;
	}else {
		pf[1] = Value->value_decimal;
		pf[0] = 10; //no display number
	}
}

static void consumption_calculate(uint8_t energy[5], uint8_t *dot, struct lcd_value *Value)
{
	if(Value->value_integer > 9999) {
		*dot = 0;
		energy[4] = (Value->value_integer % 100000) / 10000;
		energy[3] = (Value->value_integer % 10000) / 1000;
		energy[2] = (Value->value_integer % 1000) / 100;
		energy[1] = (Value->value_integer % 100) / 10;
		energy[0] = Value->value_integer % 10;
	}else {
		*dot = 1;
		if(Value->value_integer < 1000) {
			energy[4] = 10; //no display number
		}else {
			energy[4] = (Value->value_integer % 10000) / 1000;
		}
		if(Value->value_integer < 100) {
			energy[3] = 10; //no display number
		}else {
			energy[3] = (Value->value_integer % 1000) / 100;
		}
		if(Value->value_integer < 10) {
			energy[2] = 10; //no display number
		}else {
			energy[2] = (Value->value_integer % 100) / 10;
		}
		energy[1] = Value->value_integer % 10;
		energy[0] = Value->value_decimal % 10;
	}
}

static void power_calculate(uint8_t power[5], uint8_t *dot, struct lcd_value *Value)
{
	if(Value->value_integer > 9999) {
		*dot = 0;
		power[4] = (Value->value_integer % 100000) / 10000;
		power[3] = (Value->value_integer % 10000) / 1000;
		power[2] = (Value->value_integer % 1000) / 100;
		power[1] = (Value->value_integer % 100) / 10;
		power[0] = Value->value_integer % 10;
	}else {
		*dot = 1;
		if(Value->value_integer < 1000) {
			power[4] = 10; //no display number
		}else {
			power[4] = (Value->value_integer % 10000) / 1000;
		}
		if(Value->value_integer < 100) {
			power[3] = 10; //no display number
		}else {
			power[3] = (Value->value_integer % 1000) / 100;
		}
		if(Value->value_integer < 10) {
			power[2] = 10; //no display number
		}else {
			power[2] = (Value->value_integer % 100) / 10;
		}
		power[1] = Value->value_integer % 10;
		power[0] = Value->value_decimal % 10;
	}
}

static void current_calculate(uint8_t current[4], uint8_t *dot, struct lcd_value *Value)
{
	if(Value->value_integer > 99) {
		*dot = 0;
		if(Value->value_integer < 1000) {
			current[3] = 10; //no display number
		}else {
			current[3] = (Value->value_integer % 10000) / 1000;
		}
		current[2] = (Value->value_integer % 1000) / 100;
		current[1] = (Value->value_integer % 100) / 10;
		current[0] = Value->value_integer % 10;
	}else {
		*dot = 1;
		if(Value->value_integer < 10) {
			current[3] = 10; //no display number
		}else {
			current[3] = (Value->value_integer % 100) / 10;
		}
		current[2] = Value->value_integer % 10;
		if(Value->value_decimal > 9) {
			current[1] = (Value->value_decimal % 100) / 10;
			current[0] = Value->value_decimal % 10;
		}else {
			current[1] = Value->value_decimal;
			current[0] = 10; //no display number
		}
	}
}

static void voltage_calculate(uint8_t voltage[4], uint8_t *dot, struct lcd_value *Value)
{
	if(Value->value_integer > 999) {
		*dot = 0;
		voltage[3] = (Value->value_integer % 10000) / 1000;
		voltage[2] = (Value->value_integer % 1000) / 100;
		voltage[1] = (Value->value_integer % 100) / 10;
		voltage[0] = Value->value_integer % 10;
	}else {
		*dot = 1;
		if(Value->value_integer < 100) {
			voltage[3] = 10; //no display number
		}else {
			voltage[3] = (Value->value_integer % 1000) / 100;
		}
		if(Value->value_integer < 10) {
			voltage[2] = 10; //no display number
		}else {
			voltage[2] = (Value->value_integer % 100) / 10;
		}
		voltage[1] = Value->value_integer % 10;
		voltage[0] = Value->value_decimal % 10;
	}
}

static void display_update(struct device *Dev, enum lcd_type e_type, struct lcd_value *Value)
{
	static uint8_t voltage[4];
	static uint8_t current[4];
	static uint8_t power[5];
	static uint8_t energy[5];
	static uint8_t pf[3];
	static uint8_t temperature[4];
	static uint8_t voltage_dot;
	static uint8_t current_dot;
	static uint8_t power_dot;
	static uint8_t energy_dot;
	static uint8_t pf_dot;
	static uint8_t temperature_dot;
	static uint8_t power_K;
	static uint8_t energy_K;
	static uint8_t temperature_C;
	static uint8_t temperature_F;
	
	static uint8_t voltage_V;
	static uint8_t current_A;
	static uint8_t power_W;
	static uint8_t energy_Wh;
	static uint8_t pf_PF;
	
	switch (e_type) {
		case LCD_EEYE_VOLTAGE:
			if(Value->e_display_mode == DISPLAY_NORMAL) {
				voltage_V = 1;
				voltage_calculate(voltage, &voltage_dot, Value);
			}else if(Value->e_display_mode == DISPLAY_MASK_NUMBER) {
				voltage_V = 1;
				voltage[0] = 10;
				voltage[1] = 10;
				voltage[2] = 10;
				voltage[3] = 10;
				voltage_dot = 0;
			}else if(Value->e_display_mode == DISPLAY_MASK_TEXT) {
				voltage_V = 0;
				voltage_calculate(voltage, &voltage_dot, Value);
			}else if(Value->e_display_mode == DISPLAY_MASK_NUMBER_TEXT) {
				voltage_V = 0;
				voltage[0] = 10;
				voltage[1] = 10;
				voltage[2] = 10;
				voltage[3] = 10;
				voltage_dot = 0;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_1) {
				voltage[0] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_2) {
				voltage[1] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_3) {
				voltage[2] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_4) {
				voltage[3] = Value->value_integer;
			}
			break;
			
		case LCD_EEYE_CURRENT:
			if(Value->e_display_mode == DISPLAY_NORMAL) {
				current_A = 1;
				current_calculate(current, &current_dot, Value);
			}else if(Value->e_display_mode == DISPLAY_MASK_NUMBER) {
				current_A = 1;
				current[0] = 10;
				current[1] = 10;
				current[2] = 10;
				current[3] = 10;
				current_dot = 0;
			}else if(Value->e_display_mode == DISPLAY_MASK_TEXT) {
				current_A = 0;
				current_calculate(current, &current_dot, Value);
			}else if(Value->e_display_mode == DISPLAY_MASK_NUMBER_TEXT) {
				current_A = 0;
				current[0] = 10;
				current[1] = 10;
				current[2] = 10;
				current[3] = 10;
				current_dot = 0;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_1) {
				current[0] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_2) {
				current[1] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_3) {
				current[2] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_4) {
				current[3] = Value->value_integer;
			}
			break;
			
		case LCD_EEYE_POWER:
			if(Value->e_display_mode == DISPLAY_NORMAL) {
				power_W = 1;
				power_K = Value->flag_symbol_K;
				power_calculate(power, &power_dot, Value);
			}else if(Value->e_display_mode == DISPLAY_MASK_NUMBER) {
				power_W = 1;
				power[0] = 10;
				power[1] = 10;
				power[2] = 10;
				power[3] = 10;
				power[4] = 10;
				power_dot = 0;
				power_K = 0;
			}else if(Value->e_display_mode == DISPLAY_MASK_TEXT) {
				power_W = 0;
				power_K = Value->flag_symbol_K;
				power_calculate(power, &power_dot, Value);
			}else if(Value->e_display_mode == DISPLAY_MASK_NUMBER_TEXT) {
				power_W = 0;
				power[0] = 10;
				power[1] = 10;
				power[2] = 10;
				power[3] = 10;
				power[4] = 10;
				power_dot = 0;
				power_K = 0;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_1) {
				power[0] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_2) {
				power[1] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_3) {
				power[2] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_4) {
				power[3] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_5) {
				power[4] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_SYMBOL_K) {
				power_K = Value->flag_symbol_K;
			}
			break;
			
		case LCD_EEYE_CONSUMPTION:
			if(Value->e_display_mode == DISPLAY_NORMAL) {
				energy_Wh = 1;
				energy_K = Value->flag_symbol_K;
				consumption_calculate(energy, &energy_dot, Value);
			}else if(Value->e_display_mode == DISPLAY_MASK_NUMBER) {
				energy_Wh = 1;
				energy[0] = 10;
				energy[1] = 10;
				energy[2] = 10;
				energy[3] = 10;
				energy[4] = 10;
				energy_dot = 0;
				energy_K = 0;
			}else if(Value->e_display_mode == DISPLAY_MASK_TEXT) {
				energy_Wh = 0;
				energy_K = Value->flag_symbol_K;
				consumption_calculate(energy, &energy_dot, Value);
			}else if(Value->e_display_mode == DISPLAY_MASK_NUMBER_TEXT) {
				energy_Wh = 0;
				energy[0] = 10;
				energy[1] = 10;
				energy[2] = 10;
				energy[3] = 10;
				energy[4] = 10;
				energy_dot = 0;
				energy_K = 0;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_1) {
				energy[0] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_2) {
				energy[1] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_3) {
				energy[2] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_4) {
				energy[3] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_5) {
				energy[4] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_SYMBOL_K) {
				energy_K = Value->flag_symbol_K;
			}
			break;
			
		case LCD_EEYE_PF:
			if(Value->e_display_mode == DISPLAY_NORMAL) {
				pf_PF = 1;
				pf_calculate(pf, &pf_dot, Value);
			}else if(Value->e_display_mode == DISPLAY_MASK_NUMBER) {
				pf_PF = 1;
				pf[0] = 10;
				pf[1] = 10;
				pf[2] = 10;
				pf_dot = 0;
			}else if(Value->e_display_mode == DISPLAY_MASK_TEXT) {
				pf_PF = 0;
				pf_calculate(pf, &pf_dot, Value);
			}else if(Value->e_display_mode == DISPLAY_MASK_NUMBER_TEXT) {
				pf_PF = 0;
				pf[0] = 10;
				pf[1] = 10;
				pf[2] = 10;
				pf_dot = 0;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_1) {
				pf[0] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_2) {
				pf[1] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_3) {
				pf[2] = Value->value_integer;
			}
			break;
			
		case LCD_EEYE_TEMPERATURE:
			if(Value->e_display_mode == DISPLAY_NORMAL) {
				temperature_C = Value->flag_symbol_C;
				temperature_F = Value->flag_symbol_F;
				temperature_calculate(temperature, &temperature_dot, Value);
			}else if(Value->e_display_mode == DISPLAY_MASK_NUMBER) {
				temperature_C = Value->flag_symbol_C;
				temperature_F = Value->flag_symbol_F;
				temperature[0] = 10;
				temperature[1] = 10;
				temperature[2] = 10;
				temperature[3] = 10;
				temperature_dot = 0;
			}else if(Value->e_display_mode == DISPLAY_MASK_TEXT) {
				temperature_C = 0;
				temperature_F = 0;
				temperature_calculate(temperature, &temperature_dot, Value);
			}else if(Value->e_display_mode == DISPLAY_MASK_NUMBER_TEXT) {
				temperature_C = 0;
				temperature_F = 0;
				temperature[0] = 10;
				temperature[1] = 10;
				temperature[2] = 10;
				temperature[3] = 10;
				temperature_dot = 0;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_1) {
				temperature[0] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_2) {
				temperature[1] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_3) {
				temperature[2] = Value->value_integer;
			}else if(Value->e_display_mode == DISPLAY_ONLY_NUMBER_4) {
				temperature[3] = Value->value_integer;
			}
			break;
			
		default:
			break;
	}
	
	seg_show(Dev, SEG_1,  (uint8_t *)seg_no[voltage[3]], 0);
	seg_show(Dev, SEG_2,  (uint8_t *)seg_no[voltage[2]], 0);
	seg_show(Dev, SEG_3,  (uint8_t *)seg_no[voltage[1]], 0);
	seg_show(Dev, SEG_4,  (uint8_t *)seg_no[voltage[0]], voltage_dot);
	
	seg_show(Dev, SEG_5,  (uint8_t *)seg_no[current[3]], voltage_V);
	seg_show(Dev, SEG_6,  (uint8_t *)seg_no[current[2]], current_dot);
	seg_show(Dev, SEG_7,  (uint8_t *)seg_no[current[1]], 0);
	seg_show(Dev, SEG_8,  (uint8_t *)seg_no[current[0]], current_A);
	
	seg_show(Dev, SEG_12, (uint8_t *)seg_no[power[4]], 0);
	seg_show(Dev, SEG_13, (uint8_t *)seg_no[power[3]], 0);
	seg_show(Dev, SEG_14, (uint8_t *)seg_no[power[2]], 0);
	seg_show(Dev, SEG_15, (uint8_t *)seg_no[power[1]], power_dot);
	seg_show(Dev, SEG_16, (uint8_t *)seg_no[power[0]], power_K);
	
	seg_show(Dev, SEG_21, (uint8_t *)seg_no[energy[4]], 0);
	seg_show(Dev, SEG_22, (uint8_t *)seg_no[energy[3]], power_W);
	seg_show(Dev, SEG_23, (uint8_t *)seg_no[energy[2]], energy_Wh);
	seg_show(Dev, SEG_24, (uint8_t *)seg_no[energy[1]], energy_dot);
	seg_show(Dev, SEG_25, (uint8_t *)seg_no[energy[0]], energy_K);
	
	seg_show(Dev, SEG_9,  (uint8_t *)seg_no[pf[2]], 0);
	seg_show(Dev, SEG_10, (uint8_t *)seg_no[pf[1]], pf_dot);
	seg_show(Dev, SEG_11, (uint8_t *)seg_no[pf[0]], pf_PF);
	
	seg_show(Dev, SEG_17, (uint8_t *)seg_no[temperature[3]], 0);
	seg_show(Dev, SEG_18, (uint8_t *)seg_no[temperature[2]], temperature_C);
	seg_show(Dev, SEG_19, (uint8_t *)seg_no[temperature[1]], temperature_F);
	seg_show(Dev, SEG_20, (uint8_t *)seg_no[temperature[0]], temperature_dot);
}

static int eeye_lcd_value_send(struct device *Dev, enum lcd_type e_type, struct lcd_value *Value)
{
	struct eeye_lcd_data *D_data = Dev->data;
	uint16_t i;
	
	switch (e_type) {
		case LCD_SET_ALL:
			for(i = 0; i < 0x3F; i++) {                   //A5~A0: 00111111
				seg7_write_data_4(D_data->Ht1622, i, 0x0F); //D3~D0: 00001111 set 1
				HAL_Delay(1);
			}
			break;
			
		case LCD_CLEAN_ALL:
			for(i = 0; i < 0x3F; i++) {                   //A5~A0: 00111111
				seg7_write_data_4(D_data->Ht1622, i, 0x00); //D3~D0: 00001111 set 0
				HAL_Delay(1);
			}
			break;
			
		case LCD_EEYE_VOLTAGE:
		case LCD_EEYE_CURRENT:
		case LCD_EEYE_POWER:
		case LCD_EEYE_CONSUMPTION:
		case LCD_EEYE_PF:
		case LCD_EEYE_TEMPERATURE:
			display_update(Dev, e_type, Value);
			break;
			
		default:
			return -1;
	}
	return 0;
}

static const struct lcd_common_api Eeye_lcd_api = {
	.value_send = eeye_lcd_value_send,
};

static struct eeye_lcd_data Eeye_lcd_data;

static int eeye_lcd_device_init(struct device *Dev)
{
	struct eeye_lcd_data *D_data = Dev->data;
	
	D_data->Ht1622 = ht1622_device_binding();
	seg7_init(D_data->Ht1622);
	printf("EEYE LCD device init\r\n");
	
	return 0;
}

struct device Eeye_lcd = {
	.api  = &Eeye_lcd_api,
	.data = &Eeye_lcd_data,
	.init = eeye_lcd_device_init,
};

struct device* eeye_lcd_device_binding(void)
{
	return &Eeye_lcd;
}
