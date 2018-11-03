/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "gpio_a0.h"
#include "api_define.h"


#ifdef A0_OUTPUT
static void gpio_a0_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PA0_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA0_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PA0_PORT, &GPIO_InitStruct);
}
#endif

#ifdef A0_INPUT
static void gpio_a0_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA0_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA0_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PA0_PORT, &GPIO_InitStruct);
}
#endif

#ifdef A0_EXTI
static void gpio_a0_exti_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA0_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA0_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(PA0_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI0_1_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
}

void EXTI0_1_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PA0_PIN);
}
#endif

static void gpio_a0_init(void)
{
	#ifdef A0_OUTPUT
	gpio_a0_output_init();
	#endif
	#ifdef A0_INPUT
	gpio_a0_input_init();
	#endif
	#ifdef A0_EXTI
	gpio_a0_exti_init();
	#endif
	printf("GPIO_A0 HAL init\r\n");
}

static int gpio_a0_read(void)
{
	return HAL_GPIO_ReadPin(PA0_PORT, PA0_PIN);
}

static void gpio_a0_write(uint8_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PA0_PORT, PA0_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PA0_PORT, PA0_PIN, GPIO_PIN_SET);
	}
}

static void gpio_a0_toggle_write(void)
{
	HAL_GPIO_TogglePin(PA0_PORT, PA0_PIN);
}

static int gpio_a0_lock(void)
{
	return HAL_GPIO_LockPin(PA0_PORT, PA0_PIN);
}

static struct gpio_api Gpio_a0_api = {
	.init         = gpio_a0_init,
	.read         = gpio_a0_read,
	.write        = gpio_a0_write,
	.toggle_write = gpio_a0_toggle_write,
	.lock         = gpio_a0_lock,
};

struct gpio_api* gpio_a0_binding(void)
{
	return &Gpio_a0_api;
}
