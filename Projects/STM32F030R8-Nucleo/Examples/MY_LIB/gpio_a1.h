/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_A1_H
#define __GPIO_A1_H


#define PA1_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define PA1_CLK_DISABLE()         __HAL_RCC_GPIOA_CLK_DISABLE()

#define PA1_PIN                   GPIO_PIN_1
#define PA1_PORT                  GPIOA

#ifdef A1_OUTPUT
#define A1_OUTPUT_LOW()       HAL_GPIO_WritePin(PA1_PORT, PA1_PIN, GPIO_PIN_RESET)
#define A1_OUTPUT_HIGH()      HAL_GPIO_WritePin(PA1_PORT, PA1_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_a1_binding(void);


#endif
