/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_A11_H
#define __GPIO_A11_H


#define PA11_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define PA11_CLK_DISABLE()         __HAL_RCC_GPIOA_CLK_DISABLE()

#define PA11_PIN                   GPIO_PIN_11
#define PA11_PORT                  GPIOA

#ifdef A11_OUTPUT
#define A11_OUTPUT_LOW()       HAL_GPIO_WritePin(PA11_PORT, PA11_PIN, GPIO_PIN_RESET)
#define A11_OUTPUT_HIGH()      HAL_GPIO_WritePin(PA11_PORT, PA11_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_a11_binding(void);


#endif
