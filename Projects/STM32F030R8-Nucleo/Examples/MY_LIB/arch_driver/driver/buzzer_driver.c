/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "device.h"
#include "pwm_driver.h"
#include "api_pwm_common.h"
#include "buzzer_driver.h"
#include "api_buzzer_common.h"


static int output_control(struct device *Dev, uint16_t frequency, uint8_t volume)
{
	struct buzzer_data *D_data = Dev->data;
	
	pwm_output(D_data->Pwm, frequency, volume);
	return 0;
}

static const struct buzzer_common_api Buzzer_common_api = {
	.output = output_control,
};

static struct buzzer_data Buzzer_data;

static int buzzer_device_init(struct device *Dev)
{
	struct buzzer_data *D_data = Dev->data;
	
	D_data->Pwm = pwm3_4_device_binding();
	pwm_init(D_data->Pwm);
	printf("Buzzer device init\r\n");
	
	return 0;
}

struct device Buzzer = {
	.api  = &Buzzer_common_api,
	.data = &Buzzer_data,
	.init = buzzer_device_init,
};

struct device* buzzer_device_binding(void)
{
	return &Buzzer;
}
