/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __PWM1_3_H
#define __PWM1_3_H


#define TIM1_CLK_ENABLE()              __HAL_RCC_TIM1_CLK_ENABLE()
#define TIM1_CHANNEL3_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()

#define TIM1_CHANNEL3_PIN              GPIO_PIN_10
#define TIM1_CHANNEL3_PORT             GPIOA
#define TIM1_CHANNEL3_AF               GPIO_AF2_TIM1

#define TIM1_CHANNEL3                  TIM_CHANNEL_3

struct pwm_api* pwm1_3_binding(void);


#endif
