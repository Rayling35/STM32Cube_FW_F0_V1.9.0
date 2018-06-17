/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __MAX31855_DRIVER_H
#define __MAX31855_DRIVER_H


struct max31855_data {
	struct device *spi;
	
	int t1;
	int t2;
	int j1;
	int j2;
};

struct device* max31855_device_binding(void);


#endif
