/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_C6_H
#define __GPIO_C6_H


#define PC6_CLK_ENABLE()          __HAL_RCC_GPIOC_CLK_ENABLE()
#define PC6_CLK_DISABLE()         __HAL_RCC_GPIOC_CLK_DISABLE()

#define PC6_PIN                   GPIO_PIN_6
#define PC6_PORT                  GPIOC

#ifdef C6_OUTPUT
#define C6_OUTPUT_LOW()       HAL_GPIO_WritePin(PC6_PORT, PC6_PIN, GPIO_PIN_RESET)
#define C6_OUTPUT_HIGH()      HAL_GPIO_WritePin(PC6_PORT, PC6_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_c6_binding(void);


#endif
