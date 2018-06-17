/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __SPI1_H
#define __SPI1_H


#define SPI1_CLK_ENABLE()               __HAL_RCC_SPI1_CLK_ENABLE()
#define SPI1_SCK_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI1_MISO_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI1_MOSI_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI1_MISO_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
#define SPI1_MOSI_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()

#define SPI1_FORCE_RESET()              __HAL_RCC_SPI1_FORCE_RESET()
#define SPI1_RELEASE_RESET()            __HAL_RCC_SPI1_RELEASE_RESET()

#define SPI1_CLKPOLARITY                SPI_POLARITY_LOW
#define SPI1_CLKPHASE                   SPI_PHASE_1EDGE
#define SPI1_BAUDRATEPRESCALER          SPI_BAUDRATEPRESCALER_32

#define SPI1_SCK_PIN                    GPIO_PIN_5
#define SPI1_SCK_GPIO_PORT              GPIOA
#define SPI1_SCK_AF                     GPIO_AF0_SPI1

#define SPI1_MISO_PIN                   GPIO_PIN_6
#define SPI1_MISO_GPIO_PORT             GPIOA
#define SPI1_MISO_AF                    GPIO_AF0_SPI1

#define SPI1_MOSI_PIN                   GPIO_PIN_7
#define SPI1_MOSI_GPIO_PORT             GPIOA
#define SPI1_MOSI_AF                    GPIO_AF0_SPI1

#ifdef SPI1_IT
void SPI1_IRQHandler(void);

#ifdef SPI1_DMA
#define DMA_SPI1_CLK_ENABLE()          __HAL_RCC_DMA1_CLK_ENABLE()

#define DMA_SPI1_TX_STREAM             DMA1_Channel3
#define DMA_SPI1_RX_STREAM             DMA1_Channel2

#define DMA_SPI1_TX_IRQn               DMA1_Channel2_3_IRQn
#define DMA_SPI1_RX_IRQn               DMA1_Channel2_3_IRQn
#define DMA_SPI1_TX_IRQHandler         DMA1_Channel2_3_IRQHandler
#define DMA_SPI1_RX_IRQHandler         DMA1_Channel2_3_IRQHandler

void DMA_SPI1_TX_IRQHandler(void);
void DMA_SPI1_RX_IRQHandler(void);
#endif
#endif

void spi1_init(void);
void _SPI1_MspDeInit(void);


#endif
