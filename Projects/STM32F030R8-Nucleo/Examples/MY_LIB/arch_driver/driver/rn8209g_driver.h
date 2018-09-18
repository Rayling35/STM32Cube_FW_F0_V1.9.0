/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __RN8209G_DRIVER_H
#define __RN8209G_DRIVER_H


struct rn8209g_data {
	struct device *spi;
	struct device *gpio;
	uint8_t rn8209g_rx[3];
};

//SPI_POLARITY_LOW,SPI_PHASE_2EDGE
#define RN8209G_R                   0x00
#define RN8209G_W                   0x80
#define RN8209G_DEVICEID            0x7F

struct device* rn8209g_device_binding(void);


#endif
