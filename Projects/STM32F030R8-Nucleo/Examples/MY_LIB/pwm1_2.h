/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __PWM1_2_H
#define __PWM1_2_H


#define TIM1_CLK_ENABLE()              __HAL_RCC_TIM1_CLK_ENABLE()
#define TIM1_CHANNEL2_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()

#define TIM1_CHANNEL2_PIN              GPIO_PIN_9
#define TIM1_CHANNEL2_PORT             GPIOA
#define TIM1_CHANNEL2_AF               GPIO_AF2_TIM1

#define TIM1_CHANNEL2                  TIM_CHANNEL_2

struct pwm_api* pwm1_2_binding(void);


#endif
