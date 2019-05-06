/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __BUTTON_EVENT_DRIVER_H
#define __BUTTON_EVENT_DRIVER_H


struct button_event_data {
	struct device *Gpio; //button
	
	uint8_t value_pin_original_status;
};

#ifdef BUTTON_A11_EVENT
struct device* button_a11_event_device_binding(void);
#endif

#ifdef BUTTON_C13_EVENT
struct device* button_c13_event_device_binding(void);
#endif


#endif
