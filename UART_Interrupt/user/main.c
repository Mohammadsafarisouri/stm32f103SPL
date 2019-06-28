#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "delay.h"
#include "led.h"
#include <stdio.h>


void USART2_IRQHandler(void)
{
	char char_in;
	if(USART_GetFlagStatus(USART2,USART_FLAG_RXNE)==1)
	{
		char_in = USART_ReceiveData(USART2);
		USART_ClearFlag(USART2,USART_FLAG_RXNE);
		USART_SendData(USART2,char_in);
		
	}
		
}


int main() {
	GPIO_InitTypeDef GPIO_USART_AtiBin;
	USART_InitTypeDef USART_AtiBin;
	NVIC_InitTypeDef NVIC_AtiBin;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//Active Clock of UART2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//Active Clock of GPIOA
	
	
	GPIO_USART_AtiBin.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_USART_AtiBin.GPIO_Pin = GPIO_Pin_2;
	GPIO_USART_AtiBin.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_USART_AtiBin);
	
	GPIO_USART_AtiBin.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_USART_AtiBin.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_USART_AtiBin);
	
	USART_AtiBin.USART_BaudRate = 19200;																			// Set BaudRate
	USART_AtiBin.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// Set USART_HardwareFlowControl  as USART_HardwareFlowControl_None
	USART_AtiBin.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;										// Active recive and transmit of UART2
	USART_AtiBin.USART_Parity = USART_Parity_No;															// Set Parity bit
	USART_AtiBin.USART_StopBits = USART_StopBits_1;														// Set Stop Bit
	USART_AtiBin.USART_WordLength = USART_WordLength_8b;											// Set data length
	USART_Init(USART2,&USART_AtiBin);																					// Initial USART_AtiBin struc
	
	
	
	NVIC_AtiBin.NVIC_IRQChannel = USART2_IRQn;
	NVIC_AtiBin.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_AtiBin);
	
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);															// Enable Inerrupt Bit for UART2 for recive and transmit
	USART_Cmd(USART2,ENABLE);																									// Enable UART@
	
	delayInit();
	while(1){
		
	}
}
