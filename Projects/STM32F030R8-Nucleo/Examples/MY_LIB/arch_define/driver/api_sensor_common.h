/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_SENSOR_COMMON_H
#define __API_SENSOR_COMMON_H


struct sensor_value {
	int value_integer;
	int value_decimal;
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
typedef int (*sensor_api_1)(struct device *Dev, enum sensor_type e_type);
typedef int (*sensor_api_2)(struct device *Dev, enum sensor_type e_type, struct sensor_value *Data);
typedef int (*sensor_api_3)(struct device *Dev, enum sensor_type e_type);

struct sensor_common_api {
	sensor_api_1 sample_fetch;
	sensor_api_2 value_get;
	sensor_api_3 data_clear;
};


               /*-----------APP--------------*/
static inline int sensor_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline int sensor_sample_fetch(struct device *Dev)
{
	const struct sensor_common_api *D_api = Dev->api;
	return D_api->sample_fetch(Dev, SENSOR_ALL);
}

static inline int sensor_value_get(struct device *Dev, enum sensor_type e_type, struct sensor_value *Data)
{
	const struct sensor_common_api *D_api = Dev->api;
	return D_api->value_get(Dev, e_type, Data);
}

static inline int sensor_data_clear(struct device *Dev, enum sensor_type e_type)
{
	const struct sensor_common_api *D_api = Dev->api;
	return D_api->data_clear(Dev, e_type);
}


#endif
