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
	uint8_t count_click;
	
	while(1) {
		printf("Run %d\r\n", My_button_press_status.value_get_timer);
		
		if(My_button_press_status.value_get_timer > 0 && My_button_press_status.value_get_timer < 1000) {
			count_click = 1;
		}
		if(button_click && !count_click) {
			button_click = 0;
		}
		if(button_click && count_click) {
			button_click = 0;
			count_click = 0;
			printf("Button click\r\n");
		}
		
#if 1
		if(My_button_press_status.flag_button_press_1_second) {
			count_click = 0;
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
			printf("Save and Exit 1 second house\r\n");
		}
		
		if(My_button_press_status.flag_button_press_1_second) {
			count_click = 0;
			printf("go into Button press 1-1 seconds\r\n");
			while(My_button_press_status.flag_button_press_1_second || !button_click) {
				osDelay(1);
			}
			button_click = 0;
			while(1) {
				if(button_click) {
					button_click = 0;
					printf("Button click in 1-1 second house\r\n");
				}
				if(My_button_press_status.flag_button_press_1_second) {
					break;
				}
			}
			printf("Save and Exit 1-1 second house\r\n");
		}
		
		if(My_button_press_status.flag_button_press_1_second) {
			count_click = 0;
			printf("go into Button press 1-2 seconds\r\n");
			while(My_button_press_status.flag_button_press_1_second || !button_click) {
				osDelay(1);
			}
			button_click = 0;
			while(1) {
				if(button_click) {
					button_click = 0;
					printf("Button click in 1-2 second house\r\n");
				}
				if(My_button_press_status.flag_button_press_1_second) {
					break;
				}
			}
			printf("Save and Exit 1-2 second house\r\n");
		}
		
		if(My_button_press_status.flag_button_press_1_second) {
			count_click = 0;
			printf("go into Button press 1-3 seconds\r\n");
			while(My_button_press_status.flag_button_press_1_second || !button_click) {
				osDelay(1);
			}
			button_click = 0;
			while(1) {
				if(button_click) {
					button_click = 0;
					printf("Button click in 1-3 second house\r\n");
				}
				if(My_button_press_status.flag_button_press_2_second) {
					break;
				}
			}
			printf("Save and Exit 1-3 second house\r\n");
		}
		
		if(My_button_press_status.flag_button_press_2_second) {
			count_click = 0;
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
			while(My_button_press_status.flag_button_press_2_second) {
				osDelay(1);
			}
			printf("Save and Exit 2 second house\r\n");
		}
#endif
#if 1
		if(My_button_press_status.flag_button_press_3_second) {
			count_click = 0;
			printf("-->Button press 3 seconds\r\n");
			while(!My_button_press_status.flag_button_press_4_second || button_click) {
				if(button_click) {
					button_click = 0;
					printf("go into Button press 3 seconds\r\n");
					while(1) {
						if(button_click) {
							button_click = 0;
							printf("Button click in 3 second house\r\n");
						}
						if(My_button_press_status.flag_button_press_1_second) {
							printf("Save and Exit 3 second house\r\n");
							while(!button_click) {
								osDelay(1);
							}
							button_click = 0;
							break;
						}
					}
					break;
				}
				osDelay(1);
			}
		}
		
		if(My_button_press_status.flag_button_press_4_second) {
			count_click = 0;
			printf("-->Button press 4 seconds\r\n");
			while(!My_button_press_status.flag_button_press_5_second || button_click) {
				if(button_click) {
					button_click = 0;
					while(1) {
							printf("go into Button press 4-1 seconds\r\n");
							while(1) {
								if(button_click) {
									button_click = 0;
									printf("Button click in 4-1 second house\r\n");
								}
								if(My_button_press_status.flag_button_press_1_second) {
									break;
								}
							}
							printf("Save and Exit 4-1 second house\r\n");
						
						if(My_button_press_status.flag_button_press_1_second) {
							printf("go into Button press 4-2 seconds\r\n");
							while(My_button_press_status.flag_button_press_1_second || !button_click) {
								osDelay(1);
							}
							button_click = 0;
							while(1) {
								if(button_click) {
									button_click = 0;
									printf("Button click in 4-2 second house\r\n");
								}
								if(My_button_press_status.flag_button_press_1_second) {
									break;
								}
							}
							printf("Save and Exit 4-2 second house\r\n");
						}
						
						if(My_button_press_status.flag_button_press_1_second) {
							printf("go into Button press 4-3 seconds\r\n");
							while(My_button_press_status.flag_button_press_1_second || !button_click) {
								osDelay(1);
							}
							button_click = 0;
							while(1) {
								if(button_click) {
									button_click = 0;
									printf("Button click in 4-3 second house\r\n");
								}
								if(My_button_press_status.flag_button_press_1_second) {
									break;
								}
							}
							printf("Save and Exit 4-3 second house\r\n");
						}
						
						if(My_button_press_status.flag_button_press_1_second) {
							while(!button_click) {
								osDelay(1);
							}
							button_click = 0;
							break;
						}
					}
					break;
				}
				osDelay(1);
			}
		}
		
		if(My_button_press_status.flag_button_press_5_second) {
			count_click = 0;
			printf("-->Button press 5 seconds\r\n");
			while(!My_button_press_status.flag_button_press_6_second || button_click) {
				if(button_click) {
					button_click = 0;
					printf("go into Button press 5 seconds\r\n");
					while(1) {
						if(button_click) {
							button_click = 0;
							printf("Button click in 5 second house\r\n");
						}
						if(My_button_press_status.flag_button_press_1_second) {
							printf("Save and Exit 5 second house\r\n");
							while(!button_click) {
								osDelay(1);
							}
							button_click = 0;
							break;
						}
					}
					break;
				}
				osDelay(1);
			}
		}
		
		if(My_button_press_status.flag_button_press_6_second) {
			count_click = 0;
			printf("-->Button press 6 seconds\r\n");
			while(!My_button_press_status.flag_button_press_7_second || button_click) {
				if(button_click) {
					button_click = 0;
					printf("go into Button press 6 seconds\r\n");
					while(1) {
						if(button_click) {
							button_click = 0;
							printf("Button click in 6 second house\r\n");
						}
						if(My_button_press_status.flag_button_press_1_second) {
							printf("Save and Exit 6 second house\r\n");
							while(!button_click) {
								osDelay(1);
							}
							button_click = 0;
							break;
						}
					}
					break;
				}
				osDelay(1);
			}
		}
		
		if(My_button_press_status.flag_button_press_7_second) {
			count_click = 0;
			printf("-->Button press 7 seconds\r\n");
			while(!My_button_press_status.flag_button_press_8_second || button_click) {
				if(button_click) {
					button_click = 0;
					printf("go into Button press 7 seconds\r\n");
					while(1) {
						if(button_click) {
							button_click = 0;
							printf("Button click in 7 second house\r\n");
						}
						if(My_button_press_status.flag_button_press_1_second) {
							printf("Save and Exit 7 second house\r\n");
							while(!button_click) {
								osDelay(1);
							}
							button_click = 0;
							break;
						}
					}
					break;
				}
				osDelay(1);
			}
		}
		
		if(My_button_press_status.flag_button_press_8_second) {
			count_click = 0;
			printf("-->Button press 8 seconds\r\n");
			while(!My_button_press_status.flag_button_press_9_second || button_click) {
				if(button_click) {
					button_click = 0;
					printf("go into Button press 8 seconds\r\n");
					while(1) {
						if(button_click) {
							button_click = 0;
							printf("Button click in 8 second house\r\n");
						}
						if(My_button_press_status.flag_button_press_1_second) {
							printf("Save and Exit 8 second house\r\n");
							while(!button_click) {
								osDelay(1);
							}
							button_click = 0;
							break;
						}
					}
					break;
				}
				osDelay(1);
			}
		}
		
		if(My_button_press_status.flag_button_press_9_second) {
			count_click = 0;
			printf("-->Button press 9 seconds\r\n");
			while(!My_button_press_status.flag_button_press_10_second || button_click) {
				if(button_click) {
					button_click = 0;
					printf("go into Button press 9 seconds\r\n");
					while(1) {
						if(button_click) {
							button_click = 0;
							printf("Button click in 9 second house\r\n");
						}
						if(My_button_press_status.flag_button_press_1_second) {
							printf("Save and Exit 9 second house\r\n");
							while(!button_click) {
								osDelay(1);
							}
							button_click = 0;
							break;
						}
					}
					break;
				}
				osDelay(1);
			}
		}
		
		if(My_button_press_status.flag_button_press_10_second ||
			 My_button_press_status.flag_button_press_11_second ||
			 My_button_press_status.flag_button_press_12_second)
		{
			count_click = 0;
			printf("-->Button press 10 -> 11 -> 12 seconds\r\n");
			while(!My_button_press_status.flag_button_press_13_second || button_click) {
				if(button_click) {
					button_click = 0;
					printf("go into Button press 10 -> 11 -> 12 seconds\r\n");
					while(1) {
						if(button_click) {
							button_click = 0;
							printf("Button click in 10 -> 11 -> 12 second house\r\n");
						}
						if(My_button_press_status.flag_button_press_1_second) {
							printf("Save and Exit 10 -> 11 -> 12 second house\r\n");
							while(!button_click) {
								osDelay(1);
							}
							button_click = 0;
							break;
						}
					}
					break;
				}
				osDelay(1);
			}
		}
		
		if(My_button_press_status.flag_button_press_13_second) {
			count_click = 0;
			printf("Button press 13 seconds\r\n");
			while(My_button_press_status.flag_button_press_13_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_14_second) {
			count_click = 0;
			printf("Button press 14 seconds\r\n");
			while(My_button_press_status.flag_button_press_14_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_15_second) {
			count_click = 0;
			printf("Button press 15 seconds\r\n");
			while(My_button_press_status.flag_button_press_15_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_16_second) {
			count_click = 0;
			printf("Button press 16 seconds\r\n");
			while(My_button_press_status.flag_button_press_16_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_17_second) {
			count_click = 0;
			printf("Button press 17 seconds\r\n");
			while(My_button_press_status.flag_button_press_17_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_18_second) {
			count_click = 0;
			printf("Button press 18 seconds\r\n");
			while(My_button_press_status.flag_button_press_18_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_19_second) {
			count_click = 0;
			printf("Button press 19 seconds\r\n");
			while(My_button_press_status.flag_button_press_19_second) {
				osDelay(1);
			}
		}
		if(My_button_press_status.flag_button_press_20_second) {
			count_click = 0;
			printf("Button press 20 seconds\r\n");
			while(My_button_press_status.flag_button_press_20_second) {
				osDelay(1);
			}
		}
#endif
	}
}

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	#ifdef BUTTON_A11_EVENT
	struct device *Button_event = button_a11_event_device_binding();
	#endif
	
	#ifdef BUTTON_C13_EVENT
	struct device *Button_event = button_c13_event_device_binding();
	#endif
	
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
