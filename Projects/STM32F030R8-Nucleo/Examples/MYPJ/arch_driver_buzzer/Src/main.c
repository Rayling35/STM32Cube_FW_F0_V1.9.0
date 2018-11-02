/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f0xx_hal.h"
#include "device.h"
#include "buzzer_driver.h"
#include "api_buzzer_common.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *Buzzer = buzzer_device_binding();
	buzzer_init(Buzzer);
	printf("All device init\r\n");
	
	uint8_t volume = 1;
	
	while(1) {
		for(volume = 1; volume < 21; volume++)
		{
			buzzer_output(Buzzer, 262, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 294, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 330, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 349, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 392, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 440, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 494, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 523, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 587, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 659, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 698, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 784, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 880, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 988, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 1046, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 1175, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 1318, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 1397, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 1568, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 1760, volume);
			HAL_Delay(100);
			buzzer_output(Buzzer, 1976, volume);
			HAL_Delay(100);
		}
	}
}
