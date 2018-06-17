/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "device.h"
#include "api_define.h"
#include "gpio_driver.h"
#include "gpio_common_api.h"


static int read_data(struct device *dev)
{
	struct gpio_data *d_data  = dev->data;
	struct gpio_api *gpio_hal = d_data->gpio_hal;
	
	return gpio_hal->read();
}

static void write_data(struct device *dev, uint16_t state)
{
	struct gpio_data *d_data  = dev->data;
	struct gpio_api *gpio_hal = d_data->gpio_hal;
	
	gpio_hal->write(state);
}

static void toggle_write_data(struct device *dev)
{
	struct gpio_data *d_data  = dev->data;
	struct gpio_api *gpio_hal = d_data->gpio_hal;
	
	gpio_hal->toggle_write();
}

static const struct gpio_common_api gpio_common_api = {
	.read         = read_data,
	.write        = write_data,
	.toggle_write = toggle_write_data,
};


#ifdef GPIO_B2_DEV
#include "gpio_b2.h"
static struct gpio_data gpio_b2_data;

static int gpio_b2_dev_init(struct device *dev)
{
	struct gpio_data *d_data = dev->data;
	
	d_data->gpio_hal = gpio_b2_binding();
	d_data->gpio_hal->init();
	printf("GPIO_B2 device init\r\n");

	return 0;
}

struct device gpio_b2 = {
	.api    = &gpio_common_api,
	.data   = &gpio_b2_data,
	.init   = gpio_b2_dev_init,
};

struct device* gpio_b2_device_binding(void)
{
	return &gpio_b2;
}

#ifdef B2_EXTI
__weak void b2_exti_handel(void)
{
}
#endif
#endif


#ifdef GPIO_C5_DEV
#include "gpio_c5.h"
static struct gpio_data gpio_c5_data;

static int gpio_c5_dev_init(struct device *dev)
{
	struct gpio_data *d_data = dev->data;
	
	d_data->gpio_hal = gpio_c5_binding();
	d_data->gpio_hal->init();
	printf("GPIO_C5 device init\r\n");

	return 0;
}

struct device gpio_c5 = {
	.api    = &gpio_common_api,
	.data   = &gpio_c5_data,
	.init   = gpio_c5_dev_init,
};

struct device* gpio_c5_device_binding(void)
{
	return &gpio_c5;
}

#ifdef C5_EXTI
__weak void c5_exti_handel(void)
{
}
#endif
#endif


#ifdef GPIO_C6_DEV
#include "gpio_c6.h"
static struct gpio_data gpio_c6_data;

static int gpio_c6_dev_init(struct device *dev)
{
	struct gpio_data *d_data = dev->data;
	
	d_data->gpio_hal = gpio_c6_binding();
	d_data->gpio_hal->init();
	printf("GPIO_C6 device init\r\n");

	return 0;
}

struct device gpio_c6 = {
	.api    = &gpio_common_api,
	.data   = &gpio_c6_data,
	.init   = gpio_c6_dev_init,
};

struct device* gpio_c6_device_binding(void)
{
	return &gpio_c6;
}

#ifdef C6_EXTI
__weak void c6_exti_handel(void)
{
}
#endif
#endif


#ifdef GPIO_C8_DEV
#include "gpio_c8.h"
static struct gpio_data gpio_c8_data;

static int gpio_c8_dev_init(struct device *dev)
{
	struct gpio_data *d_data = dev->data;
	
	d_data->gpio_hal = gpio_c8_binding();
	d_data->gpio_hal->init();
	printf("GPIO_C8 device init\r\n");

	return 0;
}

struct device gpio_c8 = {
	.api    = &gpio_common_api,
	.data   = &gpio_c8_data,
	.init   = gpio_c8_dev_init,
};

struct device* gpio_c8_device_binding(void)
{
	return &gpio_c8;
}

#ifdef C8_EXTI
__weak void c8_exti_handel(void)
{
}
#endif
#endif


#ifdef GPIO_C13_DEV
#include "gpio_c13.h"
static struct gpio_data gpio_c13_data;

static int gpio_c13_dev_init(struct device *dev)
{
	struct gpio_data *d_data = dev->data;
	
	d_data->gpio_hal = gpio_c13_binding();
	d_data->gpio_hal->init();
	printf("GPIO_C13 device init\r\n");

	return 0;
}

struct device gpio_c13 = {
	.api    = &gpio_common_api,
	.data   = &gpio_c13_data,
	.init   = gpio_c13_dev_init,
};

struct device* gpio_c13_device_binding(void)
{
	return &gpio_c13;
}

#ifdef C13_EXTI
__weak void c13_exti_handel(void)
{
}
#endif
#endif


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	#ifdef B2_EXTI
	if(GPIO_Pin == GPIO_PIN_2) {
		b2_exti_handel();
	}
	#endif
	
	#ifdef C5_EXTI
	if(GPIO_Pin == GPIO_PIN_5) {
		c5_exti_handel();
	}
	#endif
	
	#ifdef C6_EXTI
	if(GPIO_Pin == GPIO_PIN_6) {
		c6_exti_handel();
	}
	#endif
	
	#ifdef C8_EXTI
	if(GPIO_Pin == GPIO_PIN_8) {
		c8_exti_handel();
	}
	#endif
	
	#ifdef C13_EXTI
	if(GPIO_Pin == GPIO_PIN_13) {
		c13_exti_handel();
	}
	#endif
}
