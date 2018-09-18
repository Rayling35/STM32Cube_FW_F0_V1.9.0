/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "device.h"
#include "api_define.h"
#include "spi_common_api.h"
#include "spi_driver.h"


static int transmit_data(struct device *dev, uint8_t *tx_data, uint16_t length)
{
	struct spi_data *d_data           = dev->data;
	const struct spi_config *d_config = dev->config;
	struct spi_api *spi_cs_hal        = d_data->spi_cs_hal;
	
	return spi_cs_hal->transmit(tx_data, length, d_config->tx_timeout);
}

static int receive_data(struct device *dev, uint8_t *rx_data, uint16_t length)
{
	struct spi_data *d_data           = dev->data;
	const struct spi_config *d_config = dev->config;
	struct spi_api *spi_cs_hal        = d_data->spi_cs_hal;
	
	return spi_cs_hal->receive(rx_data, length, d_config->rx_timeout);
}

static int receive_data32(struct device *dev, uint32_t *rx_data, uint16_t length)
{
	struct spi_data *d_data           = dev->data;
	const struct spi_config *d_config = dev->config;
	struct spi_api *spi_cs_hal        = d_data->spi_cs_hal;
	
	return spi_cs_hal->receive32(rx_data, length, d_config->rx_timeout);
}

static int transmit_receive_data(struct device *dev, uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	struct spi_data *d_data           = dev->data;
	const struct spi_config *d_config = dev->config;
	struct spi_api *spi_cs_hal        = d_data->spi_cs_hal;
	
	return spi_cs_hal->transmit_receive(tx_data, rx_data, length, d_config->tx_rx_timeout);
}

static const struct spi_common_api spi_common_api = {
	.transmit         = transmit_data,
	.receive          = receive_data,
	.receive32        = receive_data32,
	.transmit_receive = transmit_receive_data,
};


#ifdef SPI1_CS0_DEV
#include "spi1_cs0.h"
static struct spi_data spi1_cs0_data;

static const struct spi_config spi1_cs0_config = {
	.tx_timeout    = 100,
	.rx_timeout    = 100,
	.tx_rx_timeout = 100,
};

static int spi1_cs0_dev_init(struct device *dev)
{
	struct spi_data *d_data = dev->data;
	
	d_data->spi_cs_hal = spi1_cs0_binding();
	d_data->spi_cs_hal->init();
	printf("SPI1_CS0 device init\r\n");
	
	return 0;
}

struct device spi_1_cs0 = {
	.api    = &spi_common_api,
	.data   = &spi1_cs0_data,
	.config = &spi1_cs0_config,
	.init   = spi1_cs0_dev_init,
};

struct device* spi1_cs0_device_binding(void)
{
	return &spi_1_cs0;
}
#endif

#ifdef SPI2_CS0_DEV
#include "spi2_cs0.h"
static struct spi_data spi2_cs0_data;

static const struct spi_config spi2_cs0_config = {
	.tx_timeout    = 100,
	.rx_timeout    = 100,
	.tx_rx_timeout = 100,
};

static int spi2_cs0_dev_init(struct device *dev)
{
	struct spi_data *d_data = dev->data;
	
	d_data->spi_cs_hal = spi2_cs0_binding();
	d_data->spi_cs_hal->init();
	printf("SPI2_CS0 device init\r\n");
	
	return 0;
}

struct device spi_2_cs0 = {
	.api    = &spi_common_api,
	.data   = &spi2_cs0_data,
	.config = &spi2_cs0_config,
	.init   = spi2_cs0_dev_init,
};

struct device* spi2_cs0_device_binding(void)
{
	return &spi_2_cs0;
}
#endif
