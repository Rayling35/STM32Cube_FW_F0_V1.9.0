/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "gpio_b1.h"
#include "api_define.h"


#ifdef B1_OUTPUT
static void gpio_b1_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PB1_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PB1_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PB1_PORT, &GPIO_InitStruct);
}
#endif

#ifdef B1_INPUT
static void gpio_b1_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PB1_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PB1_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PB1_PORT, &GPIO_InitStruct);
}
#endif

#ifdef B1_EXTI
static void gpio_b1_exti_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PB1_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PB1_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(PB1_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI0_1_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
}

void EXTI0_1_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PB1_PIN);
}
#endif

static void gpio_b1_init(void)
{
	#ifdef B1_OUTPUT
	gpio_b1_output_init();
	#endif
	#ifdef B1_INPUT
	gpio_b1_input_init();
	#endif
	#ifdef B1_EXTI
	gpio_b1_exti_init();
	#endif
	printf("GPIO_B1 HAL init\r\n");
}

static int gpio_b1_read(void)
{
	return HAL_GPIO_ReadPin(PB1_PORT, PB1_PIN);
}

static void gpio_b1_write(uint8_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PB1_PORT, PB1_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PB1_PORT, PB1_PIN, GPIO_PIN_SET);
	}
}

static void gpio_b1_toggle_write(void)
{
	HAL_GPIO_TogglePin(PB1_PORT, PB1_PIN);
}

static int gpio_b1_lock(void)
{
	return HAL_GPIO_LockPin(PB1_PORT, PB1_PIN);
}

static struct gpio_api Gpio_b1_api = {
	.init         = gpio_b1_init,
	.read         = gpio_b1_read,
	.write        = gpio_b1_write,
	.toggle_write = gpio_b1_toggle_write,
	.lock         = gpio_b1_lock,
};

struct gpio_api* gpio_b1_binding(void)
{
	return &Gpio_b1_api;
}
