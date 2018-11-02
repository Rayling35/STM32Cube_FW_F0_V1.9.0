/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_PWM_COMMON_H
#define __API_PWM_COMMON_H


               /*-----------API--------------*/
typedef int (*pwm_api_1)(struct device *Dev, uint16_t frequency, uint8_t duty_cycle);

struct pwm_common_api {
	pwm_api_1 output;
};


               /*-----------APP--------------*/
static inline int pwm_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline int pwm_output(struct device *Dev, uint16_t frequency, uint8_t duty_cycle)
{
	const struct pwm_common_api *D_api = Dev->api;
	return D_api->output(Dev, frequency, duty_cycle);
}


#endif
