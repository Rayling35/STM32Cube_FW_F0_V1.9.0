/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_LCD_COMMON_H
#define __API_LCD_COMMON_H


struct lcd_value {
	uint32_t value_integer;
	uint32_t value_decimal;
	uint8_t flag_symbol_K;
};

enum lcd_type {
	LCD_SET_ALL,
	LCD_CLEAN_ALL,
	LCD_PZ_VOLTAGE,
	LCD_PZ_CURRENT,
	LCD_PZ_POWER,
	LCD_PZ_CONSUMPTION,
};

               /*-----------API--------------*/
typedef int (*lcd_api_value_send)(struct device *Dev, enum lcd_type e_type, struct lcd_value *Val);

struct lcd_common_api {
	lcd_api_value_send value_send;
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
