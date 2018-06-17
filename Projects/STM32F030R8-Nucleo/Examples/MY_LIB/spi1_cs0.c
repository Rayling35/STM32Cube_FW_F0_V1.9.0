/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "spi1.h"
#include "spi1_cs0.h"
#include "api_define.h"


#define SPI1C0_HIGH()      HAL_GPIO_WritePin(SPI1C0_OUTPUT_PORT, SPI1C0_OUTPUT_PIN, GPIO_PIN_SET)
#define SPI1C0_LOW()       HAL_GPIO_WritePin(SPI1C0_OUTPUT_PORT, SPI1C0_OUTPUT_PIN, GPIO_PIN_RESET)

extern SPI_HandleTypeDef SpiHandle1;

static void spi1_cs0_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	SPI1C0_OUTPUT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = SPI1C0_OUTPUT_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	
	HAL_GPIO_Init(SPI1C0_OUTPUT_PORT, &GPIO_InitStruct);
	spi1_init();
	printf("SPI1_CS0 HAL init\r\n");
}

static void spi1_cs0_error(void)
{
	SPI1C0_OUTPUT_CLK_DISABLE();
	_SPI1_MspDeInit();
	spi1_cs0_init();
}

static int spi1_cs0_transmit(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI1C0_LOW();
	status = HAL_SPI_Transmit(&SpiHandle1, data, length, timeout);
	SPI1C0_HIGH();
	if(status != HAL_OK) {
		spi1_cs0_error();
	}
	return status;
}

static int spi1_cs0_receive(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI1C0_LOW();
	status = HAL_SPI_Receive(&SpiHandle1, data, length, timeout);
	SPI1C0_HIGH();
	if(status != HAL_OK) {
		spi1_cs0_error();
	}
	return status;
}

static int spi1_cs0_receive32(uint32_t *data, uint16_t length, uint32_t timeout)
{
	int status;
	uint8_t rx_data[4];
	uint16_t i;
	
	for(i = 0; i < length; i++) {
		SPI1C0_LOW();
		status = HAL_SPI_Receive(&SpiHandle1, rx_data, 4, timeout);
		SPI1C0_HIGH();
		data[i] = (rx_data[0] << 24) | (rx_data[1] << 16) | (rx_data[2] << 8) | rx_data[3];
		if(status != HAL_OK) {
			spi1_cs0_error();
			return status;
		}
	}
	return status;
}

static int spi1_cs0_transmit_receive(uint8_t *tx_data, uint8_t *rx_data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI1C0_LOW();
	status = HAL_SPI_TransmitReceive(&SpiHandle1, tx_data, rx_data, length, timeout);
	SPI1C0_HIGH();
	if(status != HAL_OK) {
		spi1_cs0_error();
	}
	return status;
}

#ifdef SPI1C0_IT
static int spi1_cs0_transmit_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI1C0_LOW();
	status = HAL_SPI_Transmit_IT(&SpiHandle1, data, length);
	SPI1C0_HIGH();
	if(status != HAL_OK) {
		spi1_cs0_error();
	}
	return status;
}

static int spi1_cs0_receive_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI1C0_LOW();
	status = HAL_SPI_Receive_IT(&SpiHandle1, data, length);
	SPI1C0_HIGH();
	if(status != HAL_OK) {
		spi1_cs0_error();
	}
	return status;
}

static int spi1_cs0_transmit_receive_it(uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI1C0_LOW();
	status = HAL_SPI_TransmitReceive_IT(&SpiHandle1, tx_data, rx_data, length);
	SPI1C0_HIGH();
	if(status != HAL_OK) {
		spi1_cs0_error();
	}
	return status;
}

#ifdef SPI1C0_DMA
static int spi1_cs0_transmit_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI1C0_LOW();
	status = HAL_SPI_Transmit_DMA(&SpiHandle1, data, length);
	SPI1C0_HIGH();
	if(status != HAL_OK) {
		spi1_cs0_error();
	}
	return status;
}

static int spi1_cs0_receive_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI1C0_LOW();
	status = HAL_SPI_Receive_DMA(&SpiHandle1, data, length);
	SPI1C0_HIGH();
	if(status != HAL_OK) {
		spi1_cs0_error();
	}
	return status;
}

static int spi1_cs0_transmit_receive_dma(uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI1C0_LOW();
	status = HAL_SPI_TransmitReceive_DMA(&SpiHandle1, tx_data, rx_data, length);
	SPI1C0_HIGH();
	if(status != HAL_OK) {
		spi1_cs0_error();
	}
	return status;
}
#endif
#endif

static struct spi_api spi1_cs0_api = {
	.init                 = spi1_cs0_init,
	.transmit             = spi1_cs0_transmit,
	.receive              = spi1_cs0_receive,
	.receive32            = spi1_cs0_receive32,
	.transmit_receive     = spi1_cs0_transmit_receive,
	#ifdef SPI1C0_IT
	.transmit_it          = spi1_cs0_transmit_it,
	.receive_it           = spi1_cs0_receive_it,
	.transmit_receive_it  = spi1_cs0_transmit_receive_it,
	#ifdef SPI1C0_DMA
	.transmit_dma         = spi1_cs0_transmit_dma,
	.receive_dma          = spi1_cs0_receive_dma,
	.transmit_receive_dma = spi1_cs0_transmit_receive_dma,
	#endif
	#endif
};

struct spi_api* spi1_cs0_binding(void)
{
	return &spi1_cs0_api; //�ǻ���m
}
