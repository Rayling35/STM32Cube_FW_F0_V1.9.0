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


static struct button_status My_button_press_status;
static uint8_t button_click;

static void button_thread(const void *button_event)
{
	struct device *Button = (struct device *)button_event;
	button_click = 0;
	
	while(1) {
		button_get_press_status(Button, &My_button_press_status);
		if(My_button_press_status.flag_button_press) {
			while(1) {
				button_get_press_status(Button, &My_button_press_status);
				if(!My_button_press_status.flag_button_press) {
					button_click = 1;
					break;
				}
			}
		}
	}
}

static void main_thread(const void *argument)
{
	while(1) {
		if(button_click) {
			button_click = 0;
			printf("Button click\r\n");
		}
		
		if(My_button_press_status.flag_button_press_1_second) {
			printf("go into Button press 1 seconds\r\n");
			while(My_button_press_status.flag_button_press_1_second || !button_click) {
				osDelay(1);
			}
			button_click = 0;
			while(1) {
				if(button_click) {
					button_click = 0;
					printf("Button click in 1 second house\r\n");
				}
				if(My_button_press_status.flag_button_press_1_second) {
					break;
				}
			}
			while(My_button_press_status.flag_button_press_1_second) {
				osDelay(1);
			}
			printf("Save and Exit 1 second house\r\n");
		}
		
		if(My_button_press_status.flag_button_press_2_second) {
			printf("go into Button press 2 seconds\r\n");
			while(My_button_press_status.flag_button_press_2_second || !button_click) {
				osDelay(1);
			}
			button_click = 0;
			while(1) {
				if(button_click) {
					button_click = 0;
					printf("Button click in 2 second house\r\n");
				}
				if(My_button_press_status.flag_button_press_2_second) {
					break;
				}
			}
			printf("Save and Exit 2 second house\r\n");
		}
		
		if(My_button_press_status.flag_button_press_2_second) {
			printf("go into Button press 2-1 seconds\r\n");
			while(My_button_press_status.flag_button_press_2_second || !button_click) {
				osDelay(1);
			}
			button_click = 0;
			while(1) {
				if(button_click) {
					button_click = 0;
					printf("Button click in 2-1 second house\r\n");
				}
				if(My_button_press_status.flag_button_press_2_second) {
					break;
				}
			}
			while(My_button_press_status.flag_button_press_2_second) {
				osDelay(1);
			}
			printf("Save and Exit 2-1 second house\r\n");
		}
		
		if(My_button_press_status.flag_button_press_3_second) {
			printf("Button press 3 seconds\r\n");
			while(!My_button_press_status.flag_button_press_4_second && button_click) {
				if(button_click) {
					button_click = 0;
					printf("go into Button press 3 seconds\r\n");
					while(1) {
						if(button_click) {
							button_click = 0;
							printf("Button click in 3 second house\r\n");
						}
						if(My_button_press_status.flag_button_press_2_second) {
							printf("Save and Exit 3 second house\r\n");
							while(!button_click) {
								osDelay(1);
							}
							button_click = 0;
							break;
						}
					}
				}
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_4_second) {
			printf("Button press 4 seconds\r\n");
			while(!My_button_press_status.flag_button_press_5_second && button_click) {
				if(button_click) {
					button_click = 0;
					printf("go into Button press 4 seconds\r\n");
					while(1) {
						if(button_click) {
							button_click = 0;
							printf("Button click in 4 second house\r\n");
						}
						if(My_button_press_status.flag_button_press_2_second) {
							printf("Save and Exit 4 second house\r\n");
							while(!button_click) {
								osDelay(1);
							}
							button_click = 0;
							break;
						}
					}
				}
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_5_second) {
			printf("Button press 5 seconds\r\n");
			while(!My_button_press_status.flag_button_press_6_second && button_click) {
				if(button_click) {
					button_click = 0;
					printf("go into Button press 5 seconds\r\n");
					while(1) {
						if(button_click) {
							button_click = 0;
							printf("Button click in 5 second house\r\n");
						}
						if(My_button_press_status.flag_button_press_2_second) {
							printf("Save and Exit 5 second house\r\n");
							while(!button_click) {
								osDelay(1);
							}
							button_click = 0;
							break;
						}
					}
				}
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_6_second) {
			printf("Button press 6 seconds\r\n");
			while(My_button_press_status.flag_button_press_6_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_7_second) {
			printf("Button press 7 seconds\r\n");
			while(My_button_press_status.flag_button_press_7_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_8_second) {
			printf("Button press 8 seconds\r\n");
			while(My_button_press_status.flag_button_press_8_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_9_second) {
			printf("Button press 9 seconds\r\n");
			while(My_button_press_status.flag_button_press_9_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_10_second) {
			printf("Button press 10 seconds\r\n");
			while(My_button_press_status.flag_button_press_10_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_11_second) {
			printf("Button press 11 seconds\r\n");
			while(My_button_press_status.flag_button_press_11_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_12_second) {
			printf("Button press 12 seconds\r\n");
			while(My_button_press_status.flag_button_press_12_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_13_second) {
			printf("Button press 13 seconds\r\n");
			while(My_button_press_status.flag_button_press_13_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_14_second) {
			printf("Button press 14 seconds\r\n");
			while(My_button_press_status.flag_button_press_14_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_15_second) {
			printf("Button press 15 seconds\r\n");
			while(My_button_press_status.flag_button_press_15_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_16_second) {
			printf("Button press 16 seconds\r\n");
			while(My_button_press_status.flag_button_press_16_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_17_second) {
			printf("Button press 17 seconds\r\n");
			while(My_button_press_status.flag_button_press_17_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_18_second) {
			printf("Button press 18 seconds\r\n");
			while(My_button_press_status.flag_button_press_18_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_19_second) {
			printf("Button press 19 seconds\r\n");
			while(My_button_press_status.flag_button_press_19_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_20_second) {
			printf("Button press 20 seconds\r\n");
			while(My_button_press_status.flag_button_press_20_second) {
				osDelay(1);
			}
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
	osThreadCreate(osThread(main), NULL);
	
	osThreadDef(button, button_thread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(button), Button_event);
	
	osKernelStart();
	while(1) {
	}
}
