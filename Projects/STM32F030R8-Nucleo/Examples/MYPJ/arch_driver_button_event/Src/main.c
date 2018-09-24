/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f0xx_hal.h"
#include "cmsis_os.h"
#include "device.h"
#include "button_event_driver.h"
#include "api_button_event_common.h"
#include "main.h"


static void main_thread(const void *Button_event)
{
	struct device *Button = (struct device *)Button_event;
	uint32_t press_time;
	
	while(1) {
		press_time = button_get_press_time(Button);
		if(press_time) {
			printf("press time %d\r\n", press_time);
		}
	}
}

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *Button_event = button_event_device_binding();
	
	button_event_init(Button_event);
	printf("All device init\r\n");
	
	osThreadDef(main, main_thread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(main), Button_event);
	
	osKernelStart();
	while(1) {
	}
}
