/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __MAX31855_DRIVER_H
#define __MAX31855_DRIVER_H


struct max31855_data {
	struct device *Spi;
	
	int value_t1;
	int value_t2;
	int value_j1;
	int value_j2;
};

struct device* max31855_device_binding(void);


#endif
