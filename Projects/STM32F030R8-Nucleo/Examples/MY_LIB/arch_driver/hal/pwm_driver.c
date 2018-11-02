/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "device.h"
#include "api_define.h"
#include "pwm_driver.h"
#include "api_pwm_common.h"


static int output_data(struct device *Dev, uint16_t frequency, uint8_t duty_cycle)
{
	struct pwm_data *D_data = Dev->data;
	struct pwm_api *Pwm_hal = D_data->Pwm_hal;
	uint32_t period;
	uint32_t prescaler;
/**
	frequency = 48M / (period * perscaler)
**/
	period = 100;
	prescaler = 480000 / frequency;
	Pwm_hal->pin_set(period - 1, (period / 100) * duty_cycle, prescaler - 1);
	
	return 0;
}

static const struct pwm_common_api Pwm_common_api = {
	.output = output_data,
};

#ifdef PWM1_3_DEV
#include "pwm1_3.h"
static struct pwm_data Pwm1_3_data;

static int pwm1_3_device_init(struct device *Dev)
{
	struct pwm_data *D_data = Dev->data;
	
	D_data->Pwm_hal = pwm1_3_binding();
	D_data->Pwm_hal->init();
	printf("PWM1_3 device init\r\n");
	
	return 0;
}

struct device Pwm_1_3 = {
	.api  = &Pwm_common_api,
	.data = &Pwm1_3_data,
	.init = pwm1_3_device_init,
};

struct device* pwm1_3_device_binding(void)
{
	return &Pwm_1_3;
}
#endif


#ifdef PWM3_4_DEV
#include "pwm3_4.h"
static struct pwm_data Pwm3_4_data;

static int pwm3_4_device_init(struct device *Dev)
{
	struct pwm_data *D_data = Dev->data;
	
	D_data->Pwm_hal = pwm3_4_binding();
	D_data->Pwm_hal->init();
	printf("PWM3_4 device init\r\n");
	
	return 0;
}

struct device Pwm_3_4 = {
	.api  = &Pwm_common_api,
	.data = &Pwm3_4_data,
	.init = pwm3_4_device_init,
};

struct device* pwm3_4_device_binding(void)
{
	return &Pwm_3_4;
}
#endif
