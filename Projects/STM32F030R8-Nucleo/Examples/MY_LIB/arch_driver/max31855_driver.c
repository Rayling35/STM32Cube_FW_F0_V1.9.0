/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "device.h"
#include "spi_driver.h"
#include "spi_common_api.h"
#include "max31855_driver.h"
#include "sensor_common_api.h"


static int max31855_value_get(struct device *dev, enum sensor_type type, struct sensor_value *val)
{
	struct max31855_data *d_data = dev->data;
	
	switch (type) {
		case SENSOR_MAX31855_TEMPERATURE_THERMOCOUPLE:
			val->integer = d_data->t1;
			val->decimal = d_data->t2;
			break;
		case SENSOR_MAX31855_TEMPERATURE_JUNCTION:
			val->integer = d_data->j1;
			val->decimal = d_data->j2;
			break;
		default:
			return -1;
	}
	return 0;
}

static int max31855_sample_fetch(struct device *dev, enum sensor_type type)
{
	struct max31855_data *d_data = dev->data;
	struct device *spi           = d_data->spi;
	int ret;
	uint32_t data;
	
	ret = spi_receive32(spi, &data, 1);
	d_data->t1 = data >> 20;                //12 bit
	d_data->t2 = (data >> 18) & 0x00000003; //2 bit
	d_data->j1 = (data >> 8) & 0x000000FF;  //8 bit
	d_data->j2 = (data >> 4) & 0x0000000F;  //4 bit
	
	return ret;
}

static const struct sensor_common_api max31855_api = {
	.sample_fetch = max31855_sample_fetch,
	.value_get    = max31855_value_get,
};

static struct max31855_data max31855_data;

static int max31855_dev_init(struct device *dev)
{
	struct max31855_data *d_data = dev->data;
	
	d_data->spi = spi1_cs0_device_binding();
	spi_init(d_data->spi);
	printf("MAX31855 device init\r\n");
	
	return 0;
}

struct device max31855 = {
	.api  = &max31855_api,
	.data = &max31855_data,
	.init = max31855_dev_init,
};

struct device* max31855_device_binding(void)
{
	return &max31855;
}
