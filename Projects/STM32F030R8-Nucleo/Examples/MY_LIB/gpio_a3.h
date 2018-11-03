/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_A3_H
#define __GPIO_A3_H


#define PA3_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define PA3_CLK_DISABLE()         __HAL_RCC_GPIOA_CLK_DISABLE()

#define PA3_PIN                   GPIO_PIN_3
#define PA3_PORT                  GPIOA

#ifdef A3_OUTPUT
#define A3_OUTPUT_LOW()       HAL_GPIO_WritePin(PA3_PORT, PA3_PIN, GPIO_PIN_RESET)
#define A3_OUTPUT_HIGH()      HAL_GPIO_WritePin(PA3_PORT, PA3_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_a3_binding(void);


#endif
