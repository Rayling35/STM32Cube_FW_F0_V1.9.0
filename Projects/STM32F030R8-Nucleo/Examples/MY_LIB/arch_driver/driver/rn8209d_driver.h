/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __RN8209D_DRIVER_H
#define __RN8209D_DRIVER_H


struct rn8209d_data {
	struct device *Spi;
	struct device *Gpio;
	
	uint32_t value_voltage_integer;
	uint32_t value_voltage_decimal;
	uint32_t value_current_integer;
	uint32_t value_current_decimal;
	uint32_t value_power_integer;
	uint32_t value_power_decimal;
	uint32_t value_consumption_integer;
	uint32_t value_consumption_decimal;
};

struct rn8209d_config {
	uint8_t value_enable_write;
	uint8_t value_disable_write;
	uint8_t value_ia_chnsel;
	uint8_t value_ib_chnsel;
	uint8_t value_soft_reset;
	
	uint32_t value_clkin;
	uint32_t value_kv;
	uint32_t value_kia;
	uint32_t value_kp;
	uint16_t value_hfconst;
	uint16_t value_pstart;
	uint16_t value_dstart;
	uint16_t value_gpqa;
	uint8_t  value_phsa;
	uint16_t value_aposa;
	uint16_t value_iarmsos;
};

//SPI_POLARITY_LOW,SPI_PHASE_2EDGE
#define RN8209D_R                 0x00
#define RN8209D_W                 0x80

#define RN8209D_SYSCON            0x00
#define RN8209D_EMUCON            0x01
#define RN8209D_HFConst           0x02
#define RN8209D_PStart            0x03
#define RN8209D_DStart            0x04
#define RN8209D_GPQA              0x05
#define RN8209D_GPQB              0x06
#define RN8209D_PhsA              0x07
#define RN8209D_PhsB              0x08
#define RN8209D_QPhsCal           0x09
#define RN8209D_APOSA             0x0A
#define RN8209D_APOSB             0x0B
#define RN8209D_RPOSA             0x0C
#define RN8209D_RPOSB             0x0D
#define RN8209D_IARMSOS           0x0E
#define RN8209D_IBRMSOS           0x0F
#define RN8209D_IBGain            0x10
#define RN8209D_D2FPL             0x11
#define RN8209D_D2FPH             0x12
#define RN8209D_DCIAH             0x13
#define RN8209D_DCIBH             0x14
#define RN8209D_DCUH              0x15
#define RN8209D_DCL               0x16
#define RN8209D_EMUCON2           0x17

#define RN8209D_PFCnt             0x20
#define RN8209D_DFCnt             0x21
#define RN8209D_IARMS             0x22
#define RN8209D_IBRMS             0x23
#define RN8209D_URMS              0x24
#define RN8209D_UFreq             0x25
#define RN8209D_PowerPA           0x26
#define RN8209D_PowerPB           0x27
#define RN8209D_PowerQ            0x28
#define RN8209D_EnergyP           0x29
#define RN8209D_ENergyP2          0x2A
#define RN8209D_EnergyD           0x2B
#define RN8209D_EnergyD2          0x2C
#define RN8209D_EMUStatus         0x2D
#define RN8209D_SPL_IA            0x30
#define RN8209D_SPL_IB            0x31
#define RN8209D_SPL_U             0x32
#define RN8209D_UFreq2            0x35

#define RN8209D_IE                0x40
#define RN8209D_IF                0x41
#define RN8209D_RIF               0x42

#define RN8209D_SysStatus         0x43
#define RN8209D_RData             0x44
#define RN8209D_WData             0x45
#define RN8209D_DeviceID          0x7F

#define RN8209D_SPECIAL           0xEA

enum REG_SYSCON_00H {
	PGAIA_0 = 0,
	PGAIA_1,
	PGAU_2,
	PGAU_3,
	PGAIB_4,
	PGAIB_5,
	ADC2ON_6,
	Uartbr_8 = 8,
	Uartbr_9,
	Uartbr_10,
	Uartbr_11,
	Uartbr_12,
	Uartbr_13,
	Uartbr_14,
};

enum REG_EMUCON_01H {
	PRUN_0 = 0,
	DRUN_1,
	CFSU_2,
	CFSU_3,
	CFSUEN_4,
	HPFUOFF_5,
	HPFIAOFF_6,
	ZXCFG_7,
	ZXD0_8,
	ZXD1_9,
	PMOD_10,
	PMOD_11,
	QMOD_12,
	QMOD_13,
	HPFIBOFF_14,
	EnergyCLR_15,
};

enum REG_EMUCON2_17H {
	Energy_fz_3 = 3,
	D2FM_4,
	D2FM_5,
	ZXMODE_6,
	UPMODE_7,
	PhsA0_8,
	PhsB0_9,
	FreqCnt_12 = 12,
	FreqCnt_13,
};

enum REG_IE_40H {
	DUPDIE_0 = 0,
	PFIE_1,
	QFIE_2,
	PEOIE_3,
	QEOIE_4,
	ZXIE_5,
	FZIE_6,
};

struct device* rn8209d_device_binding(void);


#endif
