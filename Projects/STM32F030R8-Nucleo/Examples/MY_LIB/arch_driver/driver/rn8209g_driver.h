/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __RN8209G_DRIVER_H
#define __RN8209G_DRIVER_H


struct rn8209g_data {
	struct device *Spi;
	struct device *Gpio;
	
	uint8_t value_rn8209g_rx[3];
};

//SPI_POLARITY_LOW,SPI_PHASE_2EDGE
#define RN8209G_R                 0x00
#define RN8209G_W                 0x80

#define RN8209G_SYSCON            0x00
#define RN8209G_EMUCON            0x01
#define RN8209G_HFConst           0x02
#define RN8209G_PStart            0x03
#define RN8209G_DStart            0x04
#define RN8209G_GPQA              0x05
#define RN8209G_GPQB              0x06
#define RN8209G_PhsA              0x07
#define RN8209G_PhsB              0x08
//#define RN8209G_reserve           0x09
#define RN8209G_APOSA             0x0A
#define RN8209G_APOSB             0x0B
//#define RN8209G_reserve           0x0C
//#define RN8209G_reserve           0x0D
#define RN8209G_IARMSOS           0x0E
#define RN8209G_IBRMSOS           0x0F
#define RN8209G_IBGain            0x10
#define RN8209G_D2FPL             0x11
#define RN8209G_D2FPH             0x12
#define RN8209G_DCIAH             0x13
#define RN8209G_DCIBH             0x14
#define RN8209G_DCUH              0x15
#define RN8209G_DCL               0x16
#define RN8209G_EMUCON2           0x17

#define RN8209G_PFCnt             0x20
#define RN8209G_DFCnt             0x21
#define RN8209G_IARMS             0x22
#define RN8209G_IBRMS             0x23
#define RN8209G_URMS              0x24
#define RN8209G_UFreq             0x25
#define RN8209G_PowerPA           0x26
#define RN8209G_PowerPB           0x27
//#define RN8209G_reserve           0x28
#define RN8209G_EnergyP           0x29
#define RN8209G_ENergyP2          0x2A
#define RN8209G_EnergyD           0x2B
#define RN8209G_EnergyD2          0x2C
#define RN8209G_EMUStatus         0x2D
#define RN8209G_SPL_IA            0x30
#define RN8209G_SPL_IB            0x31
#define RN8209G_SPL_U             0x32

#define RN8209G_IE                0x40
#define RN8209G_IF                0x41
#define RN8209G_RIF               0x42

#define RN8209G_SysStatus         0x43
#define RN8209G_RData             0x44
#define RN8209G_WData             0x45
#define RN8209G_DeviceID          0x7F

#define RN8209G_SPECIAL           0xEA

struct device* rn8209g_device_binding(void);


#endif
