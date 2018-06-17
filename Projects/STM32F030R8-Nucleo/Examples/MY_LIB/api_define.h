/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_DEFINE_H
#define __API_DEFINE_H


#ifdef HAL_GPIO_MODULE_ENABLED
struct gpio_api {
	void (*init)        (void);
	int  (*read)        (void);
	void (*write)       (uint16_t state);
	void (*toggle_write)(void);
	int  (*lock)        (void);
};
#endif

#ifdef HAL_UART_MODULE_ENABLED
struct uart_api {
	void (*init)       (void);
	int (*transmit)    (uint8_t *data, uint16_t length, uint32_t timeout);
	int (*receive)     (uint8_t *data, uint16_t length, uint32_t timeout);
	int (*transmit_it) (uint8_t *data, uint16_t length);
	int (*receive_it)  (uint8_t *data, uint16_t length);
	int (*transmit_dma)(uint8_t *data, uint16_t length);
	int (*receive_dma) (uint8_t *data, uint16_t length);

	int (*dma_pause)        (void);
	int (*dma_resume)       (void);
	int (*dma_stop)         (void);
	int (*abort)            (void);
	int (*abort_transmit)   (void);
	int (*abort_receive)    (void);
	int (*abort_it)         (void);
	int (*abort_transmit_it)(void);
	int (*abort_receive_it) (void);
};
#endif

#ifdef HAL_I2C_MODULE_ENABLED
struct i2c_api {
	void (*init)                        (void);
	int (*master_transmit)              (uint16_t addr, uint8_t *data, uint16_t length, uint32_t timeout);
	int (*master_receive)               (uint16_t addr, uint8_t *data, uint16_t length, uint32_t timeout);
	int (*master_transmit_it)           (uint16_t addr, uint8_t *data, uint16_t length);
	int (*master_receive_it)            (uint16_t addr, uint8_t *data, uint16_t length);
	int (*master_sequential_transmit_it)(uint16_t addr, uint8_t *data, uint16_t length, uint32_t options);
	int (*master_sequential_receive_it) (uint16_t addr, uint8_t *data, uint16_t length, uint32_t options);
	int (*master_transmit_dma)          (uint16_t addr, uint8_t *data, uint16_t length);
	int (*master_receive_dma)           (uint16_t addr, uint8_t *data, uint16_t length);

	int (*slave_transmit)              (uint8_t *data, uint16_t length, uint32_t timeout);
	int (*slave_receive)               (uint8_t *data, uint16_t length, uint32_t timeout);
	int (*slave_transmit_it)           (uint8_t *data, uint16_t length);
	int (*slave_receive_it)            (uint8_t *data, uint16_t length);
	int (*slave_sequential_transmit_it)(uint8_t *data, uint16_t length, uint32_t options);
	int (*slave_sequential_receive_it) (uint8_t *data, uint16_t length, uint32_t options);
	int (*slave_transmit_dma)          (uint8_t *data, uint16_t length);
	int (*slave_receive_dma)           (uint8_t *data, uint16_t length);

	int (*mem_write)      (uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length, uint32_t timeout);
	int (*mem_read)       (uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length, uint32_t timeout);
	int (*mem_write_it)   (uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length);
	int (*mem_read_it)    (uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length);
	int (*mem_write_dma)  (uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length);
	int (*mem_read_dma)   (uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length);

	int (*enable_listen_it) (void);
	int (*disable_listen_it)(void);
	int (*master_abort_it)(uint16_t addr);
	int (*is_device_ready)(uint16_t addr, uint32_t trials, uint32_t timeout);
};
#endif

#ifdef HAL_SPI_MODULE_ENABLED
struct spi_api {
	void (*init)               (void);
	int (*transmit)            (uint8_t *data, uint16_t length, uint32_t timeout);
	int (*receive)             (uint8_t *data, uint16_t length, uint32_t timeout);
	int (*receive32)           (uint32_t *data, uint16_t length, uint32_t timeout);
	int (*transmit_receive)    (uint8_t *tx_data, uint8_t *rx_data, uint16_t length, uint32_t timeout);

	int (*transmit_it)         (uint8_t *data, uint16_t length);
	int (*receive_it)          (uint8_t *data, uint16_t length);
	int (*transmit_receive_it) (uint8_t *tx_data, uint8_t *rx_data, uint16_t length);

	int (*transmit_dma)        (uint8_t *data, uint16_t length);
	int (*receive_dma)         (uint8_t *data, uint16_t length);
	int (*transmit_receive_dma)(uint8_t *tx_data, uint8_t *rx_data, uint16_t length);

	int (*abort)     (void);
	int (*abort_it)  (void);
	int (*dma_pause) (void);
	int (*dma_resume)(void);
	int (*dma_stop)  (void);
};
#endif


#endif
