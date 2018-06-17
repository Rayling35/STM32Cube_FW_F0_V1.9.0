/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "spi2.h"


SPI_HandleTypeDef SpiHandle2;

static void _SPI2_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	#ifdef SPI2_DMA
	static DMA_HandleTypeDef DmaHandle_spi2_tx;
	static DMA_HandleTypeDef DmaHandle_spi2_rx;
	
	SPI_HandleTypeDef *pSpiHandle2;
	pSpiHandle2 = &SpiHandle2;
	#endif
	
	SPI2_SCK_GPIO_CLK_ENABLE();
	SPI2_MISO_GPIO_CLK_ENABLE();
	SPI2_MOSI_GPIO_CLK_ENABLE();
	
	GPIO_InitStruct.Pin       = SPI2_SCK_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = SPI2_SCK_AF;
	HAL_GPIO_Init(SPI2_SCK_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin       = SPI2_MISO_PIN;
	GPIO_InitStruct.Alternate = SPI2_MISO_AF;
	HAL_GPIO_Init(SPI2_MISO_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin       = SPI2_MOSI_PIN;
	GPIO_InitStruct.Alternate = SPI2_MOSI_AF;
	HAL_GPIO_Init(SPI2_MOSI_GPIO_PORT, &GPIO_InitStruct);
	
	SPI2_CLK_ENABLE();
	SPI2_FORCE_RESET();
	SPI2_RELEASE_RESET();
	
	#ifdef SPI2_IT
	HAL_NVIC_SetPriority(SPI2_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(SPI2_IRQn);
	
	#ifdef SPI2_DMA
	DMA_SPI2_CLK_ENABLE();
	
	DmaHandle_spi2_tx.Instance                 = DMA_SPI2_TX_STREAM;
	DmaHandle_spi2_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	DmaHandle_spi2_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_spi2_tx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_spi2_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_spi2_tx.Init.Mode                = DMA_NORMAL;
	DmaHandle_spi2_tx.Init.Priority            = DMA_PRIORITY_LOW;
	
	__HAL_LINKDMA(pSpiHandle2, hdmatx, DmaHandle_spi2_tx);
	HAL_DMA_Init(&DmaHandle_spi2_tx);
	
	DmaHandle_spi2_rx.Instance                 = DMA_SPI2_RX_STREAM;
	DmaHandle_spi2_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	DmaHandle_spi2_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_spi2_rx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_spi2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_spi2_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_spi2_rx.Init.Mode                = DMA_NORMAL;
	DmaHandle_spi2_rx.Init.Priority            = DMA_PRIORITY_LOW;
	
	__HAL_LINKDMA(pSpiHandle2, hdmarx, DmaHandle_spi2_rx);
	HAL_DMA_Init(&DmaHandle_spi2_rx);
	
	HAL_NVIC_SetPriority(DMA_SPI2_TX_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(DMA_SPI2_TX_IRQn);
	
	HAL_NVIC_SetPriority(DMA_SPI2_RX_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA_SPI2_RX_IRQn);
	#endif
	#endif
}

void spi2_init(void)
{
	if(HAL_SPI_GetState(&SpiHandle2) == HAL_SPI_STATE_RESET)
	{
		SpiHandle2.Instance               = SPI2;
		SpiHandle2.Init.Mode              = SPI_MODE_MASTER;
		SpiHandle2.Init.Direction         = SPI_DIRECTION_2LINES;
		SpiHandle2.Init.DataSize          = SPI_DATASIZE_8BIT;
		SpiHandle2.Init.CLKPolarity       = SPI2_CLKPOLARITY;
		SpiHandle2.Init.CLKPhase          = SPI2_CLKPHASE;
		SpiHandle2.Init.NSS               = SPI_NSS_SOFT;
		SpiHandle2.Init.BaudRatePrescaler = SPI2_BAUDRATEPRESCALER;
		SpiHandle2.Init.FirstBit          = SPI_FIRSTBIT_MSB;
		SpiHandle2.Init.TIMode            = SPI_TIMODE_DISABLE;
		SpiHandle2.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
		SpiHandle2.Init.CRCPolynomial     = 7;
		SpiHandle2.Init.CRCLength         = SPI_CRC_LENGTH_8BIT;
		SpiHandle2.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;
		
		_SPI2_MspInit();
		HAL_SPI_Init(&SpiHandle2);
	}
}

void _SPI2_MspDeInit(void)
{
	HAL_GPIO_DeInit(SPI2_SCK_GPIO_PORT, SPI2_SCK_PIN);
	HAL_GPIO_DeInit(SPI2_MISO_GPIO_PORT, SPI2_MISO_PIN);
	HAL_GPIO_DeInit(SPI2_MOSI_GPIO_PORT, SPI2_MOSI_PIN);
	
	HAL_SPI_DeInit(&SpiHandle2);
	
	#ifdef SPI2_IT
	HAL_NVIC_DisableIRQ(SPI2_IRQn);
	
	#ifdef SPI2_DMA
	HAL_DMA_DeInit(SpiHandle2.hdmatx);
	HAL_DMA_DeInit(SpiHandle2.hdmarx);
	
	HAL_NVIC_DisableIRQ(DMA_SPI2_TX_IRQn);
	HAL_NVIC_DisableIRQ(DMA_SPI2_RX_IRQn);
	#endif
	#endif
}

#ifdef SPI2_IT
void SPI2_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&SpiHandle2);
}

#ifdef SPI2_DMA
void DMA_SPI2_TX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(SpiHandle2.hdmatx);
}

void DMA_SPI2_RX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(SpiHandle2.hdmarx);
}
#endif
#endif
