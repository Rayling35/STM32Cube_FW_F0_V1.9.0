/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "device.h"
#include "pwm_driver.h"
#include "api_pwm_common.h"
#include "breathing_led_driver.h"
#include "api_led_common.h"


static int breathing_light_control(struct device *Dev, uint8_t brightness)
{
	struct breathing_led_data *D_data = Dev->data;
	
	pwm_output(D_data->Pwm, 1000, brightness);
	return 0;
}

static const struct led_common_api Breathing_led_common_api = {
	.breathing_light = breathing_light_control,
};

static struct breathing_led_data Breathing_led_data;

static int breathing_led_device_init(struct device *Dev)
{
	struct breathing_led_data *D_data = Dev->data;
	
	D_data->Pwm = pwm1_3_device_binding();
	pwm_init(D_data->Pwm);
	printf("Breathing LED device init\r\n");
	
	return 0;
}

struct device Breathing_led = {
	.api  = &Breathing_led_common_api,
	.data = &Breathing_led_data,
	.init = breathing_led_device_init,
};

struct device* breathing_led_device_binding(void)
{
	return &Breathing_led;
}
