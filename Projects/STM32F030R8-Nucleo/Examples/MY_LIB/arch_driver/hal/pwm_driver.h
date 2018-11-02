/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __PWM_DRIVER_H
#define __PWM_DRIVER_H


struct pwm_data {
	struct pwm_api *Pwm_hal;
};

#ifdef PWM1_3_DEV
struct device* pwm1_3_device_binding(void);
#endif

#ifdef PWM3_4_DEV
struct device* pwm3_4_device_binding(void);
#endif


#endif
