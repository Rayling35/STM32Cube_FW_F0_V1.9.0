/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __SPI2_CS0_H
#define __SPI2_CS0_H


#define SPI2C0_OUTPUT_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI2C0_OUTPUT_CLK_DISABLE()       __HAL_RCC_GPIOB_CLK_DISABLE()

#define SPI2C0_OUTPUT_PIN                 GPIO_PIN_12
#define SPI2C0_OUTPUT_PORT                GPIOB

struct spi_api* spi2_cs0_binding(void);


#endif
