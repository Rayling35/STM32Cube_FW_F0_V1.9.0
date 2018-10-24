/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_GPIO_COMMON_H
#define __API_GPIO_COMMON_H


enum count_unit {
	MILLISECOND,
	SECOND,
};

               /*-----------API--------------*/
typedef int (*gpio_api_1)(struct device *Dev);
typedef void (*gpio_api_2)(struct device *Dev, uint8_t state);
typedef void (*gpio_api_3)(struct device *Dev);
typedef uint32_t (*gpio_api_4)(struct device *Dev, enum count_unit e_unit);

struct gpio_common_api {
	gpio_api_1 read;
	gpio_api_2 write;
	gpio_api_3 toggle_write;
	gpio_api_4 press_time;
};


               /*-----------APP--------------*/
static inline int gpio_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline int gpio_read(struct device *Dev)
{
	const struct gpio_common_api *D_api = Dev->api;
	return D_api->read(Dev);
}

static inline void gpio_write(struct device *Dev, uint8_t state)
{
	const struct gpio_common_api *D_api = Dev->api;
	D_api->write(Dev, state);
}

static inline void gpio_toggle_write(struct device *Dev)
{
	const struct gpio_common_api *D_api = Dev->api;
	D_api->toggle_write(Dev);
}

static inline uint32_t gpio_press_time(struct device *Dev, enum count_unit e_unit)
{
	const struct gpio_common_api *D_api = Dev->api;
	return D_api->press_time(Dev, e_unit);
}


#endif
