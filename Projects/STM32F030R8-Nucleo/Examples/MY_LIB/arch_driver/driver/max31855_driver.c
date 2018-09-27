/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "device.h"
#include "spi_driver.h"
#include "api_spi_common.h"
#include "max31855_driver.h"
#include "api_sensor_common.h"


static int max31855_value_get(struct device *Dev, enum sensor_type e_type, struct sensor_value *Val)
{
	struct max31855_data *D_data = Dev->data;
	
	switch (e_type) {
		case SENSOR_MAX31855_TEMPERATURE_THERMOCOUPLE:
			Val->value_integer = D_data->value_t1;
			Val->value_decimal = D_data->value_t2;
			break;
		case SENSOR_MAX31855_TEMPERATURE_JUNCTION:
			Val->value_integer = D_data->value_j1;
			Val->value_decimal = D_data->value_j2;
			break;
		default:
			return -1;
	}
	return 0;
}

static int max31855_sample_fetch(struct device *Dev, enum sensor_type e_type)
{
	struct max31855_data *D_data = Dev->data;
	int ret;
	uint32_t data;
	
	ret = spi_receive32(D_data->Spi, &data, 1);
	D_data->value_t1 = data >> 20;                //12 bit
	D_data->value_t2 = (data >> 18) & 0x00000003; //2 bit
	D_data->value_j1 = (data >> 8) & 0x000000FF;  //8 bit
	D_data->value_j2 = (data >> 4) & 0x0000000F;  //4 bit
	
	return ret;
}

static const struct sensor_common_api Max31855_api = {
	.sample_fetch = max31855_sample_fetch,
	.value_get    = max31855_value_get,
};

static struct max31855_data Max31855_data;

static int max31855_device_init(struct device *Dev)
{
	struct max31855_data *D_data = Dev->data;
	
	D_data->Spi = spi1_cs0_device_binding();
	spi_init(D_data->Spi);
	printf("MAX31855 device init\r\n");
	
	return 0;
}

struct device Max31855 = {
	.api  = &Max31855_api,
	.data = &Max31855_data,
	.init = max31855_device_init,
};

struct device* max31855_device_binding(void)
{
	return &Max31855;
}
