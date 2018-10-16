/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "flash_internal.h"


int flash_internal_erase(enum flash_page e_page)
{
	FLASH_EraseInitTypeDef Erase;
	uint32_t page_error = 0;
	uint16_t count;
	HAL_StatusTypeDef e_status;
	
	Erase.TypeErase   = FLASH_TYPEERASE_PAGES;
	Erase.PageAddress = e_page;
	Erase.NbPages     = 1;
	
	HAL_FLASH_Unlock();
	for(count = 0; count < 10; count++) {
		e_status = HAL_FLASHEx_Erase(&Erase, &page_error);
		if(e_status == HAL_OK) {
			break;
		}
	}
	HAL_FLASH_Lock();
	
	if(count >= 10) {
		printf("Flash erase fail!!\r\n");
		return 1;
	}else if(count >= 1) {
		printf("Flash erase %d times to success\r\n", count+1);
	}
	
	return 0;
}

int flash_internal_write(enum flash_type e_type, enum flash_page e_page, uint32_t offset, uint64_t data)
{
	uint32_t address = e_page + offset;
	
	HAL_FLASH_Unlock();
	if(HAL_FLASH_Program(e_type, address, data) != HAL_OK) {
		return 1;
	}
	HAL_FLASH_Lock();
	
	return 0;
}

uint16_t flash_internal_read_halfword(enum flash_page e_page, uint32_t offset)
{
	uint32_t address = e_page + offset;
	__IO uint16_t data = *(__IO uint16_t *)address;
	
	return data;
}

uint32_t flash_internal_read_word(enum flash_page e_page, uint32_t offset)
{
	uint32_t address = e_page + offset;
	__IO uint32_t data = *(__IO uint32_t *)address;
	
	return data;
}

uint64_t flash_internal_read_doubleword(enum flash_page e_page, uint32_t offset)
{
	uint32_t address = e_page + offset;
	__IO uint64_t data = *(__IO uint64_t *)address;
	
	return data;
}

int flash_data_write(enum flash_page e_page, uint32_t offset, uint8_t data[], uint16_t length)
{
	uint16_t i;
	uint16_t *temp = (uint16_t *)data;
	
	for(i = 0; i < (length/2 + length%2); i++) {
		flash_internal_write(PROGRAM_HALFWORD, e_page, offset + i, temp[i]);
		offset++;
	}
	
	return 0;
}

int flash_data_read(enum flash_page e_page, uint32_t offset, uint8_t data[], uint16_t length)
{
	uint16_t i;
	
	for(i = 0; i < length; i += 2) {
		*(uint16_t *)(data + i) = flash_internal_read_halfword(e_page, offset + i);
	}
	
	return 0;
}
