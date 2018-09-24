/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_SEG7_COMMON_H
#define __API_SEG7_COMMON_H


               /*-----------API--------------*/
typedef void (*seg7_api_1)(struct device *Dev, uint8_t cmd);
typedef void (*seg7_api_2)(struct device *Dev, uint8_t seg_addr, uint8_t com_data);
typedef void (*seg7_api_3)(struct device *Dev, uint8_t seg_addr, uint8_t *com_data, uint16_t count);
typedef void (*seg7_api_4)(struct device *Dev, uint8_t seg_addr, uint8_t d3, uint8_t d2, uint8_t d1, uint8_t d0);

struct seg7_common_api {
	seg7_api_1 write_command;
	seg7_api_2 write_data_4;
	seg7_api_3 write_data_8;
	seg7_api_4 write_data_bit_4;
};


               /*-----------APP--------------*/
static inline int seg7_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline void seg7_write_command(struct device *Dev, uint8_t cmd)
{
	const struct seg7_common_api *D_api = Dev->api;
	D_api->write_command(Dev, cmd);
}

static inline void seg7_write_data_4(struct device *Dev, uint8_t seg_addr, uint8_t com_data)
{
	const struct seg7_common_api *D_api = Dev->api;
	D_api->write_data_4(Dev, seg_addr, com_data);
}

static inline void seg7_write_data_44(struct device *Dev, uint8_t seg_addr, uint8_t *com_data, uint16_t count)
{
	const struct seg7_common_api *D_api = Dev->api;
	D_api->write_data_8(Dev, seg_addr, com_data, count);
}

static inline void seg7_write_data_bit_4(struct device *Dev, uint8_t seg_addr, uint8_t d3, uint8_t d2, uint8_t d1, uint8_t d0)
{
	const struct seg7_common_api *D_api = Dev->api;
	D_api->write_data_bit_4(Dev, seg_addr, d3, d2, d1, d0);
}


#endif
