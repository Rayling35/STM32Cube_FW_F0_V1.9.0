/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __BUZZER_DRIVER_H
#define __BUZZER_DRIVER_H


struct buzzer_data {
	struct device *Pwm;
};

struct device* buzzer_device_binding(void);


#endif
