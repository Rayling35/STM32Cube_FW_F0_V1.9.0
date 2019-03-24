/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "myconf.h"
#include "ht1621.h"


#define  CS_LOW        HT1621_CS_OUTPUT_LOW
#define  CS_HIGH       HT1621_CS_OUTPUT_HIGH
#define  WR_LOW        HT1621_WR_OUTPUT_LOW
#define  WR_HIGH       HT1621_WR_OUTPUT_HIGH
#define  DATA_LOW      HT1621_DATA_OUTPUT_LOW
#define  DATA_HIGH     HT1621_DATA_OUTPUT_HIGH

static void addr_cmd_bit(uint8_t data, uint8_t cnt)
{
	uint8_t i;
	for(i = 0; i < cnt; i++) {
		WR_LOW;
		if(data & 0x80) //10000000 高位元在左,向左比對
			DATA_HIGH;
		else
			DATA_LOW;
		WR_HIGH;
		data <<= 1; //向左移
	}
}

static void data_bit(uint8_t data, uint8_t cnt)
{
	uint8_t i;
	for(i = 0; i < cnt; i++) {
		WR_LOW;
		if(data & 0x01) //00000001 高位元在右,向右比對
			DATA_HIGH;
		else
			DATA_LOW;
		WR_HIGH;
		data >>= 1; //向右移
	}
}

void send_command(uint8_t cmd)
{
	CS_LOW;
	addr_cmd_bit(0x80, 3); //寫入Command code:100
	addr_cmd_bit(cmd, 9);  //第9次隨意
	CS_HIGH;
	__nop();
}

/* seg_addr: A5~A0 (0011 1111) 0x3F
   com_data: D3~D0 (0000 1111) 0x0F */
void write_seg_data_4(uint8_t seg_addr, uint8_t com_data)
{
	seg_addr <<= 2;
	CS_LOW;
	addr_cmd_bit(0xA0, 3);     //寫入Command code:101
	addr_cmd_bit(seg_addr, 6); //addr高6位元寫入
	data_bit(com_data, 4);     //data低4位元寫入
	CS_HIGH;
	__nop();
}

void write_seg_data_44(uint8_t seg_addr, uint8_t *com_data, uint16_t count)
{
	uint16_t i;
	seg_addr <<= 2;
	CS_LOW;
	addr_cmd_bit(0xA0, 3);
	addr_cmd_bit(seg_addr, 6);
	for(i = 0; i < count; i++, com_data++) {
		data_bit(*com_data, 8); //連續寫入,com_data的MSB與LSB 4bit都帶值
	}
	CS_HIGH;
	__nop();
}

void write_seg_data_bit_4(uint8_t seg_addr, uint8_t d3, uint8_t d2, uint8_t d1, uint8_t d0)
{
	write_seg_data_4(seg_addr, d3<<3 | d2<<2 | d1<<1 | d0<<0);
}

void set_all(void)
{
	uint16_t i;
	for(i = 0; i < 0x3F; i++) {  //A5~A0: 00111111
		write_seg_data_4(i, 0x0F); //D3~D0: 00001111 set 1
	}
}

void clean_all(void)
{
	uint16_t i;
	for(i = 0; i < 0x3F; i++) {  //A5~A0: 00111111
		write_seg_data_4(i, 0x00); //D3~D0: 00001111 set 0
	}
}

void ht1621_init(void)
{
	send_command(BIAS);
	send_command(RC256);
	send_command(SYSEN);
	send_command(LCDON);
}
