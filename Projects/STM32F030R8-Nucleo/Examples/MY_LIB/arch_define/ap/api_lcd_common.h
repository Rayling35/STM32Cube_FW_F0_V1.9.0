/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_LCD_COMMON_H
#define __API_LCD_COMMON_H


enum lcd_type {
	LCD_SET_ALL,
	LCD_CLEAN_ALL,
	
	LCD_PZ_VOLTAGE,
	LCD_PZ_CURRENT,
	LCD_PZ_POWER,
	LCD_PZ_CONSUMPTION,
	
	LCD_EEYE_VOLTAGE,
	LCD_EEYE_CURRENT,
	LCD_EEYE_POWER,
	LCD_EEYE_CONSUMPTION,
	LCD_EEYE_PF,
	LCD_EEYE_TEMPERATURE,
};

enum display_mode {
	DISPLAY_NORMAL,
	DISPLAY_MASK_NUMBER,
	DISPLAY_MASK_TEXT,
	DISPLAY_MASK_NUMBER_TEXT,
	
	DISPLAY_ONLY_NUMBER_1, //only 0 ~ 10 @ value_integer
	DISPLAY_ONLY_NUMBER_2, //only 0 ~ 10 @ value_integer
	DISPLAY_ONLY_NUMBER_3, //only 0 ~ 10 @ value_integer
	DISPLAY_ONLY_NUMBER_4, //only 0 ~ 10 @ value_integer
	DISPLAY_ONLY_NUMBER_5, //only 0 ~ 10 @ value_integer
	DISPLAY_ONLY_SYMBOL_K, //only 0 & 1 @ flag_symbol_K
};

struct lcd_value {
	uint32_t value_integer;
	uint32_t value_decimal;
	
	uint8_t flag_symbol_K;
	uint8_t flag_symbol_C; //only mode of DISPLAY_NORMAL, DISPLAY_MASK_NUMBER, use
	uint8_t flag_symbol_F; //only mode of DISPLAY_NORMAL, DISPLAY_MASK_NUMBER, use
	
	enum display_mode e_display_mode;
};

               /*-----------API--------------*/
typedef int (*lcd_api_1)(struct device *Dev, enum lcd_type e_type, struct lcd_value *Val);

struct lcd_common_api {
	lcd_api_1 value_send;
};


               /*-----------APP--------------*/
static inline int lcd_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline int lcd_set_all(struct device *Dev)
{
	const struct lcd_common_api *D_api = Dev->api;
	return D_api->value_send(Dev, LCD_SET_ALL, NULL);
}

static inline int lcd_clean_all(struct device *Dev)
{
	const struct lcd_common_api *D_api = Dev->api;
	return D_api->value_send(Dev, LCD_CLEAN_ALL, NULL);
}

static inline int lcd_value_send(struct device *Dev, enum lcd_type e_type, struct lcd_value *Val)
{
	const struct lcd_common_api *D_api = Dev->api;
	return D_api->value_send(Dev, e_type, Val);
}


#endif
