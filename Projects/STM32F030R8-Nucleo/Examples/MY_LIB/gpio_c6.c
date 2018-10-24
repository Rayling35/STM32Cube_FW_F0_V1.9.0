/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "gpio_c6.h"
#include "api_define.h"


#ifdef C6_OUTPUT
static void gpio_c6_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PC6_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC6_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PC6_PORT, &GPIO_InitStruct);
}
#endif

#ifdef C6_INPUT
static void gpio_c6_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PC6_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC6_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PC6_PORT, &GPIO_InitStruct);
}
#endif

#ifdef C6_EXTI
static void gpio_c6_exti_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PC6_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC6_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(PC6_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI4_15_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}

void EXTI4_15_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PC6_PIN);
}
#endif

static void gpio_c6_init(void)
{
	#ifdef C6_OUTPUT
	gpio_c6_output_init();
	#endif
	#ifdef C6_INPUT
	gpio_c6_input_init();
	#endif
	#ifdef C6_EXTI
	gpio_c6_exti_init();
	#endif
	printf("GPIO_C6 HAL init\r\n");
}

static int gpio_c6_read(void)
{
	return HAL_GPIO_ReadPin(PC6_PORT, PC6_PIN);
}

static void gpio_c6_write(uint8_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PC6_PORT, PC6_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PC6_PORT, PC6_PIN, GPIO_PIN_SET);
	}
}

static void gpio_c6_toggle_write(void)
{
	HAL_GPIO_TogglePin(PC6_PORT, PC6_PIN);
}

static int gpio_c6_lock(void)
{
	return HAL_GPIO_LockPin(PC6_PORT, PC6_PIN);
}

static struct gpio_api Gpio_c6_api = {
	.init         = gpio_c6_init,
	.read         = gpio_c6_read,
	.write        = gpio_c6_write,
	.toggle_write = gpio_c6_toggle_write,
	.lock         = gpio_c6_lock,
};

struct gpio_api* gpio_c6_binding(void)
{
	return &Gpio_c6_api;
}
