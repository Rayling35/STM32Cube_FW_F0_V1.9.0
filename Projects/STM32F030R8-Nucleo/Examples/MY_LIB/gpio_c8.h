/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_C8_H
#define __GPIO_C8_H


#define PC8_CLK_ENABLE()          __HAL_RCC_GPIOC_CLK_ENABLE()
#define PC8_CLK_DISABLE()         __HAL_RCC_GPIOC_CLK_DISABLE()

#define PC8_PIN                   GPIO_PIN_8
#define PC8_PORT                  GPIOC

#ifdef C8_OUTPUT
#define C8_OUTPUT_LOW()       HAL_GPIO_WritePin(PC8_PORT, PC8_PIN, GPIO_PIN_RESET)
#define C8_OUTPUT_HIGH()      HAL_GPIO_WritePin(PC8_PORT, PC8_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_c8_binding(void);


#endif
