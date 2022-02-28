/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/




#include "stm32f10x.h"
#include "uart_driver.h"
#include <stdio.h>
#include "spi_driver.h"

uint8_t received_data[8];

int main(void)
{


	SystemCoreClockUpdate();

		uart_init();
		spi_init();


		flash_write_page(data , WRITE_ADDRESS , (uint8_t)sizeof(data));
		flash_read_buffer(data , WRITE_ADDRESS , (uint8_t)sizeof(received_data));

	}
