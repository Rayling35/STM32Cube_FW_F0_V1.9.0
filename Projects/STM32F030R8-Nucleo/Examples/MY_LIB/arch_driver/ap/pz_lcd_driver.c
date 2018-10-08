/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "device.h"
#include "ht1621_driver.h"
#include "api_seg7_common.h"
#include "pz_lcd_driver.h"
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

static void seg7(struct device *Dev, uint16_t select, uint8_t a, uint8_t b, uint8_t c,
	               uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint16_t function)
{
	struct pz_lcd_data *D_data = Dev->data;
	
	if(select == 0 || select == 2 || select == 4 || select == 6 || select == 8 ||
		select == 10 || select == 12 || select == 14) {
			
			seg7_write_data_bit_4(D_data->Ht1621, select+0, a, f, e, d);
			seg7_write_data_bit_4(D_data->Ht1621, select+1, b, g, c, function);
			
	}else if(select == 16 || select == 18 || select == 20 || select == 22 || select == 24 ||
		select == 26 || select == 28 || select == 30) {
			
			seg7_write_data_bit_4(D_data->Ht1621, select+0, d, e, f, a);
			seg7_write_data_bit_4(D_data->Ht1621, select+1, function, c, g, b);
	}
}

//seg_show(Dev, 2, (uint8_t *)seg_no[0], 0); addr:2,4,6,8.. number:seg_no[0 1 2 3 4..]
static void seg_show(struct device *Dev, uint16_t addr, uint8_t *number, uint16_t function)
{
	seg7(Dev,addr,number[0],number[1],number[2],number[3],number[4],number[5],number[6],function);
}

static void display_update(struct device *Dev, enum lcd_type e_type, struct lcd_value *Value)
{
	static uint32_t voltage[4];
	static uint32_t current[4];
	static uint32_t power[4];
	static uint32_t energy[4];
	static uint8_t voltage_dot;
	static uint8_t current_dot;
	static uint8_t power_dot;
	static uint8_t power_K;
	static uint8_t energy_K;
	
	uint8_t voltage_text = 1;
	uint8_t voltage_V = 1;
	uint8_t current_text = 1;
	uint8_t current_A = 1;
	uint8_t power_text = 1;
	uint8_t power_W = 1;
	uint8_t energy_text = 1;
	uint8_t energy_Wh = 1;
	
	switch (e_type) {
		case LCD_PZ_VOLTAGE:
			if(Value->value_integer > 99) {
				voltage_dot = 0;
				if(Value->value_integer < 1000) {
					voltage[3] = 10; //no display number
				}else {
					voltage[3] = (Value->value_integer % 10000) / 1000;
				}
				voltage[2] = (Value->value_integer % 1000) / 100;
				voltage[1] = (Value->value_integer % 100) / 10;
				voltage[0] = Value->value_integer % 10;
			}else {
				voltage_dot = 1;
				if(Value->value_integer < 10) {
					voltage[3] = 10; //no display number
				}else {
					voltage[3] = (Value->value_integer % 100) / 10;
				}
				voltage[2] = Value->value_integer % 10;
				if(Value->value_decimal > 9) {
					voltage[1] = (Value->value_decimal % 100) / 10;
					voltage[0] = Value->value_decimal % 10;
				} else {
					voltage[1] = Value->value_decimal;
					voltage[0] = 10; //no display number
				}
			}
			break;
			
		case LCD_PZ_CURRENT:
			if(Value->value_integer > 99) {
				current_dot = 0;
				if(Value->value_integer < 1000) {
					current[3] = 10; //no display number
				}else {
					current[3] = (Value->value_integer % 10000) / 1000;
				}
				current[2] = (Value->value_integer % 1000) / 100;
				current[1] = (Value->value_integer % 100) / 10;
				current[0] = Value->value_integer % 10;
			}else {
				current_dot = 1;
				if(Value->value_integer < 10) {
					current[3] = 10; //no display number
				}else {
					current[3] = (Value->value_integer % 100) / 10;
				}
				current[2] = Value->value_integer % 10;
				if(Value->value_decimal > 9) {
					current[1] = (Value->value_decimal % 100) / 10;
					current[0] = Value->value_decimal % 10;
				} else {
					current[1] = Value->value_decimal;
					current[0] = 10; //no display number
				}
			}
			break;
			
		case LCD_PZ_POWER:
				power_K = Value->flag_symbol_K;
			if(Value->value_integer > 999) {
				power_dot = 0;
				power[3] = (Value->value_integer % 10000) / 1000;
				power[2] = (Value->value_integer % 1000) / 100;
				power[1] = (Value->value_integer % 100) / 10;
				power[0] = Value->value_integer % 10;
			}else {
				power_dot = 1;
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
			break;
			
		case LCD_PZ_CONSUMPTION:
			energy_K = Value->flag_symbol_K;
			if(Value->value_integer < 1000) {
				energy[3] = 10; //no display number
			}else {
				energy[3] = (Value->value_integer % 10000) / 1000;
			}
			if(Value->value_integer < 100) {
				energy[2] = 10; //no display number
			}else {
				energy[2] = (Value->value_integer % 1000) / 100;
			}
			if(Value->value_integer < 10) {
				energy[1] = 10; //no display number
			}else {
				energy[1] = (Value->value_integer % 100) / 10;
			}
			energy[0] = Value->value_integer % 10;
			break;
			
		default:
			break;
	}
	
	seg_show(Dev,  0, (uint8_t *)seg_no[voltage[3]], voltage_text);
	seg_show(Dev,  2, (uint8_t *)seg_no[voltage[2]], voltage_dot);
	seg_show(Dev,  4, (uint8_t *)seg_no[voltage[1]], 0);
	seg_show(Dev,  6, (uint8_t *)seg_no[voltage[0]], voltage_V);

	seg_show(Dev,  8, (uint8_t *)seg_no[current[3]], current_text);
	seg_show(Dev, 10, (uint8_t *)seg_no[current[2]], current_dot);
	seg_show(Dev, 12, (uint8_t *)seg_no[current[1]], 0);
	seg_show(Dev, 14, (uint8_t *)seg_no[current[0]], current_A);

	seg_show(Dev, 16, (uint8_t *)seg_no[power[3]], 0);
	seg_show(Dev, 18, (uint8_t *)seg_no[power[2]], power_text);
	seg_show(Dev, 20, (uint8_t *)seg_no[power[1]], power_dot);
	seg_show(Dev, 22, (uint8_t *)seg_no[power[0]], energy_text);

	seg_show(Dev, 24, (uint8_t *)seg_no[energy[3]], power_W);
	seg_show(Dev, 26, (uint8_t *)seg_no[energy[2]], power_K);
	seg_show(Dev, 28, (uint8_t *)seg_no[energy[1]], energy_Wh);
	seg_show(Dev, 30, (uint8_t *)seg_no[energy[0]], energy_K);
}

static int pz_lcd_value_send(struct device *Dev, enum lcd_type e_type, struct lcd_value *Value)
{
	struct pz_lcd_data *D_data = Dev->data;
	uint16_t i;
	
	switch (e_type) {
		case LCD_SET_ALL:
			for(i = 0; i < 0x3F; i++) {                   //A5~A0: 00111111
				seg7_write_data_4(D_data->Ht1621, i, 0x0F); //D3~D0: 00001111 set 1
				HAL_Delay(1);
			}
			break;
		case LCD_CLEAN_ALL:
			for(i = 0; i < 0x3F; i++) {                   //A5~A0: 00111111
				seg7_write_data_4(D_data->Ht1621, i, 0x00); //D3~D0: 00001111 set 0
				HAL_Delay(1);
			}
			break;
		case LCD_PZ_VOLTAGE:
		case LCD_PZ_CURRENT:
		case LCD_PZ_POWER:
		case LCD_PZ_CONSUMPTION:
			display_update(Dev, e_type, Value);
			break;
		default:
			return -1;
	}
	return 0;
}

static const struct lcd_common_api Pz_lcd_api = {
	.value_send = pz_lcd_value_send,
};

static struct pz_lcd_data Pz_lcd_data;

static int pz_lcd_device_init(struct device *Dev)
{
	struct pz_lcd_data *D_data = Dev->data;
	
	D_data->Ht1621 = ht1621_device_binding();
	seg7_init(D_data->Ht1621);
	printf("PZ LCD device init\r\n");
	
	return 0;
}

struct device Pz_lcd = {
	.api  = &Pz_lcd_api,
	.data = &Pz_lcd_data,
	.init = pz_lcd_device_init,
};

struct device* pz_lcd_device_binding(void)
{
	return &Pz_lcd;
}
