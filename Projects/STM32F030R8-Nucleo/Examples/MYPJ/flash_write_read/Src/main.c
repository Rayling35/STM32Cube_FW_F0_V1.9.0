/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "stm32f0xx_hal.h"
#include "uart_printf.h"
#include "flash_internal.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	uint8_t hello[] = "Hello how are you ";
	uint8_t hi[] = "Hi nice to meet you";
	uint8_t temp_1[37];
	uint8_t temp_2[20];
	
	flash_internal_erase(PAGE_26_1KB_8006800);
	flash_data_write(PAGE_26_1KB_8006800, 0, hello, 18);
	flash_data_write(PAGE_26_1KB_8006800, 18, hi, 19);
	flash_data_read(PAGE_26_1KB_8006800, 0, temp_1, 37);
	flash_data_read(PAGE_26_1KB_8006800, 12, temp_2, 20);
	printf("%s\r\n", temp_1);
	printf("%s\r\n", temp_2);
	
	flash_internal_erase(PAGE_16_1KB_8004000);
	flash_internal_write(PROGRAM_DOUBLEWORD, PAGE_16_1KB_8004000, 0, 0x11abcdef12345678);
	flash_internal_write(PROGRAM_DOUBLEWORD, PAGE_16_1KB_8004000, 1016, 0x12abcdef12345678);
	printf("0x%llx\r\n", flash_internal_read_doubleword(PAGE_16_1KB_8004000, 0));
	printf("0x%llx\r\n", flash_internal_read_doubleword(PAGE_16_1KB_8004000, 1016));
	
	flash_internal_erase(PAGE_16_1KB_8004000);
	flash_internal_write(PROGRAM_WORD, PAGE_16_1KB_8004000, 0, 0x11abcdef);
	flash_internal_write(PROGRAM_WORD, PAGE_16_1KB_8004000, 1020, 0x12abcdef);
	printf("0x%x\r\n", flash_internal_read_word(PAGE_16_1KB_8004000, 0));
	printf("0x%x\r\n", flash_internal_read_word(PAGE_16_1KB_8004000, 1020));
	
	flash_internal_erase(PAGE_16_1KB_8004000);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_16_1KB_8004000, 0, 0x11ab);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_16_1KB_8004000, 1022, 0x12ab);
	printf("0x%x\r\n", flash_internal_read_halfword(PAGE_16_1KB_8004000, 0));
	printf("0x%x\r\n", flash_internal_read_halfword(PAGE_16_1KB_8004000, 1022));
	
	
	flash_internal_erase(PAGE_16_1KB_8004000);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_16_1KB_8004000, 0x0, 161);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_16_1KB_8004000, 0x3FE, 162);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_16_1KB_8004000, 0x0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_16_1KB_8004000, 0x3FE));
	
	flash_internal_erase(PAGE_18_1KB_8004800);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_18_1KB_8004800, 0x0, 181);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_18_1KB_8004800, 0x3FE, 182);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_18_1KB_8004800, 0x0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_18_1KB_8004800, 0x3FE));
	
	flash_internal_erase(PAGE_21_1KB_8005400);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_21_1KB_8005400, 0, 211);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_21_1KB_8005400, 1022, 212);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_21_1KB_8005400, 0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_21_1KB_8005400, 1022));
	
	flash_internal_erase(PAGE_23_1KB_8005C00);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_23_1KB_8005C00, 0, 231);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_23_1KB_8005C00, 1022, 232);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_23_1KB_8005C00, 0x0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_23_1KB_8005C00, 1022));
	
	flash_internal_erase(PAGE_26_1KB_8006800);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_26_1KB_8006800, 0, 261);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_26_1KB_8006800, 1022, 262);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_26_1KB_8006800, 0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_26_1KB_8006800, 1022));
	
	flash_internal_erase(PAGE_31_1KB_8007C00);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_31_1KB_8007C00, 0x0, 311);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_31_1KB_8007C00, 0x3FE, 312);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_31_1KB_8007C00, 0x0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_31_1KB_8007C00, 0x3FE));
	
	flash_internal_erase(PAGE_33_1KB_8008400);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_33_1KB_8008400, 0x0, 331);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_33_1KB_8008400, 0x3FE, 332);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_33_1KB_8008400, 0x0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_33_1KB_8008400, 0x3FE));
	
	flash_internal_erase(PAGE_36_1KB_8009000);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_36_1KB_8009000, 0x0, 361);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_36_1KB_8009000, 0x3FE, 362);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_36_1KB_8009000, 0x0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_36_1KB_8009000, 0x3FE));
	
	flash_internal_erase(PAGE_41_1KB_800A400);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_41_1KB_800A400, 0, 411);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_41_1KB_800A400, 1022, 412);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_41_1KB_800A400, 0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_41_1KB_800A400, 1022));
	
	flash_internal_erase(PAGE_43_1KB_800AC00);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_43_1KB_800AC00, 0, 431);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_43_1KB_800AC00, 1022, 432);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_43_1KB_800AC00, 0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_43_1KB_800AC00, 1022));
	
	flash_internal_erase(PAGE_46_1KB_800B800);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_46_1KB_800B800, 0, 461);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_46_1KB_800B800, 1022, 462);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_46_1KB_800B800, 0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_46_1KB_800B800, 1022));
	
	flash_internal_erase(PAGE_51_1KB_800CC00);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_51_1KB_800CC00, 0x0, 511);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_51_1KB_800CC00, 0x3FE, 512);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_51_1KB_800CC00, 0x0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_51_1KB_800CC00, 0x3FE));
	
	flash_internal_erase(PAGE_53_1KB_800D400);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_53_1KB_800D400, 0x0, 531);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_53_1KB_800D400, 0x3FE, 532);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_53_1KB_800D400, 0x0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_53_1KB_800D400, 0x3FE));
	
	flash_internal_erase(PAGE_56_1KB_800E000);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_56_1KB_800E000, 0x0, 561);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_56_1KB_800E000, 0x3FE, 562);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_56_1KB_800E000, 0x0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_56_1KB_800E000, 0x3FE));
	
	flash_internal_erase(PAGE_61_1KB_800F400);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_61_1KB_800F400, 0, 611);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_61_1KB_800F400, 1022, 612);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_61_1KB_800F400, 0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_61_1KB_800F400, 1022));
	
	flash_internal_erase(PAGE_63_1KB_800FC00);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_63_1KB_800FC00, 0, 631);
	flash_internal_write(PROGRAM_HALFWORD, PAGE_63_1KB_800FC00, 1022, 632);
	printf("%d\r\n", flash_internal_read_halfword(PAGE_63_1KB_800FC00, 0));
	printf("%d\r\n", flash_internal_read_halfword(PAGE_63_1KB_800FC00, 1022));
}
