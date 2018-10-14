/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "device.h"
#include "spi_driver.h"
#include "gpio_driver.h"
#include "api_spi_common.h"
#include "api_gpio_common.h"
#include "rn8209g_driver.h"
#include "api_sensor_common.h"


static int spi_register_write(struct device *Spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	int status;
	uint8_t tx_data[length+1];
	uint8_t dummy;
	uint16_t i;
	
	tx_data[0] = reg;
	for(i = 0; i < length; i++) {
		tx_data[length-i] = *data;
		data++;
	}
	status = spi_transmit_receive(Spi, tx_data, &dummy, length+1);
	status = spi_transmit_receive(Spi, tx_data, &dummy, length+1);
	return status;
}

static int spi_register_read(struct device *Spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	int status;
	uint8_t rx_data[length+1];
	uint16_t i;
	
	status = spi_transmit_receive(Spi, &reg, rx_data, length+1);
	status = spi_transmit_receive(Spi, &reg, rx_data, length+1);
	for(i = 0; i < length; i++) {
		data[length-1-i] = rx_data[i+1];
	}
	return status;
}

static void rn8209g_register_list(struct device *Dev)
{
	struct rn8209g_data *D_data = Dev->data;
	uint8_t reg_read[4];
	
	spi_register_read(D_data->Spi, RN8209G_SYSCON | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_SYSCON | RN8209G_R, reg_read, 2);
	printf("RN8209G_SYSCON    00H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_EMUCON | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_EMUCON | RN8209G_R, reg_read, 2);
	printf("RN8209G_EMUCON    01H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_HFConst | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_HFConst | RN8209G_R, reg_read, 2);
	printf("RN8209G_HFConst   02H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_PStart | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_PStart | RN8209G_R, reg_read, 2);
	printf("RN8209G_PStart    03H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_DStart | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_DStart | RN8209G_R, reg_read, 2);
	printf("RN8209G_DStart    04H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_GPQA | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_GPQA | RN8209G_R, reg_read, 2);
	printf("RN8209G_GPQA      05H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_GPQB | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_GPQB | RN8209G_R, reg_read, 2);
	printf("RN8209G_GPQB      06H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_PhsA | RN8209G_R, reg_read, 1);
	spi_register_read(D_data->Spi, RN8209G_PhsA | RN8209G_R, reg_read, 1);
	printf("RN8209G_PhsA      07H = %02Xh\r\n", reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_PhsB | RN8209G_R, reg_read, 1);
	spi_register_read(D_data->Spi, RN8209G_PhsB | RN8209G_R, reg_read, 1);
	printf("RN8209G_PhsB      08H = %02Xh\r\n", reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_APOSA | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_APOSA | RN8209G_R, reg_read, 2);
	printf("RN8209G_APOSA     0AH = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_APOSB | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_APOSB | RN8209G_R, reg_read, 2);
	printf("RN8209G_APOSB     0BH = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_IARMSOS | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_IARMSOS | RN8209G_R, reg_read, 2);
	printf("RN8209G_IARMSOS   0EH = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_IBRMSOS | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_IBRMSOS | RN8209G_R, reg_read, 2);
	printf("RN8209G_IBRMSOS   0FH = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_IBGain | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_IBGain | RN8209G_R, reg_read, 2);
	printf("RN8209G_IBGain    10H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_D2FPL | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_D2FPL | RN8209G_R, reg_read, 2);
	printf("RN8209G_D2FPL     11H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_D2FPH | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_D2FPH | RN8209G_R, reg_read, 2);
	printf("RN8209G_D2FPH     12H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_DCIAH | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_DCIAH | RN8209G_R, reg_read, 2);
	printf("(RN8209G_DCIAH    13H = %02X%02Xh)\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_DCIBH | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_DCIBH | RN8209G_R, reg_read, 2);
	printf("(RN8209G_DCIBH    14H = %02X%02Xh)\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_DCUH | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_DCUH | RN8209G_R, reg_read, 2);
	printf("(RN8209G_DCUH     15H = %02X%02Xh)\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_DCL | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_DCL | RN8209G_R, reg_read, 2);
	printf("(RN8209G_DCL      16H = %02X%02Xh)\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_EMUCON2 | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_EMUCON2 | RN8209G_R, reg_read, 2);
	printf("RN8209G_EMUCON2   17H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	printf("\r\n");
	
	spi_register_read(D_data->Spi, RN8209G_PFCnt | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_PFCnt | RN8209G_R, reg_read, 2);
	printf("RN8209G_PFCnt     20H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_DFCnt | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_DFCnt | RN8209G_R, reg_read, 2);
	printf("RN8209G_DFCnt     21H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	printf("\r\n");
	
	spi_register_read(D_data->Spi, RN8209G_IARMS | RN8209G_R, reg_read, 3);
	spi_register_read(D_data->Spi, RN8209G_IARMS | RN8209G_R, reg_read, 3);
	printf("RN8209G_IARMS     22H = %02X%02X%02Xh\r\n", reg_read[2], reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_IBRMS | RN8209G_R, reg_read, 3);
	spi_register_read(D_data->Spi, RN8209G_IBRMS | RN8209G_R, reg_read, 3);
	printf("RN8209G_IBRMS     23H = %02X%02X%02Xh\r\n", reg_read[2], reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_URMS | RN8209G_R, reg_read, 3);
	spi_register_read(D_data->Spi, RN8209G_URMS | RN8209G_R, reg_read, 3);
	printf("RN8209G_URMS      24H = %02X%02X%02Xh\r\n", reg_read[2], reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_UFreq | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_UFreq | RN8209G_R, reg_read, 2);
	printf("RN8209G_UFreq     25H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_PowerPA | RN8209G_R, reg_read, 4);
	spi_register_read(D_data->Spi, RN8209G_PowerPA | RN8209G_R, reg_read, 4);
	printf("RN8209G_PowerPA   26H = %02X%02X%02X%02Xh\r\n", reg_read[3], reg_read[2], reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_PowerPB | RN8209G_R, reg_read, 4);
	spi_register_read(D_data->Spi, RN8209G_PowerPB | RN8209G_R, reg_read, 4);
	printf("RN8209G_PowerPB   27H = %02X%02X%02X%02Xh\r\n", reg_read[3], reg_read[2], reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_EnergyP | RN8209G_R, reg_read, 3);
	spi_register_read(D_data->Spi, RN8209G_EnergyP | RN8209G_R, reg_read, 3);
	printf("RN8209G_EnergyP   29H = %02X%02X%02Xh\r\n", reg_read[2], reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_ENergyP2 | RN8209G_R, reg_read, 3);
	spi_register_read(D_data->Spi, RN8209G_ENergyP2 | RN8209G_R, reg_read, 3);
	printf("RN8209G_ENergyP2  2AH = %02X%02X%02Xh\r\n", reg_read[2], reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_EnergyD | RN8209G_R, reg_read, 3);
	spi_register_read(D_data->Spi, RN8209G_EnergyD | RN8209G_R, reg_read, 3);
	printf("RN8209G_EnergyD   2BH = %02X%02X%02Xh\r\n", reg_read[2], reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_EnergyD2 | RN8209G_R, reg_read, 3);
	spi_register_read(D_data->Spi, RN8209G_EnergyD2 | RN8209G_R, reg_read, 3);
	printf("RN8209G_EnergyD2  2CH = %02X%02X%02Xh\r\n", reg_read[2], reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_EMUStatus | RN8209G_R, reg_read, 3);
	spi_register_read(D_data->Spi, RN8209G_EMUStatus | RN8209G_R, reg_read, 3);
	printf("RN8209G_EMUStatus 2DH = %02X%02X%02Xh\r\n", reg_read[2], reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_SPL_IA | RN8209G_R, reg_read, 3);
	spi_register_read(D_data->Spi, RN8209G_SPL_IA | RN8209G_R, reg_read, 3);
	printf("(RN8209G_SPL_IA   30H = %02X%02X%02Xh)\r\n", reg_read[2], reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_SPL_IB | RN8209G_R, reg_read, 3);
	spi_register_read(D_data->Spi, RN8209G_SPL_IB | RN8209G_R, reg_read, 3);
	printf("(RN8209G_SPL_IB   31H = %02X%02X%02Xh)\r\n", reg_read[2], reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_SPL_U | RN8209G_R, reg_read, 3);
	spi_register_read(D_data->Spi, RN8209G_SPL_U | RN8209G_R, reg_read, 3);
	printf("(RN8209G_SPL_U    32H = %02X%02X%02Xh)\r\n", reg_read[2], reg_read[1], reg_read[0]);
	printf("\r\n");
	
	spi_register_read(D_data->Spi, RN8209G_IE | RN8209G_R, reg_read, 1);
	spi_register_read(D_data->Spi, RN8209G_IE | RN8209G_R, reg_read, 1);
	printf("RN8209G_IE        40H = %02Xh\r\n", reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_IF | RN8209G_R, reg_read, 1);
	spi_register_read(D_data->Spi, RN8209G_IF | RN8209G_R, reg_read, 1);
	printf("RN8209G_IF        41H = %02Xh\r\n", reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_RIF | RN8209G_R, reg_read, 1);
	spi_register_read(D_data->Spi, RN8209G_RIF | RN8209G_R, reg_read, 1);
	printf("RN8209G_RIF       42H = %02Xh\r\n", reg_read[0]);
	printf("\r\n");
	
	spi_register_read(D_data->Spi, RN8209G_SysStatus | RN8209G_R, reg_read, 1);
	spi_register_read(D_data->Spi, RN8209G_SysStatus | RN8209G_R, reg_read, 1);
	printf("RN8209G_SysStatus 43H = %02Xh\r\n", reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_RData | RN8209G_R, reg_read, 4);
	spi_register_read(D_data->Spi, RN8209G_RData | RN8209G_R, reg_read, 4);
	printf("RN8209G_RData     44H = %02X%02X%02X%02Xh\r\n", reg_read[3], reg_read[2], reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_WData | RN8209G_R, reg_read, 2);
	spi_register_read(D_data->Spi, RN8209G_WData | RN8209G_R, reg_read, 2);
	printf("RN8209G_WData     45H = %02X%02Xh\r\n", reg_read[1], reg_read[0]);
	
	spi_register_read(D_data->Spi, RN8209G_DeviceID | RN8209G_R, reg_read, 3);
	spi_register_read(D_data->Spi, RN8209G_DeviceID | RN8209G_R, reg_read, 3);
	printf("RN8209G_DeviceID  7FH = %02X%02X%02Xh\r\n", reg_read[2], reg_read[1], reg_read[0]);
	printf("\r\n");
}

static int rn8209g_value_get(struct device *Dev, enum sensor_type e_type, struct sensor_value *Val)
{
	return 0;
}

static int rn8209g_sample_fetch(struct device *Dev, enum sensor_type e_type)
{
//	struct rn8209g_data *D_data = Dev->data;
//	uint8_t *rn8209_id = D_data->value_rn8209g_rx;
	
	rn8209g_register_list(Dev);
	
	return 0;
}

static const struct sensor_common_api Rn8209g_api = {
	.sample_fetch = rn8209g_sample_fetch,
	.value_get    = rn8209g_value_get,
};

static struct rn8209g_data Rn8209g_data;

static int rn8209g_device_init(struct device *Dev)
{
	struct rn8209g_data *D_data = Dev->data;
	
	D_data->Spi = spi2_cs0_device_binding();
	D_data->Gpio = gpio_b2_device_binding();
	spi_init(D_data->Spi);
	gpio_init(D_data->Gpio);
	printf("RN8209G device init\r\n");
	
	uint8_t reg_write[2];
	uint8_t sw_reset = 0xFA; //reset
	uint8_t reg_w_en = 0xE5; //enable write
	uint8_t reg_w_dis = 0xDC; //disable write
	
	spi_register_write(D_data->Spi, RN8209G_SPECIAL, &sw_reset, 1);
	spi_register_write(D_data->Spi, RN8209G_SPECIAL, &reg_w_en, 1);
	
	reg_write[1] = 0x00;
	reg_write[0] = 0x03;
	spi_register_write(D_data->Spi, RN8209G_SYSCON | RN8209G_W, reg_write, 2);
	
	spi_register_write(D_data->Spi, RN8209G_SPECIAL, &reg_w_dis, 1);
	
	return 0;
}

struct device Rn8209g = {
	.api  = &Rn8209g_api,
	.data = &Rn8209g_data,
	.init = rn8209g_device_init,
};

struct device* rn8209g_device_binding(void)
{
	return &Rn8209g;
}

void b2_exti_handel(void)
{
	printf("RN8209G IRQ handel\r\n");
}
