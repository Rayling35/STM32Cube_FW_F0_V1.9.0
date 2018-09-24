#include "stm32f0xx_hal.h"
#include "cmsis_os.h"
#include "stm32f0xx_it.h"


void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void SysTick_Handler(void)
{
  HAL_IncTick();
  osSystickHandler();
}
