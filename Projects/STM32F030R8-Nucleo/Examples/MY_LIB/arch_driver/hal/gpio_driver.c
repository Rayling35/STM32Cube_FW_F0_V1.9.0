/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#ifdef RTOS_ON
#include "cmsis_os.h"
#endif
#include "device.h"
#include "api_define.h"
#include "gpio_driver.h"
#include "api_gpio_common.h"


static int read_data(struct device *Dev)
{
	struct gpio_data *D_data  = Dev->data;
	struct gpio_api *Gpio_hal = D_data->Gpio_hal;
	
	return Gpio_hal->read();
}

static void write_data(struct device *Dev, uint16_t state)
{
	struct gpio_data *D_data  = Dev->data;
	struct gpio_api *Gpio_hal = D_data->Gpio_hal;
	
	Gpio_hal->write(state);
}

static void toggle_write_data(struct device *Dev)
{
	struct gpio_data *D_data  = Dev->data;
	struct gpio_api *Gpio_hal = D_data->Gpio_hal;
	
	Gpio_hal->toggle_write();
}

#ifdef RTOS_ON
static uint32_t press_time_data(struct device *Dev, enum count_unit e_unit)
{
	struct gpio_data *D_data  = Dev->data;
	struct gpio_api *Gpio_hal = D_data->Gpio_hal;
	int no_press_status;
	uint32_t count;
	
	no_press_status = Gpio_hal->read();
	
	switch (e_unit) {
		case MILLISECOND:
			while(1) {
				if(Gpio_hal->read() != no_press_status) {
					count = osKernelSysTick();
					do {
					}while(Gpio_hal->read() != no_press_status);
					return osKernelSysTick() - count;
				}
			}
		case SECOND:
			while(1) {
				if(Gpio_hal->read() != no_press_status) {
					count = osKernelSysTick();
					do {
					}while(Gpio_hal->read() != no_press_status);
					return (osKernelSysTick() - count) / 1000;
				}
			}
		default:
			return 0;
	}
}
#else
static uint32_t press_time_data(struct device *Dev, enum count_unit e_unit)
{
	return 0;
}
#endif

static const struct gpio_common_api Gpio_common_api = {
	.read         = read_data,
	.write        = write_data,
	.toggle_write = toggle_write_data,
	.press_time   = press_time_data,
};


#ifdef GPIO_B2_DEV
#include "gpio_b2.h"
static struct gpio_data Gpio_b2_data;

static int gpio_b2_device_init(struct device *Dev)
{
	struct gpio_data *D_data = Dev->data;
	
	D_data->Gpio_hal = gpio_b2_binding();
	D_data->Gpio_hal->init();
	printf("GPIO_B2 device init\r\n");

	return 0;
}

struct device Gpio_b2 = {
	.api  = &Gpio_common_api,
	.data = &Gpio_b2_data,
	.init = gpio_b2_device_init,
};

struct device* gpio_b2_device_binding(void)
{
	return &Gpio_b2;
}

#ifdef B2_EXTI
__weak void b2_exti_handel(void)
{
}
#endif
#endif


#ifdef GPIO_C5_DEV
#include "gpio_c5.h"
static struct gpio_data Gpio_c5_data;

static int gpio_c5_device_init(struct device *Dev)
{
	struct gpio_data *D_data = Dev->data;
	
	D_data->Gpio_hal = gpio_c5_binding();
	D_data->Gpio_hal->init();
	printf("GPIO_C5 device init\r\n");

	return 0;
}

struct device Gpio_c5 = {
	.api  = &Gpio_common_api,
	.data = &Gpio_c5_data,
	.init = gpio_c5_device_init,
};

struct device* gpio_c5_device_binding(void)
{
	return &Gpio_c5;
}

#ifdef C5_EXTI
__weak void c5_exti_handel(void)
{
}
#endif
#endif


#ifdef GPIO_C6_DEV
#include "gpio_c6.h"
static struct gpio_data Gpio_c6_data;

static int gpio_c6_device_init(struct device *Dev)
{
	struct gpio_data *D_data = Dev->data;
	
	D_data->Gpio_hal = gpio_c6_binding();
	D_data->Gpio_hal->init();
	printf("GPIO_C6 device init\r\n");

	return 0;
}

struct device Gpio_c6 = {
	.api  = &Gpio_common_api,
	.data = &Gpio_c6_data,
	.init = gpio_c6_device_init,
};

struct device* gpio_c6_device_binding(void)
{
	return &Gpio_c6;
}

#ifdef C6_EXTI
__weak void c6_exti_handel(void)
{
}
#endif
#endif


#ifdef GPIO_C8_DEV
#include "gpio_c8.h"
static struct gpio_data Gpio_c8_data;

static int gpio_c8_device_init(struct device *Dev)
{
	struct gpio_data *D_data = Dev->data;
	
	D_data->Gpio_hal = gpio_c8_binding();
	D_data->Gpio_hal->init();
	printf("GPIO_C8 device init\r\n");

	return 0;
}

struct device Gpio_c8 = {
	.api  = &Gpio_common_api,
	.data = &Gpio_c8_data,
	.init = gpio_c8_device_init,
};

struct device* gpio_c8_device_binding(void)
{
	return &Gpio_c8;
}

#ifdef C8_EXTI
__weak void c8_exti_handel(void)
{
}
#endif
#endif


#ifdef GPIO_C13_DEV
#include "gpio_c13.h"
static struct gpio_data Gpio_c13_data;

static int gpio_c13_device_init(struct device *Dev)
{
	struct gpio_data *D_data = Dev->data;
	
	D_data->Gpio_hal = gpio_c13_binding();
	D_data->Gpio_hal->init();
	printf("GPIO_C13 device init\r\n");

	return 0;
}

struct device Gpio_c13 = {
	.api  = &Gpio_common_api,
	.data = &Gpio_c13_data,
	.init = gpio_c13_device_init,
};

struct device* gpio_c13_device_binding(void)
{
	return &Gpio_c13;
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
