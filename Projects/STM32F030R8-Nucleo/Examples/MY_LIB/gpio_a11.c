/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "gpio_a11.h"
#include "api_define.h"


#ifdef A11_OUTPUT
static void gpio_a11_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PA11_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA11_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PA11_PORT, &GPIO_InitStruct);
}
#endif

#ifdef A11_INPUT
static void gpio_a11_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA11_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA11_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PA11_PORT, &GPIO_InitStruct);
}
#endif

#ifdef A11_EXTI
static void gpio_a11_exti_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA11_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA11_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(PA11_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI4_15_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}

void EXTI4_15_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PA11_PIN);
}
#endif

static void gpio_a11_init(void)
{
	#ifdef A11_OUTPUT
	gpio_a11_output_init();
	#endif
	#ifdef A11_INPUT
	gpio_a11_input_init();
	#endif
	#ifdef A11_EXTI
	gpio_a11_exti_init();
	#endif
	printf("GPIO_A11 HAL init\r\n");
}

static int gpio_a11_read(void)
{
	return HAL_GPIO_ReadPin(PA11_PORT, PA11_PIN);
}

static void gpio_a11_write(uint8_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PA11_PORT, PA11_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PA11_PORT, PA11_PIN, GPIO_PIN_SET);
	}
}

static void gpio_a11_toggle_write(void)
{
	HAL_GPIO_TogglePin(PA11_PORT, PA11_PIN);
}

static int gpio_a11_lock(void)
{
	return HAL_GPIO_LockPin(PA11_PORT, PA11_PIN);
}

static struct gpio_api Gpio_a11_api = {
	.init         = gpio_a11_init,
	.read         = gpio_a11_read,
	.write        = gpio_a11_write,
	.toggle_write = gpio_a11_toggle_write,
	.lock         = gpio_a11_lock,
};

struct gpio_api* gpio_a11_binding(void)
{
	return &Gpio_a11_api;
}
