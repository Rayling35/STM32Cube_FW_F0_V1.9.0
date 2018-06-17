/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "spi1.h"


SPI_HandleTypeDef SpiHandle1;

static void _SPI1_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	#ifdef SPI1_DMA
	static DMA_HandleTypeDef DmaHandle_spi1_tx;
	static DMA_HandleTypeDef DmaHandle_spi1_rx;
	
	SPI_HandleTypeDef *pSpiHandle1;
	pSpiHandle1 = &SpiHandle1;
	#endif
	
	SPI1_SCK_GPIO_CLK_ENABLE();
	SPI1_MISO_GPIO_CLK_ENABLE();
	SPI1_MOSI_GPIO_CLK_ENABLE();
	
	GPIO_InitStruct.Pin       = SPI1_SCK_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = SPI1_SCK_AF;
	HAL_GPIO_Init(SPI1_SCK_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin       = SPI1_MISO_PIN;
	GPIO_InitStruct.Alternate = SPI1_MISO_AF;
	HAL_GPIO_Init(SPI1_MISO_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin       = SPI1_MOSI_PIN;
	GPIO_InitStruct.Alternate = SPI1_MOSI_AF;
	HAL_GPIO_Init(SPI1_MOSI_GPIO_PORT, &GPIO_InitStruct);
	
	SPI1_CLK_ENABLE();
	SPI1_FORCE_RESET();
	SPI1_RELEASE_RESET();
	
	#ifdef SPI1_IT
	HAL_NVIC_SetPriority(SPI1_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(SPI1_IRQn);
	
	#ifdef SPI1_DMA
	DMA_SPI1_CLK_ENABLE();
	
	DmaHandle_spi1_tx.Instance                 = DMA_SPI1_TX_STREAM;
	DmaHandle_spi1_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	DmaHandle_spi1_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_spi1_tx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_spi1_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_spi1_tx.Init.Mode                = DMA_NORMAL;
	DmaHandle_spi1_tx.Init.Priority            = DMA_PRIORITY_LOW;
	
	__HAL_LINKDMA(pSpiHandle1, hdmatx, DmaHandle_spi1_tx);
	HAL_DMA_Init(&DmaHandle_spi1_tx);
	
	DmaHandle_spi1_rx.Instance                 = DMA_SPI1_RX_STREAM;
	DmaHandle_spi1_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	DmaHandle_spi1_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_spi1_rx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_spi1_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_spi1_rx.Init.Mode                = DMA_NORMAL;
	DmaHandle_spi1_rx.Init.Priority            = DMA_PRIORITY_LOW;
	
	__HAL_LINKDMA(pSpiHandle1, hdmarx, DmaHandle_spi1_rx);
	HAL_DMA_Init(&DmaHandle_spi1_rx);
	
	HAL_NVIC_SetPriority(DMA_SPI1_TX_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(DMA_SPI1_TX_IRQn);
	
	HAL_NVIC_SetPriority(DMA_SPI1_RX_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA_SPI1_RX_IRQn);
	#endif
	#endif
}

void spi1_init(void)
{
	if(HAL_SPI_GetState(&SpiHandle1) == HAL_SPI_STATE_RESET)
	{
		SpiHandle1.Instance               = SPI1;
		SpiHandle1.Init.Mode              = SPI_MODE_MASTER;
		SpiHandle1.Init.Direction         = SPI_DIRECTION_2LINES;
		SpiHandle1.Init.DataSize          = SPI_DATASIZE_8BIT;
		SpiHandle1.Init.CLKPolarity       = SPI1_CLKPOLARITY;
		SpiHandle1.Init.CLKPhase          = SPI1_CLKPHASE;
		SpiHandle1.Init.NSS               = SPI_NSS_SOFT;
		SpiHandle1.Init.BaudRatePrescaler = SPI1_BAUDRATEPRESCALER;
		SpiHandle1.Init.FirstBit          = SPI_FIRSTBIT_MSB;
		SpiHandle1.Init.TIMode            = SPI_TIMODE_DISABLE;
		SpiHandle1.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
		SpiHandle1.Init.CRCPolynomial     = 7;
		SpiHandle1.Init.CRCLength         = SPI_CRC_LENGTH_8BIT;
		SpiHandle1.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;
		
		_SPI1_MspInit();
		HAL_SPI_Init(&SpiHandle1);
	}
}

void _SPI1_MspDeInit(void)
{
	HAL_GPIO_DeInit(SPI1_SCK_GPIO_PORT, SPI1_SCK_PIN);
	HAL_GPIO_DeInit(SPI1_MISO_GPIO_PORT, SPI1_MISO_PIN);
	HAL_GPIO_DeInit(SPI1_MOSI_GPIO_PORT, SPI1_MOSI_PIN);
	
	HAL_SPI_DeInit(&SpiHandle1);
	
	#ifdef SPI1_IT
	HAL_NVIC_DisableIRQ(SPI1_IRQn);
	
	#ifdef SPI1_DMA
	HAL_DMA_DeInit(SpiHandle1.hdmatx);
	HAL_DMA_DeInit(SpiHandle1.hdmarx);
	
	HAL_NVIC_DisableIRQ(DMA_SPI1_TX_IRQn);
	HAL_NVIC_DisableIRQ(DMA_SPI1_RX_IRQn);
	#endif
	#endif
}

#ifdef SPI1_IT
void SPI1_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&SpiHandle1);
}

#ifdef SPI1_DMA
void DMA_SPI1_TX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(SpiHandle1.hdmatx);
}

void DMA_SPI1_RX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(SpiHandle1.hdmarx);
}
#endif
#endif
