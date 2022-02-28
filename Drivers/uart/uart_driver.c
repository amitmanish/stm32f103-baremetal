#include "uart_driver.h"


void uart_init(){
// Enable clock for UART controller and TX/RX clocks
RCC->APB2ENR |= (uint32_t)0x00004004U;
//Configure TX/RX for AFIO
GPIOA->CRH |= (uint32_t)0x00000FF0U;


//Configure USART as TX and RX and Parity and Word length
USART1->CR1 |= (uint32_t)0x0000000CU;

//set baudarate
/*       BaudRate(Tx/Rx) = Fclk/(16 * UARTDIV)
 *       Fclk = 72MHz
 *       UARTDIV = Fclk/(16*BaudRate)
 *       UARTDIV = 72000000/(16*115200) = 72000000/1843200 = 39.0625
 *
 */

USART1->BRR = (uint32_t)(64000000/115200);

//Enable the UART1
USART1->CR1 |= (uint32_t)0x0002000;

}

void send_byte(uint8_t db){
	USART1->DR = (uint8_t)db;
			while(!(USART1->SR & (0x00000040)));
}

void send_data(uint8_t *dp){
while(*dp){
	send_byte(*dp);
	dp++;
}
}
