/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __SPI1_CS0_H
#define __SPI1_CS0_H


#define SPI1C0_OUTPUT_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI1C0_OUTPUT_CLK_DISABLE()       __HAL_RCC_GPIOA_CLK_DISABLE()

#define SPI1C0_OUTPUT_PIN                 GPIO_PIN_4
#define SPI1C0_OUTPUT_PORT                GPIOA

struct spi_api* spi1_cs0_binding(void);


#endif
