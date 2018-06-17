/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_C5_H
#define __GPIO_C5_H


#define PC5_CLK_ENABLE()          __HAL_RCC_GPIOC_CLK_ENABLE()
#define PC5_CLK_DISABLE()         __HAL_RCC_GPIOC_CLK_DISABLE()

#define PC5_PIN                   GPIO_PIN_5
#define PC5_PORT                  GPIOC

#ifdef C5_OUTPUT
#define C5_OUTPUT_LOW()       HAL_GPIO_WritePin(PC5_PORT, PC5_PIN, GPIO_PIN_RESET)
#define C5_OUTPUT_HIGH()      HAL_GPIO_WritePin(PC5_PORT, PC5_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_c5_binding(void);


#endif
