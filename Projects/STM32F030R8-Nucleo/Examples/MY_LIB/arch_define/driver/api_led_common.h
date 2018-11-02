/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_LED_COMMON_H
#define __API_LED_COMMON_H


enum led_state {
	OFF,
	ON,
};

               /*-----------API--------------*/
typedef int (*led_api_1)(struct device *Dev, enum led_state e_state);
typedef int (*led_api_2)(struct device *Dev, uint8_t brightness); //brightness:0-100

struct led_common_api {
	led_api_1 normal_light;
	led_api_2 breathing_light;
};


               /*-----------APP--------------*/
static inline int led_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline int led_on_off(struct device *Dev, enum led_state e_state)
{
	const struct led_common_api *D_api = Dev->api;
	return D_api->normal_light(Dev, e_state);
}

static inline int led_breathing(struct device *Dev, uint8_t brightness)
{
	const struct led_common_api *D_api = Dev->api;
	return D_api->breathing_light(Dev, brightness);
}


#endif
