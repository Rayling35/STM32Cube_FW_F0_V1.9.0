/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "spi2.h"
#include "spi2_cs0.h"
#include "api_define.h"


#define SPI2C0_HIGH()      HAL_GPIO_WritePin(SPI2C0_OUTPUT_PORT, SPI2C0_OUTPUT_PIN, GPIO_PIN_SET)
#define SPI2C0_LOW()       HAL_GPIO_WritePin(SPI2C0_OUTPUT_PORT, SPI2C0_OUTPUT_PIN, GPIO_PIN_RESET)

extern SPI_HandleTypeDef SpiHandle2;

static void spi2_cs0_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	SPI2C0_OUTPUT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = SPI2C0_OUTPUT_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	
	HAL_GPIO_Init(SPI2C0_OUTPUT_PORT, &GPIO_InitStruct);
	spi2_init();
	printf("SPI2_CS0 HAL init\r\n");
}

static void spi2_cs0_error(void)
{
	SPI2C0_OUTPUT_CLK_DISABLE();
	_SPI2_MspDeInit();
	spi2_cs0_init();
}

static int spi2_cs0_transmit(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI2C0_LOW();
	status = HAL_SPI_Transmit(&SpiHandle2, data, length, timeout);
	SPI2C0_HIGH();
	if(status != HAL_OK) {
		spi2_cs0_error();
	}
	return status;
}

static int spi2_cs0_receive(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI2C0_LOW();
	status = HAL_SPI_Receive(&SpiHandle2, data, length, timeout);
	SPI2C0_HIGH();
	if(status != HAL_OK) {
		spi2_cs0_error();
	}
	return status;
}

static int spi2_cs0_receive32(uint32_t *data, uint16_t length, uint32_t timeout)
{
	int status;
	uint8_t rx_data[4];
	uint16_t i;
	
	for(i = 0; i < length; i++) {
		SPI2C0_LOW();
		status = HAL_SPI_Receive(&SpiHandle2, rx_data, 4, timeout);
		SPI2C0_HIGH();
		data[i] = (rx_data[0] << 24) | (rx_data[1] << 16) | (rx_data[2] << 8) | rx_data[3];
		if(status != HAL_OK) {
			spi2_cs0_error();
			return status;
		}
	}
	return status;
}

static int spi2_cs0_transmit_receive(uint8_t *tx_data, uint8_t *rx_data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI2C0_LOW();
	status = HAL_SPI_TransmitReceive(&SpiHandle2, tx_data, rx_data, length, timeout);
	SPI2C0_HIGH();
	if(status != HAL_OK) {
		spi2_cs0_error();
	}
	return status;
}

#ifdef SPI2C0_IT
static int spi2_cs0_transmit_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI2C0_LOW();
	status = HAL_SPI_Transmit_IT(&SpiHandle2, data, length);
	SPI2C0_HIGH();
	if(status != HAL_OK) {
		spi2_cs0_error();
	}
	return status;
}

static int spi2_cs0_receive_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI2C0_LOW();
	status = HAL_SPI_Receive_IT(&SpiHandle2, data, length);
	SPI2C0_HIGH();
	if(status != HAL_OK) {
		spi2_cs0_error();
	}
	return status;
}

static int spi2_cs0_transmit_receive_it(uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI2C0_LOW();
	status = HAL_SPI_TransmitReceive_IT(&SpiHandle2, tx_data, rx_data, length);
	SPI2C0_HIGH();
	if(status != HAL_OK) {
		spi2_cs0_error();
	}
	return status;
}

#ifdef SPI2C0_DMA
static int spi2_cs0_transmit_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI2C0_LOW();
	status = HAL_SPI_Transmit_DMA(&SpiHandle2, data, length);
	SPI2C0_HIGH();
	if(status != HAL_OK) {
		spi2_cs0_error();
	}
	return status;
}

static int spi2_cs0_receive_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI2C0_LOW();
	status = HAL_SPI_Receive_DMA(&SpiHandle2, data, length);
	SPI2C0_HIGH();
	if(status != HAL_OK) {
		spi2_cs0_error();
	}
	return status;
}

static int spi2_cs0_transmit_receive_dma(uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI2C0_LOW();
	status = HAL_SPI_TransmitReceive_DMA(&SpiHandle2, tx_data, rx_data, length);
	SPI2C0_HIGH();
	if(status != HAL_OK) {
		spi2_cs0_error();
	}
	return status;
}
#endif
#endif

static struct spi_api spi2_cs0_api = {
	.init                 = spi2_cs0_init,
	.transmit             = spi2_cs0_transmit,
	.receive              = spi2_cs0_receive,
	.receive32            = spi2_cs0_receive32,
	.transmit_receive     = spi2_cs0_transmit_receive,
	#ifdef SPI2C0_IT
	.transmit_it          = spi2_cs0_transmit_it,
	.receive_it           = spi2_cs0_receive_it,
	.transmit_receive_it  = spi2_cs0_transmit_receive_it,
	#ifdef SPI2C0_DMA
	.transmit_dma         = spi2_cs0_transmit_dma,
	.receive_dma          = spi2_cs0_receive_dma,
	.transmit_receive_dma = spi2_cs0_transmit_receive_dma,
	#endif
	#endif
};

struct spi_api* spi2_cs0_binding(void)
{
	return &spi2_cs0_api; //¶Ç»¼¦ì¸m
}
