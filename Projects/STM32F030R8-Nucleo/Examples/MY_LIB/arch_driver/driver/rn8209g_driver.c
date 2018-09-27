/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "device.h"
#include "spi_driver.h"
#include "gpio_driver.h"
#include "api_spi_common.h"
#include "api_gpio_common.h"
#include "rn8209g_driver.h"
#include "api_sensor_common.h"


static int spi_register_write(struct device *Spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	uint8_t tx_data[length+1];
	uint8_t dummy;
	uint16_t i;
	
	tx_data[0] = reg;
	for(i = 1; i <= length; i++) {
		tx_data[i] = *data;
		data++;
	}
	return spi_transmit_receive(Spi, tx_data, &dummy, length+1);
}

static int spi_register_read(struct device *Spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	int status;
	uint8_t rx_data[length+1];
	uint16_t i;
	
	status = spi_transmit_receive(Spi, &reg, rx_data, length+1);
	for(i = 0; i < length; i++) {
		data[i] = rx_data[i+1];
	}
	return status;
}

static int rn8209g_value_get(struct device *Dev, enum sensor_type e_type, struct sensor_value *Val)
{
	return 0;
}

static int rn8209g_sample_fetch(struct device *Dev, enum sensor_type e_type)
{
	struct rn8209g_data *D_data = Dev->data;
	uint8_t *rn8209_id = D_data->value_rn8209g_rx;
	
	spi_register_read(D_data->Spi, RN8209G_DEVICEID | RN8209G_R, rn8209_id, 3);
	printf("RN8209G_0x820900 = %02X%02X%02X\r\n", rn8209_id[0],rn8209_id[1],rn8209_id[2]);
	return 0;
}

static const struct sensor_common_api Rn8209g_api = {
	.sample_fetch = rn8209g_sample_fetch,
	.value_get    = rn8209g_value_get,
};

static struct rn8209g_data Rn8209g_data;

static int rn8209g_dev_init(struct device *Dev)
{
	struct rn8209g_data *D_data = Dev->data;
	
	D_data->Spi = spi2_cs0_device_binding();
	D_data->Gpio = gpio_b2_device_binding();
	spi_init(D_data->Spi);
	gpio_init(D_data->Gpio);
	printf("RN8209G device init\r\n");
	
	return 0;
}

struct device Rn8209g = {
	.api  = &Rn8209g_api,
	.data = &Rn8209g_data,
	.init = rn8209g_dev_init,
};

struct device* rn8209g_device_binding(void)
{
	return &Rn8209g;
}


void b2_exti_handel(void)
{
	printf("RN8209G IRQ handel\r\n");
}
