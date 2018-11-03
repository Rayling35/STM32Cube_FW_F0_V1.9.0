/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "device.h"
#include "api_define.h"
#include "spi_driver.h"
#include "api_spi_common.h"


static int transmit_data(struct device *Dev, uint8_t *tx_data, uint16_t length)
{
	struct spi_data *D_data = Dev->data;
	const struct spi_config *D_config = Dev->config;
	struct spi_api *Spi_cs_hal = D_data->Spi_cs_hal;
	
	return Spi_cs_hal->transmit(tx_data, length, D_config->value_tx_timeout);
}

static int receive_data(struct device *Dev, uint8_t *rx_data, uint16_t length)
{
	struct spi_data *D_data = Dev->data;
	const struct spi_config *D_config = Dev->config;
	struct spi_api *Spi_cs_hal = D_data->Spi_cs_hal;
	
	return Spi_cs_hal->receive(rx_data, length, D_config->value_rx_timeout);
}

static int receive_data32(struct device *Dev, uint32_t *rx_data, uint16_t length)
{
	struct spi_data *D_data = Dev->data;
	const struct spi_config *D_config = Dev->config;
	struct spi_api *Spi_cs_hal = D_data->Spi_cs_hal;
	
	return Spi_cs_hal->receive32(rx_data, length, D_config->value_rx_timeout);
}

static int transmit_receive_data(struct device *Dev, uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	struct spi_data *D_data = Dev->data;
	const struct spi_config *D_config = Dev->config;
	struct spi_api *Spi_cs_hal = D_data->Spi_cs_hal;
	
	return Spi_cs_hal->transmit_receive(tx_data, rx_data, length, D_config->value_tx_rx_timeout);
}

static const struct spi_common_api Spi_common_api = {
	.transmit         = transmit_data,
	.receive          = receive_data,
	.receive32        = receive_data32,
	.transmit_receive = transmit_receive_data,
};


#ifdef SPI1_CS0_DEV
#include "spi1_cs0.h"
static struct spi_data Spi1_cs0_data;

static const struct spi_config Spi1_cs0_config = {
	.value_tx_timeout    = 100,
	.value_rx_timeout    = 100,
	.value_tx_rx_timeout = 100,
};

static int spi1_cs0_device_init(struct device *Dev)
{
	struct spi_data *D_data = Dev->data;
	
	D_data->Spi_cs_hal = spi1_cs0_binding();
	D_data->Spi_cs_hal->init();
	printf("SPI1_CS0 device init\r\n");
	
	return 0;
}

struct device Spi_1_cs0 = {
	.api    = &Spi_common_api,
	.data   = &Spi1_cs0_data,
	.config = &Spi1_cs0_config,
	.init   = spi1_cs0_device_init,
};

struct device* spi1_cs0_device_binding(void)
{
	return &Spi_1_cs0;
}
#endif


#ifdef SPI2_CS0_DEV
#include "spi2_cs0.h"
static struct spi_data Spi2_cs0_data;

static const struct spi_config Spi2_cs0_config = {
	.value_tx_timeout    = 100,
	.value_rx_timeout    = 100,
	.value_tx_rx_timeout = 100,
};

static int spi2_cs0_device_init(struct device *Dev)
{
	struct spi_data *D_data = Dev->data;
	
	D_data->Spi_cs_hal = spi2_cs0_binding();
	D_data->Spi_cs_hal->init();
	printf("SPI2_CS0 device init\r\n");
	
	return 0;
}

struct device Spi_2_cs0 = {
	.api    = &Spi_common_api,
	.data   = &Spi2_cs0_data,
	.config = &Spi2_cs0_config,
	.init   = spi2_cs0_device_init,
};

struct device* spi2_cs0_device_binding(void)
{
	return &Spi_2_cs0;
}
#endif
