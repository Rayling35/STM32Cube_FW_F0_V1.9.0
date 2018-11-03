/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_B1_H
#define __GPIO_B1_H


#define PB1_CLK_ENABLE()          __HAL_RCC_GPIOB_CLK_ENABLE()
#define PB1_CLK_DISABLE()         __HAL_RCC_GPIOB_CLK_DISABLE()

#define PB1_PIN                   GPIO_PIN_1
#define PB1_PORT                  GPIOB

#ifdef B1_OUTPUT
#define B1_OUTPUT_LOW()       HAL_GPIO_WritePin(PB1_PORT, PB1_PIN, GPIO_PIN_RESET)
#define B1_OUTPUT_HIGH()      HAL_GPIO_WritePin(PB1_PORT, PB1_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_b1_binding(void);


#endif
