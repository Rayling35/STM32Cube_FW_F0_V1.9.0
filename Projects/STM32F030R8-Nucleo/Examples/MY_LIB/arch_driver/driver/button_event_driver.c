/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "cmsis_os.h"
#include "device.h"
#include "gpio_driver.h"
#include "api_gpio_common.h"
#include "button_event_driver.h"
#include "api_button_event_common.h"


static uint32_t get_press_time_data(struct device *Dev)
{
	struct button_event_data *D_data = Dev->data;
	struct device *Gpio = D_data->Gpio_c13;
	static uint32_t start_press_time = 0;
	
	if(start_press_time == 0) {
		start_press_time = osKernelSysTick();
	}
	
	if(gpio_read(Gpio) != D_data->value_pin_original_status) {
		return (osKernelSysTick() - start_press_time);
	}
	
	if(gpio_read(Gpio) == D_data->value_pin_original_status) {
		start_press_time = 0;
	}
	
	return 0;
}

static const struct button_event_common_api Button_event_api = {
	.get_press_time = get_press_time_data,
};

static struct button_event_data Button_event_data;

static int button_event_device_init(struct device *Dev)
{
	struct button_event_data *D_data = Dev->data;
	
	D_data->Gpio_c13 = gpio_c13_device_binding();
	gpio_init(D_data->Gpio_c13);
	
	D_data->value_pin_original_status = gpio_read(D_data->Gpio_c13);
	
	printf("Button Event device init\r\n");
	return 0;
}

struct device Button_event = {
	.api  = &Button_event_api,
	.data = &Button_event_data,
	.init = button_event_device_init,
};

struct device* button_event_device_binding(void)
{
	return &Button_event;
}
