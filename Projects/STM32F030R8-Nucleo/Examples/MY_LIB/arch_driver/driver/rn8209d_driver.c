/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "add_define.h"
#include "device.h"
#include "spi_driver.h"
#include "api_spi_common.h"
#include "rn8209d_driver.h"
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
	struct rn8209d_data *D_data = Dev->data;
	const struct rn8209d_config *D_config = Dev->config;
	uint8_t write_en = D_config->value_enable_write;
	uint8_t write_dis = D_config->value_disable_write;
	int status;
	
	status = spi_register_write(D_data->Spi, RN8209D_SPECIAL, &write_en, 1);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, reg | RN8209D_W, data, length);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, RN8209D_SPECIAL, &write_dis, 1);
	if(status) {
		return status;
	}
	return 0;
}

static int register_read(struct device *Dev, uint8_t reg, uint8_t *data, uint16_t length)
{
	struct rn8209d_data *D_data = Dev->data;
	int status;
	
	status = spi_register_read(D_data->Spi, reg | RN8209D_R, data, length);
	if(status) {
		return status;
	}
	return 0;
}

static int ia_chnsel(struct device *Dev)
{
	struct rn8209d_data *D_data = Dev->data;
	const struct rn8209d_config *D_config = Dev->config;
	uint8_t write_en = D_config->value_enable_write;
	uint8_t write_dis = D_config->value_disable_write;
	uint8_t ia_chnsel = D_config->value_ia_chnsel;
	int status;
	
	status = spi_register_write(D_data->Spi, RN8209D_SPECIAL, &write_en, 1);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, RN8209D_SPECIAL, &ia_chnsel, 1);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, RN8209D_SPECIAL, &write_dis, 1);
	if(status) {
		return status;
	}
	return 0;
}

static int ib_chnsel(struct device *Dev)
{
	struct rn8209d_data *D_data = Dev->data;
	const struct rn8209d_config *D_config = Dev->config;
	uint8_t write_en = D_config->value_enable_write;
	uint8_t write_dis = D_config->value_disable_write;
	uint8_t ib_chnsel = D_config->value_ib_chnsel;
	int status;
	
	status = spi_register_write(D_data->Spi, RN8209D_SPECIAL, &write_en, 1);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, RN8209D_SPECIAL, &ib_chnsel, 1);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, RN8209D_SPECIAL, &write_dis, 1);
	if(status) {
		return status;
	}
	return 0;
}

static int software_reset(struct device *Dev)
{
	struct rn8209d_data *D_data = Dev->data;
	const struct rn8209d_config *D_config = Dev->config;
	uint8_t write_en = D_config->value_enable_write;
	uint8_t write_dis = D_config->value_disable_write;
	uint8_t soft_reset = D_config->value_soft_reset;
	int status;
	
	status = spi_register_write(D_data->Spi, RN8209D_SPECIAL, &write_en, 1);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, RN8209D_SPECIAL, &soft_reset, 1);
	if(status) {
		return status;
	}
	status = spi_register_write(D_data->Spi, RN8209D_SPECIAL, &write_dis, 1);
	if(status) {
		return status;
	}
	return 0;
}

static void clear_consumption_data(struct device *Dev)
{
	uint8_t reg_data[3];
	uint16_t *reg_value = (uint16_t *)reg_data;
	
	register_read(Dev, RN8209D_EMUCON, reg_data, 2);
	REG_BIT_SET(*reg_value, EnergyCLR_15, 1);
	register_write(Dev, RN8209D_EMUCON, reg_data, 2);
	
	register_read(Dev, RN8209D_EnergyP, reg_data, 3);
	register_read(Dev, RN8209D_EnergyD, reg_data, 3);
	
	register_read(Dev, RN8209D_EMUCON, reg_data, 2);
	REG_BIT_SET(*reg_value, EnergyCLR_15, 0);
	register_write(Dev, RN8209D_EMUCON, reg_data, 2);
}

static void fetch_voltage(struct device *Dev)
{
	struct rn8209d_data *D_data = Dev->data;
	const struct rn8209d_config *D_config = Dev->config;
	uint8_t reg_data[4];
	uint32_t *reg_value = (uint32_t *)reg_data;
	
	reg_data[3] = 0;
	register_read(Dev, RN8209D_URMS, reg_data, 3);
//	printf("RN8209D URMS    = 0x%06X, %d\r\n", *reg_value, *reg_value);
	*reg_value = D_config->value_kv * *reg_value / 100000;
	D_data->value_voltage_integer = *reg_value / 100;
	D_data->value_voltage_decimal = *reg_value % 100;
//	printf("RN8209D URMS    = %d.%d V\r\n", D_data->value_voltage_integer, D_data->value_voltage_decimal);
	
	reg_data[3] = 0;
	reg_data[2] = 0;
	register_read(Dev, RN8209D_UFreq, reg_data, 2);
//	printf("RN8209D UFreq   = 0x%04X, %d\r\n", *reg_value, *reg_value);
	*reg_value = D_config->value_clkin*100 / 8 / *reg_value;
//	printf("RN8209D UFreq   = %d.%d Hz\r\n", *reg_value/100, *reg_value%100);
}

static void fetch_current(struct device *Dev)
{
	struct rn8209d_data *D_data = Dev->data;
	const struct rn8209d_config *D_config = Dev->config;
	uint8_t reg_data[4];
	uint32_t *reg_value = (uint32_t *)reg_data;
	
	reg_data[3] = 0;
	register_read(Dev, RN8209D_IARMS, reg_data, 3);
//	printf("RN8209D IARMS   = 0x%06X, %d\r\n", *reg_value, *reg_value);
	*reg_value = D_config->value_kia * *reg_value / 1000000;
	D_data->value_current_integer = *reg_value / 100;
	D_data->value_current_decimal = *reg_value % 100;
//	printf("RN8209D IARMS   = %d.%d A\r\n", D_data->value_current_integer, D_data->value_current_decimal);
}

static void fetch_power(struct device *Dev)
{
	struct rn8209d_data *D_data = Dev->data;
	const struct rn8209d_config *D_config = Dev->config;
	uint8_t reg_data[4];
	uint32_t *reg_value = (uint32_t *)reg_data;
	
	register_read(Dev, RN8209D_PowerPA, reg_data, 4);
//	printf("RN8209D PowerPA = 0x%08X, %d\r\n", *reg_value, *reg_value);
	*reg_value = D_config->value_kp * *reg_value / 1000000;
	D_data->value_power_integer = *reg_value / 100;
	D_data->value_power_decimal = *reg_value % 100;
//	printf("RN8209D PowerPA = %d.%d W\r\n", D_data->value_power_integer, D_data->value_power_decimal);
}

static void fetch_consumption(struct device *Dev)
{
	struct rn8209d_data *D_data = Dev->data;
	uint8_t reg_data[4];
	uint32_t *reg_value = (uint32_t *)reg_data;
	
	reg_data[3] = 0;
	register_read(Dev, RN8209D_EnergyP, reg_data, 3);
//	printf("RN8209D EnergyP = 0x%06X, %d\r\n", *reg_value, *reg_value);
	
	D_data->value_consumption_integer = *reg_value;
//	printf("RN8209D EnergyP = %d Wh\r\n", D_data->value_consumption_integer);
}

/*static void register_list(struct device *Dev)
{
	uint8_t reg_data[4];
	
	printf("---1---\r\n");
	register_read(Dev, RN8209D_SYSCON, reg_data, 2);
	printf("RN8209D SYSCON    00H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_EMUCON, reg_data, 2);
	printf("RN8209D EMUCON    01H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_HFConst, reg_data, 2);
	printf("RN8209D HFConst   02H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_PStart, reg_data, 2);
	printf("RN8209D PStart    03H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_DStart, reg_data, 2);
	printf("RN8209D DStart    04H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_GPQA, reg_data, 2);
	printf("RN8209D GPQA      05H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_GPQB, reg_data, 2);
	printf("RN8209D GPQB      06H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_PhsA, reg_data, 1);
	printf("RN8209D PhsA      07H = %02Xh\r\n", reg_data[0]);
	register_read(Dev, RN8209D_PhsB, reg_data, 1);
	printf("RN8209D PhsB      08H = %02Xh\r\n", reg_data[0]);
	register_read(Dev, RN8209D_QPhsCal, reg_data, 2);
	printf("RN8209D QPhsCal   09H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_APOSA, reg_data, 2);
	printf("RN8209D APOSA     0AH = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_APOSB, reg_data, 2);
	printf("RN8209D APOSB     0BH = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_RPOSA, reg_data, 2);
	printf("RN8209D RPOSA     0CH = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_RPOSB, reg_data, 2);
	printf("RN8209D RPOSB     0DH = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_IARMSOS, reg_data, 2);
	printf("RN8209D IARMSOS   0EH = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_IBRMSOS, reg_data, 2);
	printf("RN8209D IBRMSOS   0FH = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_IBGain, reg_data, 2);
	printf("RN8209D IBGain    10H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_D2FPL, reg_data, 2);
	printf("RN8209D D2FPL     11H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_D2FPH, reg_data, 2);
	printf("RN8209D D2FPH     12H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_DCIAH, reg_data, 2);
	printf("RN8209D DCIAH     13H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_DCIBH, reg_data, 2);
	printf("RN8209D DCIBH     14H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_DCUH, reg_data, 2);
	printf("RN8209D DCUH      15H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_DCL, reg_data, 2);
	printf("RN8209D DCL       16H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_EMUCON2, reg_data, 2);
	printf("RN8209D EMUCON2   17H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	printf("---2---\r\n");
	register_read(Dev, RN8209D_PFCnt, reg_data, 2);
	printf("RN8209D PFCnt     20H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_DFCnt, reg_data, 2);
	printf("RN8209D DFCnt     21H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_IARMS, reg_data, 3);
	printf("RN8209D IARMS     22H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_IBRMS, reg_data, 3);
	printf("RN8209D IBRMS     23H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_URMS, reg_data, 3);
	printf("RN8209D URMS      24H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_UFreq, reg_data, 2);
	printf("RN8209D UFreq     25H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_PowerPA, reg_data, 4);
	printf("RN8209D PowerPA   26H = %02X%02X%02X%02Xh\r\n", reg_data[3], reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_PowerPB, reg_data, 4);
	printf("RN8209D PowerPB   27H = %02X%02X%02X%02Xh\r\n", reg_data[3], reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_PowerQ, reg_data, 4);
	printf("RN8209D PowerQ    28H = %02X%02X%02X%02Xh\r\n", reg_data[3], reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_EnergyP, reg_data, 3);
	printf("RN8209D EnergyP   29H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_ENergyP2, reg_data, 3);
	printf("RN8209D ENergyP2  2AH = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_EnergyD, reg_data, 3);
	printf("RN8209D EnergyD   2BH = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_EnergyD2, reg_data, 3);
	printf("RN8209D EnergyD2  2CH = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_EMUStatus, reg_data, 3);
	printf("RN8209D EMUStatus 2DH = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_SPL_IA, reg_data, 3);
	printf("RN8209D SPL_IA    30H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_SPL_IB, reg_data, 3);
	printf("RN8209D SPL_IB    31H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_SPL_U, reg_data, 3);
	printf("RN8209D SPL_U     32H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_UFreq2, reg_data, 3);
	printf("RN8209D UFreq2    35H = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	printf("---3---\r\n");
	register_read(Dev, RN8209D_IE, reg_data, 1);
	printf("RN8209D IE        40H = %02Xh\r\n", reg_data[0]);
	register_read(Dev, RN8209D_IF, reg_data, 1);
	printf("RN8209D IF        41H = %02Xh\r\n", reg_data[0]);
	register_read(Dev, RN8209D_RIF, reg_data, 1);
	printf("RN8209D RIF       42H = %02Xh\r\n", reg_data[0]);
	printf("---4---\r\n");
	register_read(Dev, RN8209D_SysStatus, reg_data, 1);
	printf("RN8209D SysStatus 43H = %02Xh\r\n", reg_data[0]);
	register_read(Dev, RN8209D_RData, reg_data, 4);
	printf("RN8209D RData     44H = %02X%02X%02X%02Xh\r\n", reg_data[3], reg_data[2], reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_WData, reg_data, 2);
	printf("RN8209D WData     45H = %02X%02Xh\r\n", reg_data[1], reg_data[0]);
	register_read(Dev, RN8209D_DeviceID, reg_data, 3);
	printf("RN8209D DeviceID  7FH = %02X%02X%02Xh\r\n", reg_data[2], reg_data[1], reg_data[0]);
	printf("---END---\r\n");
}*/

static int rn8209d_data_clear(struct device *Dev, enum sensor_type e_type)
{
	switch (e_type) {
		case SENSOR_RN8209D_CONSUMPTION:
			clear_consumption_data(Dev);
			break;
		default:
			return -1;
	}
	return 0;
}

static int rn8209d_value_get(struct device *Dev, enum sensor_type e_type, struct sensor_value *Data)
{
	struct rn8209d_data *D_data = Dev->data;
	
	switch (e_type) {
		case SENSOR_RN8209D_VOLTAGE:
			Data->value_integer = D_data->value_voltage_integer;
			Data->value_decimal = D_data->value_voltage_decimal;
			break;
		case SENSOR_RN8209D_CURRENT:
			Data->value_integer = D_data->value_current_integer;
			Data->value_decimal = D_data->value_current_decimal;
			break;
		case SENSOR_RN8209D_POWER:
			Data->value_integer = D_data->value_power_integer;
			Data->value_decimal = D_data->value_power_decimal;
			break;
		case SENSOR_RN8209D_CONSUMPTION:
			Data->value_integer = D_data->value_consumption_integer;
			Data->value_decimal = D_data->value_consumption_decimal;
			break;
		default:
			return -1;
	}
	return 0;
}

static int rn8209d_sample_fetch(struct device *Dev, enum sensor_type e_type)
{
	switch (e_type) {
		case SENSOR_RN8209D_VOLTAGE:
			fetch_voltage(Dev);
			break;
		case SENSOR_RN8209D_CURRENT:
			fetch_current(Dev);
			break;
		case SENSOR_RN8209D_POWER:
			fetch_power(Dev);
			break;
		case SENSOR_RN8209D_CONSUMPTION:
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
//	register_list(Dev);
	return 0;
}

static const struct sensor_common_api Rn8209d_api = {
	.sample_fetch = rn8209d_sample_fetch,
	.value_get    = rn8209d_value_get,
	.data_clear   = rn8209d_data_clear
};

static void calibration(struct device *Dev)
{
	const struct rn8209d_config *D_config = Dev->config;
	uint8_t reg_data[2];
	uint16_t *reg_value = (uint16_t *)reg_data;
	
	//00H
	register_read(Dev, RN8209D_SYSCON, reg_data, 2);
	REG_BIT_SET(*reg_value, ADC2ON_6, 0); //1
	REG_BIT_SET(*reg_value, PGAIB_5,  0); //1
	REG_BIT_SET(*reg_value, PGAIB_4,  0); //1
	REG_BIT_SET(*reg_value, PGAU_3,   0); //1
	REG_BIT_SET(*reg_value, PGAU_2,   0); //1
	REG_BIT_SET(*reg_value, PGAIA_1,  1); //1
	REG_BIT_SET(*reg_value, PGAIA_0,  1); //1
	register_write(Dev, RN8209D_SYSCON, reg_data, 2);
	
	//01H
	register_read(Dev, RN8209D_EMUCON, reg_data, 2);
	REG_BIT_SET(*reg_value, EnergyCLR_15, 0);
	REG_BIT_SET(*reg_value, HPFIBOFF_14,  0); //1
	REG_BIT_SET(*reg_value, QMOD_13,      0); //4
	REG_BIT_SET(*reg_value, QMOD_12,      0); //4
	REG_BIT_SET(*reg_value, PMOD_11,      0); //4
	REG_BIT_SET(*reg_value, PMOD_10,      0); //4
	REG_BIT_SET(*reg_value, ZXD1_9,       0);
	REG_BIT_SET(*reg_value, ZXD0_8,       0);
	REG_BIT_SET(*reg_value, ZXCFG_7,      0);
	REG_BIT_SET(*reg_value, HPFIAOFF_6,   0); //1
	REG_BIT_SET(*reg_value, HPFUOFF_5,    0); //1
	REG_BIT_SET(*reg_value, CFSUEN_4,     0); //4
	REG_BIT_SET(*reg_value, CFSU_3,       0); //4
	REG_BIT_SET(*reg_value, CFSU_2,       0); //4
	REG_BIT_SET(*reg_value, DRUN_1,       1); //4
	REG_BIT_SET(*reg_value, PRUN_0,       1); //4
	register_write(Dev, RN8209D_EMUCON, reg_data, 2);
	
	//17H
	register_read(Dev, RN8209D_EMUCON2, reg_data, 2);
	REG_BIT_SET(*reg_value, FreqCnt_13,  0);
	REG_BIT_SET(*reg_value, FreqCnt_12,  0);
	REG_BIT_SET(*reg_value, PhsB0_9,     0); //1
	REG_BIT_SET(*reg_value, PhsA0_8,     0); //1
	REG_BIT_SET(*reg_value, UPMODE_7,    0);
	REG_BIT_SET(*reg_value, ZXMODE_6,    0);
	REG_BIT_SET(*reg_value, D2FM_5,      0); //4
	REG_BIT_SET(*reg_value, D2FM_4,      0); //4
	REG_BIT_SET(*reg_value, Energy_fz_3, 0);
	register_write(Dev, RN8209D_EMUCON2, reg_data, 2);
	
	//40H
	register_read(Dev, RN8209D_IE, reg_data, 1);
	REG_BIT_SET(*reg_value, FZIE_6,   0);
	REG_BIT_SET(*reg_value, ZXIE_5,   0);
	REG_BIT_SET(*reg_value, QEOIE_4,  0);
	REG_BIT_SET(*reg_value, PEOIE_3,  0);
	REG_BIT_SET(*reg_value, QFIE_2,   0);
	REG_BIT_SET(*reg_value, PFIE_1,   0);
	REG_BIT_SET(*reg_value, DUPDIE_0, 0);
	register_write(Dev, RN8209D_IE, reg_data, 1);
	
	//02H
	register_read(Dev, RN8209D_HFConst, reg_data, 2);
	*reg_value = D_config->value_hfconst;
	register_write(Dev, RN8209D_HFConst, reg_data, 2);
	
	//03H
	register_read(Dev, RN8209D_PStart, reg_data, 2);
	*reg_value = D_config->value_pstart;
	register_write(Dev, RN8209D_PStart, reg_data, 2);
	
	//04H
	register_read(Dev, RN8209D_DStart, reg_data, 2);
	*reg_value = D_config->value_dstart;
	register_write(Dev, RN8209D_DStart, reg_data, 2);
	
	//05H
	register_read(Dev, RN8209D_GPQA, reg_data, 2);
	*reg_value = D_config->value_gpqa;
	register_write(Dev, RN8209D_GPQA, reg_data, 2);
	
	//07H
	register_read(Dev, RN8209D_PhsA, reg_data, 1);
	*reg_value = D_config->value_phsa;
	register_write(Dev, RN8209D_PhsA, reg_data, 1);
	
	//0AH
	register_read(Dev, RN8209D_APOSA, reg_data, 2);
	*reg_value = D_config->value_aposa;
	register_write(Dev, RN8209D_APOSA, reg_data, 2);
	
	//0EH
	register_read(Dev, RN8209D_IARMSOS, reg_data, 2);
	*reg_value = D_config->value_iarmsos;
	register_write(Dev, RN8209D_IARMSOS, reg_data, 2);
}

static struct rn8209d_data Rn8209d_data;

static const struct rn8209d_config Rn8209d_config = {
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
	Vu = Un*(1K/(1M+1K))*1
	   = 108*(1/1001)
	   = 0.10789V
	Vi = Ib*Rm*16
	   = 6.28*0.00035*16
	   = 0.035168V
	HFConst = INT[(16.1079*Vu*Vi*10^11)/(Un*Ib*EC)]
	        = 6111781065/2170368
	        = 2816(B00h)
	Kv = Un/URMS
	   = 108/959597
	   = 0.0001125
	Ki = Ib/IARMS
	   = 6.28/415124
	   = 0.00001512
	Kp = (3.22155*10^12)/(2^32*HFConst*EC)
	   = 3221550000000/38702809297715200
	   = 0.00008324
	**/
};

static int rn8209d_device_init(struct device *Dev)
{
	struct rn8209d_data *D_data = Dev->data;
	
	D_data->Spi = spi1_cs0_device_binding();
	spi_init(D_data->Spi);
	printf("RN8209D device init\r\n");
	
	software_reset(Dev);
	ib_chnsel(Dev);
	ia_chnsel(Dev);
	
//	register_list(Dev);
	calibration(Dev);
	
	return 0;
}

struct device Rn8209d = {
	.api    = &Rn8209d_api,
	.data   = &Rn8209d_data,
	.config = &Rn8209d_config,
	.init   = rn8209d_device_init,
};

struct device* rn8209d_device_binding(void)
{
	return &Rn8209d;
}
