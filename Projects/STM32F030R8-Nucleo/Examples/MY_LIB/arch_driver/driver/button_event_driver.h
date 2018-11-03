/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __BUTTON_EVENT_DRIVER_H
#define __BUTTON_EVENT_DRIVER_H


struct button_event_data {
	struct device *Gpio; //button
	
	uint8_t value_pin_original_status;
};

struct device* button_event_device_binding(void);


#endif
