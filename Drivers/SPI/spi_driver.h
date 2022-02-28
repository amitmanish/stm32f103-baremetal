/*
 * i2c_driver.h
 *
 *  Created on: Sep 1, 2021
 *      Author: lucifer
 */

#ifndef __SPI_DRIVER__
#define __SPI_DRIVER__

#include "stm32f10x.h"
#include "stdint.h"


#define MPU_ADDRESS (0x68<<1)
#define MPU_ADDRESS_READ (0x68<<1|0x1)
#define WHO_AM_I_REG 0x75
#define PWR_1_REG 0x68



//Flash Configurations
#define PAGE_SIZE 0x100
#define PAGE_PROGRAM_CMD 0x02
#define WRITE_ADDRESS 0x80000000
#define READ_FLASH 0x03

//Data to be written to flash

extern uint8_t data[160];

void spi_init(void);

uint8_t spi_send_byte(uint8_t);

uint8_t spi_receive_byte(void);

void flash_write_page(uint8_t *buffer , uint32_t write_address , uint16_t data_length);

void flash_write_buffer(uint8_t *buffer , uint32_t write_address , uint16_t data_length);

void flash_read_buffer(uint8_t *buffer , uint32_t write_address , uint16_t data_length);

#endif
