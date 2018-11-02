/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __PWM3_4_H
#define __PWM3_4_H


#define TIM3_CLK_ENABLE()              __HAL_RCC_TIM3_CLK_ENABLE()
#define TIM3_CHANNEL4_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()

#define TIM3_CHANNEL4_PIN              GPIO_PIN_1
#define TIM3_CHANNEL4_PORT             GPIOB
#define TIM3_CHANNEL4_AF               GPIO_AF1_TIM3

#define TIM3_CHANNEL4                  TIM_CHANNEL_4

struct pwm_api* pwm3_4_binding(void);


#endif
