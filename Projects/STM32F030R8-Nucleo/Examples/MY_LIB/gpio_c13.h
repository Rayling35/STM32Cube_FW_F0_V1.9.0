/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_C13_H
#define __GPIO_C13_H


#define PC13_CLK_ENABLE()         __HAL_RCC_GPIOC_CLK_ENABLE()
#define PC13_CLK_DISABLE()        __HAL_RCC_GPIOC_CLK_DISABLE()

#define PC13_PIN                  GPIO_PIN_13
#define PC13_PORT                 GPIOC

#ifdef C13_OUTPUT
#define C13_OUTPUT_LOW()      HAL_GPIO_WritePin(PC13_PORT, PC13_PIN, GPIO_PIN_RESET)
#define C13_OUTPUT_HIGH()     HAL_GPIO_WritePin(PC13_PORT, PC13_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_c13_binding(void);


#endif
