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
const uint8_t seg_no[10][7] = {
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

static void consumption_display(struct device *Dev, struct lcd_value *Value)
{
	seg_show(Dev, 24, (uint8_t *)seg_no[(Value->value_integer % 10000) / 1000], 1);
	seg_show(Dev, 26, (uint8_t *)seg_no[(Value->value_integer % 1000) / 100], 0);
	seg_show(Dev, 28, (uint8_t *)seg_no[(Value->value_integer % 100) / 10], 1);
	seg_show(Dev, 30, (uint8_t *)seg_no[(Value->value_integer % 10) / 1], 0);
}

static void power_display(struct device *Dev, struct lcd_value *Value)
{
	seg_show(Dev, 16, (uint8_t *)seg_no[6], 1);
	seg_show(Dev, 18, (uint8_t *)seg_no[5], 1);
	seg_show(Dev, 20, (uint8_t *)seg_no[4], 0);
	seg_show(Dev, 22, (uint8_t *)seg_no[3], 0);
}

static void current_display(struct device *Dev, struct lcd_value *Value)
{
	seg_show(Dev, 8,  (uint8_t *)seg_no[8], 1);
	seg_show(Dev, 10, (uint8_t *)seg_no[9], 1);
	seg_show(Dev, 12, (uint8_t *)seg_no[0], 1);
	seg_show(Dev, 14, (uint8_t *)seg_no[1], 1);
}

static void voltage_display(struct device *Dev, struct lcd_value *Value)
{
	seg_show(Dev, 2, (uint8_t *)seg_no[(Value->value_integer % 1000) / 100], 0);
	seg_show(Dev, 4, (uint8_t *)seg_no[(Value->value_integer % 100) / 10], 1);
	seg_show(Dev, 6, (uint8_t *)seg_no[(Value->value_integer % 10) / 1], 1);
}

static int pz_lcd_value_send(struct device *Dev, enum lcd_type e_type, struct lcd_value *Value)
{
	struct pz_lcd_data *D_data = Dev->data;
	uint16_t i;
	
	switch (e_type) {
		case LCD_SET_ALL:
			for(i = 0; i < 0x3F; i++) {                   //A5~A0: 00111111
				seg7_write_data_4(D_data->Ht1621, i, 0x0F); //D3~D0: 00001111 set 1
			}
			break;
		case LCD_CLEAN_ALL:
			for(i = 0; i < 0x3F; i++) {                   //A5~A0: 00111111
				seg7_write_data_4(D_data->Ht1621, i, 0x00); //D3~D0: 00001111 set 0
			}
			break;
		case LCD_PZ_VOLTAGE:
			voltage_display(Dev, Value);
			break;
		case LCD_PZ_CURRENT:
			current_display(Dev, Value);
			break;
		case LCD_PZ_POWER:
			power_display(Dev, Value);
			break;
		case LCD_PZ_CONSUMPTION:
			consumption_display(Dev, Value);
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
