/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "uart_printf.h"


UART_HandleTypeDef UartHandlePrintf;

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&UartHandlePrintf, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

void _UARTxPrintf_MspInit(void)
{  
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  USARTxPrintf_TX_GPIO_CLK_ENABLE();
  USARTxPrintf_RX_GPIO_CLK_ENABLE();

  USARTxPrintf_CLK_ENABLE(); 
  
  GPIO_InitStruct.Pin       = USARTxPrintf_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = USARTxPrintf_TX_AF;
  HAL_GPIO_Init(USARTxPrintf_TX_GPIO_PORT, &GPIO_InitStruct);
    
  GPIO_InitStruct.Pin = USARTxPrintf_RX_PIN;
  GPIO_InitStruct.Alternate = USARTxPrintf_RX_AF;
  HAL_GPIO_Init(USARTxPrintf_RX_GPIO_PORT, &GPIO_InitStruct);
}

void _UARTxPrintf_MspDeInit(void)
{
  USARTxPrintf_FORCE_RESET();
  USARTxPrintf_RELEASE_RESET();

  HAL_GPIO_DeInit(USARTxPrintf_TX_GPIO_PORT, USARTxPrintf_TX_PIN);
  HAL_GPIO_DeInit(USARTxPrintf_RX_GPIO_PORT, USARTxPrintf_RX_PIN);
}

void uart_printf_init(void)
{
  _UARTxPrintf_MspDeInit();
  _UARTxPrintf_MspInit();
  UartHandlePrintf.Instance          = USARTxPrintf;
  UartHandlePrintf.Init.BaudRate     = 115200;
  UartHandlePrintf.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandlePrintf.Init.StopBits     = UART_STOPBITS_1;
  UartHandlePrintf.Init.Parity       = UART_PARITY_NONE;
  UartHandlePrintf.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandlePrintf.Init.Mode         = UART_MODE_TX_RX;
  UartHandlePrintf.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&UartHandlePrintf);
	
  //printf("** Printf() init OK ** \n\r");
}
