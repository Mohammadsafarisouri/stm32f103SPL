#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "delay.h"
#include "led.h"






int main() {
	GPIO_InitTypeDef GPIO_USART_AtiBin;											// New Struct GPIO_InitTypeDef type
	USART_InitTypeDef USART_AtiBin;													// New Struct USART_InitTypeDef type
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);		//Active Clock of UART2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//Active Clock of GPIOA
	
	// Configuration UART2 Pins
	GPIO_USART_AtiBin.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_USART_AtiBin.GPIO_Pin = GPIO_Pin_2;
	GPIO_USART_AtiBin.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_USART_AtiBin);
	
	GPIO_USART_AtiBin.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_USART_AtiBin.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_USART_AtiBin);
	
	// Configuration UART2
	USART_AtiBin.USART_BaudRate = 19200;																			// Set BaudRate
	USART_AtiBin.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// Set USART_HardwareFlowControl  as USART_HardwareFlowControl_None
	USART_AtiBin.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;										// Active recive and transmit of UART2
	USART_AtiBin.USART_Parity = USART_Parity_No;															// Set Parity bit
	USART_AtiBin.USART_StopBits = USART_StopBits_1;														// Set Stop Bit
	USART_AtiBin.USART_WordLength = USART_WordLength_8b;											// Set data length
	USART_Init(USART2,&USART_AtiBin);																					// Initial USART_AtiBin struc
	
	
	USART_Cmd(USART2,ENABLE);																									// Enables USART
	
	delayInit();
	while(1) {
		USART_SendData(USART2,'M');
		delayMsecond(1000);
	}
}
