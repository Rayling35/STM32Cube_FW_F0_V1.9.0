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

static int register_write(struct device *Dev, uint8_t reg, uint8_t *data, uint16_t length)
{
	struct rn8209g_data *D_data = Dev->data;
	const struct rn8209g_config *D_config = Dev->config;
	uint8_t write_en = D_config->value_enable_write;
	uint8_t write_dis = D_config->value_disable_write;
	int status;
	
	status = spi_register_write(D_data->Spi, RN8209G_SPECIAL, &write_en, 1);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, reg | RN8209G_W, data, length);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, RN8209G_SPECIAL, &write_dis, 1);
	if(status) {
		return status;
	}
	return 0;
}

static int register_read(struct device *Dev, uint8_t reg, uint8_t *data, uint16_t length)
{
	struct rn8209g_data *D_data = Dev->data;
	int status;
	
	status = spi_register_read(D_data->Spi, reg | RN8209G_R, data, length);
	if(status) {
		return status;
	}
	return 0;
}

static int ia_chnsel(struct device *Dev)
{
	struct rn8209g_data *D_data = Dev->data;
	const struct rn8209g_config *D_config = Dev->config;
	uint8_t write_en = D_config->value_enable_write;
	uint8_t write_dis = D_config->value_disable_write;
	uint8_t ia_chnsel = D_config->value_ia_chnsel;
	int status;
	
	status = spi_register_write(D_data->Spi, RN8209G_SPECIAL, &write_en, 1);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, RN8209G_SPECIAL, &ia_chnsel, 1);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, RN8209G_SPECIAL, &write_dis, 1);
	if(status) {
		return status;
	}
	return 0;
}

static int ib_chnsel(struct device *Dev)
{
	struct rn8209g_data *D_data = Dev->data;
	const struct rn8209g_config *D_config = Dev->config;
	uint8_t write_en = D_config->value_enable_write;
	uint8_t write_dis = D_config->value_disable_write;
	uint8_t ib_chnsel = D_config->value_ib_chnsel;
	int status;
	
	status = spi_register_write(D_data->Spi, RN8209G_SPECIAL, &write_en, 1);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, RN8209G_SPECIAL, &ib_chnsel, 1);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, RN8209G_SPECIAL, &write_dis, 1);
	if(status) {
		return status;
	}
	return 0;
}

static int software_reset(struct device *Dev)
{
	struct rn8209g_data *D_data = Dev->data;
	const struct rn8209g_config *D_config = Dev->config;
	uint8_t write_en = D_config->value_enable_write;
	uint8_t write_dis = D_config->value_disable_write;
	uint8_t soft_reset = D_config->value_soft_reset;
	int status;
	
	status = spi_register_write(D_data->Spi, RN8209G_SPECIAL, &write_en, 1);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, RN8209G_SPECIAL, &soft_reset, 1);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, RN8209G_SPECIAL, &write_dis, 1);
	if(status) {
		return status;
	}
	return 0;
}

static void clear_consumption_data(struct device *Dev)
{
	uint8_t reg_data[3];
	uint16_t *data = (uint16_t *)reg_data;
	
	register_read(Dev, RN8209G_EMUCON, reg_data, 2);
	REG_BIT_SET(*data, EnergyCLR_15, 1);
	register_write(Dev, RN8209G_EMUCON, reg_data, 2);
	
	register_read(Dev, RN8209G_EnergyP, reg_data, 3);
	register_read(Dev, RN8209G_EnergyD, reg_data, 3);
	
	register_read(Dev, RN8209G_EMUCON, reg_data, 2);
	REG_BIT_SET(*data, EnergyCLR_15, 0);
	register_write(Dev, RN8209G_EMUCON, reg_data, 2);
}

static void fetch_voltage(struct device *Dev)
{
	struct rn8209g_data *D_data = Dev->data;
	const struct rn8209g_config *D_config = Dev->config;
	uint8_t reg_data[4];
	uint32_t *data = (uint32_t *)reg_data;
	
	reg_data[3] = 0;
	register_read(Dev, RN8209G_URMS, reg_data, 3);
	printf("RN8209G_URMS    = 0x%06X, %d\r\n", *data, *data);
	*data = D_config->value_kv * *data / 100000;
	D_data->value_voltage_integer = *data / 100;
	D_data->value_voltage_decimal = *data % 100;
	printf("RN8209G_URMS    = %d.%dV\r\n", D_data->value_voltage_integer, D_data->value_voltage_decimal);
	
	reg_data[3] = 0;
	reg_data[2] = 0;
	register_read(Dev, RN8209G_UFreq, reg_data, 2);
	printf("RN8209G_UFreq   = 0x%04X, %d\r\n", *data, *data);
	*data = D_config->value_clkin*100 / 8 / *data;
	printf("RN8209G_UFreq   = %d.%dHz\r\n", *data/100, *data%100);
}

static void fetch_current(struct device *Dev)
{
	struct rn8209g_data *D_data = Dev->data;
	const struct rn8209g_config *D_config = Dev->config;
	uint8_t reg_data[4];
	uint32_t *data = (uint32_t *)reg_data;
	
	reg_data[3] = 0;
	register_read(Dev, RN8209G_IARMS, reg_data, 3);
	printf("RN8209G_IARMS   = 0x%06X, %d\r\n", *data, *data);
	*data = D_config->value_kia * *data / 1000000;
	D_data->value_current_integer = *data / 100;
	D_data->value_current_decimal = *data % 100;
	printf("RN8209G_IARMS   = %d.%dA\r\n", D_data->value_current_integer, D_data->value_current_decimal);
}

static void fetch_power(struct device *Dev)
{
	struct rn8209g_data *D_data = Dev->data;
	const struct rn8209g_config *D_config = Dev->config;
	uint8_t reg_data[4];
	uint32_t *data = (uint32_t *)reg_data;
	
	register_read(Dev, RN8209G_PowerPA, reg_data, 4);
	printf("RN8209G_PowerPA = 0x%08X, %d\r\n", *data, *data);
	*data = D_config->value_kp * *data / 1000000;
	D_data->value_power_integer = *data / 100;
	D_data->value_power_decimal = *data % 100;
	printf("RN8209G_PowerPA = %d.%dW\r\n", D_data->value_power_integer, D_data->value_power_decimal);
}

static void fetch_consumption(struct device *Dev)
{
	struct rn8209g_data *D_data = Dev->data;
	uint8_t reg_data[4];
	uint32_t *data = (uint32_t *)reg_data;
	
	reg_data[3] = 0;
	register_read(Dev, RN8209G_EnergyP, reg_data, 3);
	printf("RN8209G_EnergyP = 0x%06X, %d\r\n", *data, *data);
	
	D_data->value_consumption_integer = *data;
	printf("RN8209G_EnergyP = %dWh\r\n", D_data->value_consumption_integer);
}

static void register_list(struct device *Dev)
{
	uint8_t reg_data[4];
	
	register_read(Dev, RN8209G_SYSCON, reg_data, 2);
	printf("RN8209G_SYSCON    00H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_EMUCON, reg_data, 2);
	printf("RN8209G_EMUCON    01H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_HFConst, reg_data, 2);
	printf("RN8209G_HFConst   02H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_PStart, reg_data, 2);
	printf("RN8209G_PStart    03H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_DStart, reg_data, 2);
	printf("RN8209G_DStart    04H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_GPQA, reg_data, 2);
	printf("RN8209G_GPQA      05H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_GPQB, reg_data, 2);
	printf("RN8209G_GPQB      06H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_PhsA, reg_data, 1);
	printf("RN8209G_PhsA      07H = %02Xh\r\n", reg_data[0]);
	register_read(Dev, RN8209G_PhsB, reg_data, 1);
	printf("RN8209G_PhsB      08H = %02Xh\r\n", reg_data[0]);
	register_read(Dev, RN8209G_APOSA, reg_data, 2);
	printf("RN8209G_APOSA     0AH = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_APOSB, reg_data, 2);
	printf("RN8209G_APOSB     0BH = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_IARMSOS, reg_data, 2);
	printf("RN8209G_IARMSOS   0EH = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_IBRMSOS, reg_data, 2);
	printf("RN8209G_IBRMSOS   0FH = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_IBGain, reg_data, 2);
	printf("RN8209G_IBGain    10H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_D2FPL, reg_data, 2);
	printf("RN8209G_D2FPL     11H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_D2FPH, reg_data, 2);
	printf("RN8209G_D2FPH     12H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_DCIAH, reg_data, 2);
	printf("RN8209G_DCIAH     13H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_DCIBH, reg_data, 2);
	printf("RN8209G_DCIBH     14H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_DCUH, reg_data, 2);
	printf("RN8209G_DCUH      15H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_DCL, reg_data, 2);
	printf("RN8209G_DCL       16H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_EMUCON2, reg_data, 2);
	printf("RN8209G_EMUCON2   17H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_PFCnt, reg_data, 2);
	printf("RN8209G_PFCnt     20H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_DFCnt, reg_data, 2);
	printf("RN8209G_DFCnt     21H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	printf("\r\n");
	register_read(Dev, RN8209G_IARMS, reg_data, 3);
	printf("RN8209G_IARMS     22H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_IBRMS, reg_data, 3);
	printf("RN8209G_IBRMS     23H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_URMS, reg_data, 3);
	printf("RN8209G_URMS      24H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_UFreq, reg_data, 2);
	printf("RN8209G_UFreq     25H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_PowerPA, reg_data, 4);
	printf("RN8209G_PowerPA   26H = %02X%02X%02X%02Xh\r\n", reg_data[3], reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_PowerPB, reg_data, 4);
	printf("RN8209G_PowerPB   27H = %02X%02X%02X%02Xh\r\n", reg_data[3], reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_EnergyP, reg_data, 3);
	printf("RN8209G_EnergyP   29H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_ENergyP2, reg_data, 3);
	printf("RN8209G_ENergyP2  2AH = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_EnergyD, reg_data, 3);
	printf("RN8209G_EnergyD   2BH = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_EnergyD2, reg_data, 3);
	printf("RN8209G_EnergyD2  2CH = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_EMUStatus, reg_data, 3);
	printf("RN8209G_EMUStatus 2DH = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_SPL_IA, reg_data, 3);
	printf("RN8209G_SPL_IA    30H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_SPL_IB, reg_data, 3);
	printf("RN8209G_SPL_IB    31H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_SPL_U, reg_data, 3);
	printf("RN8209G_SPL_U     32H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_IE, reg_data, 1);
	printf("RN8209G_IE        40H = %02Xh\r\n", reg_data[0]);
	register_read(Dev, RN8209G_IF, reg_data, 1);
	printf("RN8209G_IF        41H = %02Xh\r\n", reg_data[0]);
	register_read(Dev, RN8209G_RIF, reg_data, 1);
	printf("RN8209G_RIF       42H = %02Xh\r\n", reg_data[0]);
	printf("\r\n");
	register_read(Dev, RN8209G_SysStatus, reg_data, 1);
	printf("RN8209G_SysStatus 43H = %02Xh\r\n", reg_data[0]);
	register_read(Dev, RN8209G_RData, reg_data, 4);
	printf("RN8209G_RData     44H = %02X%02X%02X%02Xh\r\n", reg_data[3], reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_WData, reg_data, 2);
	printf("RN8209G_WData     45H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209G_DeviceID, reg_data, 3);
	printf("RN8209G_DeviceID  7FH = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	printf("\r\n");
}

static int rn8209g_data_clear(struct device *Dev, enum sensor_type e_type)
{
	switch (e_type) {
		case SENSOR_RN8209G_CONSUMPTION:
			clear_consumption_data(Dev);
			break;
		default:
			return -1;
	}
	return 0;
}

static int rn8209g_value_get(struct device *Dev, enum sensor_type e_type, struct sensor_value *Data)
{
	struct rn8209g_data *D_data = Dev->data;
	
	switch (e_type) {
		case SENSOR_RN8209G_VOLTAGE:
			Data->value_integer = D_data->value_voltage_integer;
			Data->value_decimal = D_data->value_voltage_decimal;
			break;
		case SENSOR_RN8209G_CURRENT:
			Data->value_integer = D_data->value_current_integer;
			Data->value_decimal = D_data->value_current_decimal;
			break;
		case SENSOR_RN8209G_POWER:
			Data->value_integer = D_data->value_power_integer;
			Data->value_decimal = D_data->value_power_decimal;
			break;
		case SENSOR_RN8209G_CONSUMPTION:
			Data->value_integer = D_data->value_consumption_integer;
			Data->value_decimal = D_data->value_consumption_decimal;
			break;
		default:
			return -1;
	}
	return 0;
}

static int rn8209g_sample_fetch(struct device *Dev, enum sensor_type e_type)
{
	switch (e_type) {
		case SENSOR_RN8209G_VOLTAGE:
			fetch_voltage(Dev);
			break;
		case SENSOR_RN8209G_CURRENT:
			fetch_current(Dev);
			break;
		case SENSOR_RN8209G_POWER:
			fetch_power(Dev);
			break;
		case SENSOR_RN8209G_CONSUMPTION:
			fetch_consumption(Dev);
			break;
		case SENSOR_ALL:
			fetch_voltage(Dev);
			fetch_current(Dev);
			fetch_power(Dev);
			fetch_consumption(Dev);
			break;
		default:
			return -1;
	}
	printf("\r\n");
	register_list(Dev);
	printf("\r\n");
	return 0;
}

static const struct sensor_common_api Rn8209g_api = {
	.sample_fetch = rn8209g_sample_fetch,
	.value_get    = rn8209g_value_get,
	.data_clear   = rn8209g_data_clear
};

static void calibration(struct device *Dev)
{
	const struct rn8209g_config *D_config = Dev->config;
	uint8_t reg_data[2];
	uint16_t *data = (uint16_t *)reg_data;
	
	//00H
	register_read(Dev, RN8209G_SYSCON, reg_data, 2);
	REG_BIT_SET(*data, ADC2ON_6, 0); //1
	REG_BIT_SET(*data, PGAIB_5,  0); //1
	REG_BIT_SET(*data, PGAIB_4,  0); //1
	REG_BIT_SET(*data, PGAU_3,   0); //1
	REG_BIT_SET(*data, PGAU_2,   0); //1
	REG_BIT_SET(*data, PGAIA_1,  1); //1
	REG_BIT_SET(*data, PGAIA_0,  1); //1
	register_write(Dev, RN8209G_SYSCON, reg_data, 2);
	
	//01H
	register_read(Dev, RN8209G_EMUCON, reg_data, 2);
	REG_BIT_SET(*data, EnergyCLR_15, 0);
	REG_BIT_SET(*data, HPFIBOFF_14,  0); //1
	REG_BIT_SET(*data, QMOD_13,      0); //4
	REG_BIT_SET(*data, QMOD_12,      0); //4
	REG_BIT_SET(*data, PMOD_11,      0); //4
	REG_BIT_SET(*data, PMOD_10,      0); //4
	REG_BIT_SET(*data, ZXD1_9,       0);
	REG_BIT_SET(*data, ZXD0_8,       0);
	REG_BIT_SET(*data, ZXCFG_7,      0);
	REG_BIT_SET(*data, HPFIAOFF_6,   0); //1
	REG_BIT_SET(*data, HPFUOFF_5,    0); //1
	REG_BIT_SET(*data, CFSUEN_4,     0); //4
	REG_BIT_SET(*data, CFSU_3,       0); //4
	REG_BIT_SET(*data, CFSU_2,       0); //4
	REG_BIT_SET(*data, DRUN_1,       1); //4
	REG_BIT_SET(*data, PRUN_0,       1); //4
	register_write(Dev, RN8209G_EMUCON, reg_data, 2);
	
	//17H
	register_read(Dev, RN8209G_EMUCON2, reg_data, 2);
	REG_BIT_SET(*data, PhsB0_9,  0); //1
	REG_BIT_SET(*data, PhsA0_8,  0); //1
	REG_BIT_SET(*data, ZXMODE_6, 0);
	REG_BIT_SET(*data, D2FM_5,   0); //4
	REG_BIT_SET(*data, D2FM_4,   0); //4
	register_write(Dev, RN8209G_EMUCON2, reg_data, 2);
	
	//40H
	register_read(Dev, RN8209G_IE, reg_data, 1);
	REG_BIT_SET(*data, ZXIE_5,   0);
	REG_BIT_SET(*data, QEOIE_4,  0);
	REG_BIT_SET(*data, PEOIE_3,  0);
	REG_BIT_SET(*data, QFIE_2,   0);
	REG_BIT_SET(*data, PFIE_1,   0);
	REG_BIT_SET(*data, DUPDIE_0, 0);
	register_write(Dev, RN8209G_IE, reg_data, 1);
	
	//02H
	register_read(Dev, RN8209G_HFConst, reg_data, 2);
	*data = D_config->value_hfconst;
	register_write(Dev, RN8209G_HFConst, reg_data, 2);
	
	//03H
	register_read(Dev, RN8209G_PStart, reg_data, 2);
	*data = D_config->value_pstart;
	register_write(Dev, RN8209G_PStart, reg_data, 2);
	
	//04H
	register_read(Dev, RN8209G_DStart, reg_data, 2);
	*data = D_config->value_dstart;
	register_write(Dev, RN8209G_DStart, reg_data, 2);
	
	//05H
	register_read(Dev, RN8209G_GPQA, reg_data, 2);
	*data = D_config->value_gpqa;
	register_write(Dev, RN8209G_GPQA, reg_data, 2);
	
	//07H
	register_read(Dev, RN8209G_PhsA, reg_data, 1);
	*data = D_config->value_phsa;
	register_write(Dev, RN8209G_PhsA, reg_data, 1);
	
	//0AH
	register_read(Dev, RN8209G_APOSA, reg_data, 2);
	*data = D_config->value_aposa;
	register_write(Dev, RN8209G_APOSA, reg_data, 2);
	
	//0EH
	register_read(Dev, RN8209G_IARMSOS, reg_data, 2);
	*data = D_config->value_iarmsos;
	register_write(Dev, RN8209G_IARMSOS, reg_data, 2);
}

static struct rn8209g_data Rn8209g_data;

static const struct rn8209g_config Rn8209g_config = {
	.value_enable_write  = 0xE5,
	.value_disable_write = 0xDC,
	.value_ia_chnsel     = 0x5A,
	.value_ib_chnsel     = 0xA5,
	.value_soft_reset    = 0xFA,
	
	.value_clkin   = 3579545,
	.value_kv      = 1125,
	.value_kia     = 1512,
	.value_kp      = 8324,
	.value_hfconst = 0x0B00, //4
	.value_pstart  = 0x0060, //4
	.value_dstart  = 0x0120, //4
	.value_gpqa    = 0x0000, //2
	.value_phsa    = 0x00,   //1
	.value_aposa   = 0x0000, //2
	.value_iarmsos = 0x0000, //3
	/**
	Un = 108V
	Ib = 6.28A
	EC = 3200
	Kv = Un/URMS                                                 => 108/959597 = 0.0001125
	Ki = Ib/IARMS                                               => 6.28/415124 = 0.00001512
	Vu = Un*(1K/(1M+1K))*1                                     => 108*(1/1001) = 0.10789V
	Vi = Ib*Rm*16                                           => 6.28*0.00035*16 = 0.035168V
	HFConst = INT[(16.1079*Vu*Vi*10^11)/(Un*Ib*EC)]      => 6111781065/2170368 = 2816(B00h)
	Kp = (3.22155*10^12)/(2^32*HFConst*EC)  => 3221550000000/38702809297715200 = 0.00008324
	**/
};

static int rn8209g_device_init(struct device *Dev)
{
	struct rn8209g_data *D_data = Dev->data;
	
	D_data->Spi = spi2_cs0_device_binding();
	D_data->Gpio = gpio_b2_device_binding();
	spi_init(D_data->Spi);
	gpio_init(D_data->Gpio);
	printf("RN8209G device init\r\n");
	
	software_reset(Dev);
	ib_chnsel(Dev);
	ia_chnsel(Dev);
	
	register_list(Dev);
	calibration(Dev);
	
	return 0;
}

struct device Rn8209g = {
	.api    = &Rn8209g_api,
	.data   = &Rn8209g_data,
	.config = &Rn8209g_config,
	.init   = rn8209g_device_init,
};

struct device* rn8209g_device_binding(void)
{
	return &Rn8209g;
}

void b2_exti_handel(void)
{
	printf("RN8209G IRQ handel\r\n");
}
