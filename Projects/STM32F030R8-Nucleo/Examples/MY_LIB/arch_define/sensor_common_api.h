/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __SENSOR_COMMON_API_H
#define __SENSOR_COMMON_API_H


struct sensor_value {
	int integer;
	int decimal;
};

enum sensor_type {
	SENSOR_MAX31855_TEMPERATURE_THERMOCOUPLE,
	SENSOR_MAX31855_TEMPERATURE_JUNCTION,
	SENSOR_RN8209G_VOLTAGE,
	SENSOR_RN8209G_CURRENT,
	SENSOR_RN8209G_POWER,
	SENSOR_RN8209G_CONSUMPTION,
	SENSOR_BME280_TEMPERATURE,
	SENSOR_BME280_HUMIDITY,
	SENSOR_ADXL362_ACCEL_X,
	SENSOR_ADXL362_ACCEL_Y,
	SENSOR_ADXL362_ACCEL_Z,
	SENSOR_ALL,
};

               /*-----------API--------------*/
typedef int (*sensor_api_sample_fetch)(struct device *dev, enum sensor_type type);
typedef int (*sensor_api_value_get)(struct device *dev, enum sensor_type type, struct sensor_value *val);

struct sensor_common_api {
	sensor_api_sample_fetch sample_fetch;
	sensor_api_value_get value_get;
};

               /*-----------APP--------------*/
static inline int sensor_init(struct device *dev)
{
	return dev->init(dev);
}

static inline int sensor_sample_fetch(struct device *dev)
{
	const struct sensor_common_api *d_api = dev->api;
	return d_api->sample_fetch(dev, SENSOR_ALL);
}

static inline int sensor_value_get(struct device *dev, enum sensor_type type, struct sensor_value *val)
{
	const struct sensor_common_api *d_api = dev->api;
	return d_api->value_get(dev, type, val);
}


#endif
