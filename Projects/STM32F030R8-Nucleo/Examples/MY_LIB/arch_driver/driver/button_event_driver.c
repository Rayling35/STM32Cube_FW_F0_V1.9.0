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
	
	if(gpio_read(D_data->Gpio) != D_data->value_pin_original_status) {
		return (osKernelSysTick() - start_press_time);
	}
	
	if(gpio_read(D_data->Gpio) == D_data->value_pin_original_status) {
		start_press_time = 0;
	}
	
	return 0;
}

static int get_press_status_data(struct device *Dev, struct button_status *Status)
{
	uint32_t seconds = get_press_time_data(Dev);
	
	Status->value_get_timer = seconds;
	
	if(seconds > 0) {
		Status->flag_button_press = 1;
	}else {
		Status->flag_button_press = 0;
	}
	if(seconds >= 1000 && seconds < 2000) {
		Status->flag_button_press_1_second = 1;
	}else {
		Status->flag_button_press_1_second = 0;
	}
	if(seconds >= 2000 && seconds < 3000) {
		Status->flag_button_press_2_second = 1;
	}else {
		Status->flag_button_press_2_second = 0;
	}
	if(seconds >= 3000 && seconds < 4000) {
		Status->flag_button_press_3_second = 1;
	}else {
		Status->flag_button_press_3_second = 0;
	}
	if(seconds >=4000 && seconds < 5000) {
		Status->flag_button_press_4_second = 1;
	}else {
		Status->flag_button_press_4_second = 0;
	}
	if(seconds >=5000 && seconds < 6000) {
		Status->flag_button_press_5_second = 1;
	}else {
		Status->flag_button_press_5_second = 0;
	}
	if(seconds >=6000 && seconds < 7000) {
		Status->flag_button_press_6_second = 1;
	}else {
		Status->flag_button_press_6_second = 0;
	}
	if(seconds >=7000 && seconds < 8000) {
		Status->flag_button_press_7_second = 1;
	}else {
		Status->flag_button_press_7_second = 0;
	}
	if(seconds >=8000 && seconds < 9000) {
		Status->flag_button_press_8_second = 1;
	}else {
		Status->flag_button_press_8_second = 0;
	}
	if(seconds >=9000 && seconds < 10000) {
		Status->flag_button_press_9_second = 1;
	}else {
		Status->flag_button_press_9_second = 0;
	}
	if(seconds >=10000 && seconds < 11000) {
		Status->flag_button_press_10_second = 1;
	}else {
		Status->flag_button_press_10_second = 0;
	}
	if(seconds >=11000 && seconds < 12000) {
		Status->flag_button_press_11_second = 1;
	}else {
		Status->flag_button_press_11_second = 0;
	}
	if(seconds >=12000 && seconds < 13000) {
		Status->flag_button_press_12_second = 1;
	}else {
		Status->flag_button_press_12_second = 0;
	}
	if(seconds >=13000 && seconds < 14000) {
		Status->flag_button_press_13_second = 1;
	}else {
		Status->flag_button_press_13_second = 0;
	}
	if(seconds >=14000 && seconds < 15000) {
		Status->flag_button_press_14_second = 1;
	}else {
		Status->flag_button_press_14_second = 0;
	}
	if(seconds >=15000 && seconds < 16000) {
		Status->flag_button_press_15_second = 1;
	}else {
		Status->flag_button_press_15_second = 0;
	}
	if(seconds >=16000 && seconds < 17000) {
		Status->flag_button_press_16_second = 1;
	}else {
		Status->flag_button_press_16_second = 0;
	}
	if(seconds >=17000 && seconds < 18000) {
		Status->flag_button_press_17_second = 1;
	}else {
		Status->flag_button_press_17_second = 0;
	}
	if(seconds >=18000 && seconds < 19000) {
		Status->flag_button_press_18_second = 1;
	}else {
		Status->flag_button_press_18_second = 0;
	}
	if(seconds >=19000 && seconds < 20000) {
		Status->flag_button_press_19_second = 1;
	}else {
		Status->flag_button_press_19_second = 0;
	}
	if(seconds >=20000 && seconds < 21000) {
		Status->flag_button_press_20_second = 1;
	}else {
		Status->flag_button_press_20_second = 0;
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
	
	D_data->Gpio = gpio_c13_device_binding();
	gpio_init(D_data->Gpio);
	
	D_data->value_pin_original_status = gpio_read(D_data->Gpio);
	
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
