/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __LCD_COMMON_API_H
#define __LCD_COMMON_API_H


struct lcd_value {
	uint32_t integer;
	uint32_t decimal;
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
typedef int (*lcd_api_value_send)(struct device *dev, enum lcd_type type, struct lcd_value *val);

struct lcd_common_api {
	lcd_api_value_send value_send;
};

               /*-----------APP--------------*/
static inline int lcd_init(struct device *dev)
{
	return dev->init(dev);
}

static inline int lcd_set_all(struct device *dev)
{
	const struct lcd_common_api *d_api = dev->api;
	return d_api->value_send(dev, LCD_SET_ALL, NULL);
}

static inline int lcd_clean_all(struct device *dev)
{
	const struct lcd_common_api *d_api = dev->api;
	return d_api->value_send(dev, LCD_CLEAN_ALL, NULL);
}

static inline int lcd_value_send(struct device *dev, enum lcd_type type, struct lcd_value *val)
{
	const struct lcd_common_api *d_api = dev->api;
	return d_api->value_send(dev, type, val);
}


#endif
