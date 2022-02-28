/*
 * spi_driver.c
 *
 *  Created on: Sep 1, 2021
 *      Author: lucifer
 */
#include "spi_driver.h"
#include "uart_driver.h"


uint8_t data[160] = {0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,
				  0xAA , 0XBB , 0XCC , 0xEE , 0x11 , 0x22 , 0x33 , 0x44,};


void chipselect_low(void){
	//select the SPI slave PIN CS(PA4)
	GPIOA->BSRR |= (0x1<<20);
}

void chipselect_high(void){
	//deselect the SPI slave PIN CS(PA4)
	GPIOA->BSRR |= (0x1<<4);
}


void spi_init(void){

//Enable clock for SPI controller and MISO(PA6),MOSI(PA7), SCK(PA5) and CS(PA4) of SPI1
RCC->APB1ENR |= (uint32_t)(0x1<<12);                //ENABLING CLOCK FOR SPI1 CONTROLLER
RCC->APB2ENR |= (uint32_t)(0x1<<2 | 0x1<<0);             //ENABLING CLOCK FOR SPI1 PORTA PINS

//Configure SP MISO(PA6),MOSI(PA7), SCK(PA5) and CS(PA4) of SPI1
	GPIOA->CRL |= (uint32_t)(0x088880000);

chipselect_high();

//configure SPI1 controller
//step1:Disabled SPI1
SPI1->CR1 &= ~(0x1<<6);
//step2: set the baudrate clock
//SPI baudrate = SystemCoreClock/prescaler
SPI1->CR1 |= (0x2<<3);
//step3: set CPH and CPOL
SPI1->CR1 &= (0x2);
//step3: set frame size
SPI1->CR1 &= ~(0x1<<11);
//step4: set msb bit to send first
SPI1->CR1 &= ~(0x1<<7);
//step5: set SPI1 in master mode and enable Software slave mode
SPI1->CR1 |= (0x1<<9 | 0x1<<2);
//step6:Enable SPI1 controllers
SPI1->CR1 &= (0x1<<6);

}


uint8_t spi_send_byte(uint8_t data){
	while(!(SPI1->SR & 0x2));
	SPI1->DR = data;
	while(!(SPI1->SR & 0x1));
	return SPI1->DR;
}

uint8_t spi_receive_byte(void){
uint8_t dummy_data = 0xff;
return spi_send_byte(dummy_data);
}

uint32_t flash_read_id(void)
{
uint8_t temp =0 , temp0 = 0, temp1 =0 , temp2=0;
chipselect_low();
spi_send_byte(0x9F);
//receive first byte
temp0 = spi_receive_byte();
//receive second byte
temp1 = spi_receive_byte();
//receive third byte
temp2 = spi_receive_byte();
//deselect slave
chipselect_high();
//complete id
temp = (temp2<<16 | temp1<<8 | temp0);
return temp;
}

void flash_write_enable(void){
chipselect_low();
spi_send_byte(0x06);
chipselect_high();
}


void flash_write_disable(void){
chipselect_low();
spi_send_byte(0x04);
chipselect_high();
}


uint8_t flash_read_status_register1(void){
	chipselect_low();
	spi_send_byte(0x05);
	uint8_t status1 = spi_receive_byte();
	chipselect_high();
	return status1;
}

uint8_t flash_read_status_register2(void){
	chipselect_low();
	spi_send_byte(0x35);
	uint8_t status2 = spi_receive_byte();
	chipselect_high();
	return status2;
}

uint8_t flash_read_status_register3(void){
	chipselect_low();
	spi_send_byte(0x15);
	uint8_t status3 = spi_receive_byte();
	chipselect_high();
	return status3;
}


void flash_write_status_register1(void){
	chipselect_low();
	flash_write_enable();
	spi_send_byte(0x05);
	chipselect_high();
	return;
}

void flash_write_status_register2(void)
{
	chipselect_low();
	flash_write_enable();
	spi_send_byte(0x35);
	chipselect_high();
	return;
}

void flash_write_status_register3(void)
{
	chipselect_low();
	flash_write_enable();
	spi_send_byte(0x15);
	chipselect_high();
	return;
}

void flash_write_page(uint8_t *buffer , uint32_t write_address , uint16_t data_length)
{
//step1: send flash_write_enable command
	flash_write_enable();
//step2:send page program command
	spi_send_byte(PAGE_PROGRAM_CMD);
//step3: send address MSB Byte
	spi_send_byte((WRITE_ADDRESS&0x00FF0000)>>16);
//step4: send address Middle Byte
	spi_send_byte((WRITE_ADDRESS&0x0000FF00)>>8);
//step5: send address Lower Byte
	spi_send_byte(WRITE_ADDRESS&0x000000FF);
//step6:Send data from buffer
	while(data_length--)
	{
		spi_send_byte(*buffer);
		buffer++;
	}
//step7: Disable the slave flash
	chipselect_low();
}

void flash_write_buffer(uint8_t *buffer , uint32_t write_address , uint16_t data_length)
{

	uint32_t address = (write_address % PAGE_SIZE);
	uint8_t page_number = (data_length / PAGE_SIZE);

	if (address == 0)        //address to be written is algned to page length boundary
	{
		if (page_number == 0)        //data to be written is less than page size
		{
			flash_write_page(data , write_address , sizeof(data));
		}
		else               // data to be written is greater than page
		{
			while(page_number--)
			{
				flash_write_page(data , write_address , sizeof(data));
				write_address += PAGE_SIZE;
				buffer += PAGE_SIZE;
			}
		}
	}
	else                     //address to be written is not aligned on page boundary
	{

	}

}

void flash_read_buffer(uint8_t *buffer , uint32_t write_address , uint16_t data_length)
{
	//step1: select the slave flash
	    chipselect_low();
	//step2:send read command
		spi_send_byte(READ_FLASH);
	//step3: send address MSB Byte
		spi_send_byte((WRITE_ADDRESS&0x00FF0000)>>16);
	//step4: send address Middle Byte
		spi_send_byte((WRITE_ADDRESS&0x0000FF00)>>8);
	//step5: send address Lower Byte
		spi_send_byte(WRITE_ADDRESS&0x000000FF);
	//step6:Read data into buffer
		while(data_length--)
		{
			spi_receive_byte();
			buffer++;
		}
	//step7: Disable the slave flash
		chipselect_low();

}


