/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __SPI2_H
#define __SPI2_H


#define SPI2_CLK_ENABLE()               __HAL_RCC_SPI2_CLK_ENABLE()
#define SPI2_SCK_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI2_MISO_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI2_MOSI_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI2_MISO_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()
#define SPI2_MOSI_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()

#define SPI2_FORCE_RESET()              __HAL_RCC_SPI2_FORCE_RESET()
#define SPI2_RELEASE_RESET()            __HAL_RCC_SPI2_RELEASE_RESET()

#define SPI2_CLKPOLARITY                SPI_POLARITY_LOW
#define SPI2_CLKPHASE                   SPI_PHASE_2EDGE
#define SPI2_BAUDRATEPRESCALER          SPI_BAUDRATEPRESCALER_32

#define SPI2_SCK_PIN                    GPIO_PIN_13
#define SPI2_SCK_GPIO_PORT              GPIOB
#define SPI2_SCK_AF                     GPIO_AF0_SPI2

#define SPI2_MISO_PIN                   GPIO_PIN_14
#define SPI2_MISO_GPIO_PORT             GPIOB
#define SPI2_MISO_AF                    GPIO_AF0_SPI2

#define SPI2_MOSI_PIN                   GPIO_PIN_15
#define SPI2_MOSI_GPIO_PORT             GPIOB
#define SPI2_MOSI_AF                    GPIO_AF0_SPI2

#ifdef SPI2_IT
void SPI2_IRQHandler(void);

#ifdef SPI2_DMA
#define DMA_SPI2_CLK_ENABLE()          __HAL_RCC_DMA1_CLK_ENABLE()

#define DMA_SPI2_TX_STREAM             DMA1_Channel5
#define DMA_SPI2_RX_STREAM             DMA1_Channel4

#define DMA_SPI2_TX_IRQn               DMA1_Channel4_5_IRQn
#define DMA_SPI2_RX_IRQn               DMA1_Channel4_5_IRQn
#define DMA_SPI2_TX_IRQHandler         DMA1_Channel4_5_IRQHandler
#define DMA_SPI2_RX_IRQHandler         DMA1_Channel4_5_IRQHandler

void DMA_SPI2_TX_IRQHandler(void);
void DMA_SPI2_RX_IRQHandler(void);
#endif
#endif

void spi2_init(void);
void _SPI2_MspDeInit(void);


#endif
