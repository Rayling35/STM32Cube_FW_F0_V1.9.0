/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_SPI_COMMON_H
#define __API_SPI_COMMON_H


               /*-----------API--------------*/
typedef int (*spi_api_1)(struct device *Dev, uint8_t *data, uint16_t length);
typedef int (*spi_api_2)(struct device *Dev, uint8_t *data, uint16_t length);
typedef int (*spi_api_3)(struct device *Dev, uint32_t *data, uint16_t length);
typedef int (*spi_api_4)(struct device *Dev, uint8_t *tx_data, uint8_t *rx_data, uint16_t length);

struct spi_common_api {
	spi_api_1 transmit;
	spi_api_2 receive;
	spi_api_3 receive32;
	spi_api_4 transmit_receive;
};


               /*-----------APP--------------*/
static inline int spi_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline int spi_transmit(struct device *Dev, uint8_t *data, uint16_t length)
{
	const struct spi_common_api *D_api = Dev->api;
	return D_api->transmit(Dev, data, length);
}

static inline int spi_receive(struct device *Dev, uint8_t *data, uint16_t length)
{
	const struct spi_common_api *D_api = Dev->api;
	return D_api->receive(Dev, data, length);
}

static inline int spi_receive32(struct device *Dev, uint32_t *data, uint16_t length)
{
	const struct spi_common_api *D_api = Dev->api;
	return D_api->receive32(Dev, data, length);
}

static inline int spi_transmit_receive(struct device *Dev, uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	const struct spi_common_api *D_api = Dev->api;
	return D_api->transmit_receive(Dev, tx_data, rx_data, length);
}


#endif
