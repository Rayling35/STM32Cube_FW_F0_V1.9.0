/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __BREATHING_LED_DRIVER_H
#define __BREATHING_LED_DRIVER_H


struct breathing_led_data {
	struct device *Pwm;
};

struct device* breathing_led_device_binding(void);


#endif
