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
	static uint32_t start_press_time = 0;
	
	if(start_press_time == 0) {
		start_press_time = osKernelSysTick();
	}
	
	if(gpio_read(D_data->Gpio_c13) != D_data->value_pin_original_status) {
		return (osKernelSysTick() - start_press_time);
	}
	
	if(gpio_read(D_data->Gpio_c13) == D_data->value_pin_original_status) {
		start_press_time = 0;
	}
	
	return 0;
}

static int get_press_status_data(struct device *Dev, struct button_status *Status)
{
	uint32_t seconds = get_press_time_data(Dev);
	
	if(seconds > 0) {
		Status->flag_button_press = 1;
	}else {
		Status->flag_button_press = 0;
	}
	if(seconds >= 3000 && seconds < 5000) {
		Status->flag_button_press_3_second = 1;
	}else {
		Status->flag_button_press_3_second = 0;
	}
	if(seconds >=5000 && seconds < 8000) {
		Status->flag_button_press_5_second = 1;
	}else {
		Status->flag_button_press_5_second = 0;
	}
	if(seconds >=8000 && seconds < 10000) {
		Status->flag_button_press_8_second = 1;
	}else {
		Status->flag_button_press_8_second = 0;
	}
	if(seconds >=10000 && seconds < 15000) {
		Status->flag_button_press_10_second = 1;
	}else {
		Status->flag_button_press_10_second = 0;
	}
	if(seconds >=15000 && seconds < 20000) {
		Status->flag_button_press_15_second = 1;
	}else {
		Status->flag_button_press_15_second = 0;
	}
	if(seconds >=20000 && seconds < 30000) {
		Status->flag_button_press_20_second = 1;
	}else {
		Status->flag_button_press_20_second = 0;
	}
	if(seconds >=30000) {
		Status->flag_button_press_30_second = 1;
	}else {
		Status->flag_button_press_30_second = 0;
	}
	
	return 0;
}

static const struct button_event_common_api Button_event_api = {
	.get_press_time = get_press_time_data,
	.get_press_status = get_press_status_data,
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
