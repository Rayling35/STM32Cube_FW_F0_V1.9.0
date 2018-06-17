/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_B2_H
#define __GPIO_B2_H


#define PB2_CLK_ENABLE()          __HAL_RCC_GPIOB_CLK_ENABLE()
#define PB2_CLK_DISABLE()         __HAL_RCC_GPIOB_CLK_DISABLE()

#define PB2_PIN                   GPIO_PIN_2
#define PB2_PORT                  GPIOB

#ifdef B2_OUTPUT
#define B2_OUTPUT_LOW()       HAL_GPIO_WritePin(PB2_PORT, PB2_PIN, GPIO_PIN_RESET)
#define B2_OUTPUT_HIGH()      HAL_GPIO_WritePin(PB2_PORT, PB2_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_b2_binding(void);


#endif
