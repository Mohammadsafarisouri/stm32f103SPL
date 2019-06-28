#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "led.h"
#include "delay.h"

char DATA[17] = "Mohammad Safari\n";


int main() {
	GPIO_InitTypeDef GPIO_AtiBin;
	USART_InitTypeDef USART_AtiBin;
	DMA_InitTypeDef DMA_AtiBin;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	
	
	// Configuration UART2 Pins
	GPIO_AtiBin.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_AtiBin.GPIO_Pin = GPIO_Pin_2;
	GPIO_AtiBin.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_AtiBin);
	
	GPIO_AtiBin.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_AtiBin.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_AtiBin);
	
	
	// Configuration UART2
	USART_AtiBin.USART_BaudRate = 9600;																				// Set BaudRate
	USART_AtiBin.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// Set USART_HardwareFlowControl  as USART_HardwareFlowControl_None
	USART_AtiBin.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;										// Active recive and transmit of UART2
	USART_AtiBin.USART_Parity = USART_Parity_No;															// Set Parity bit
	USART_AtiBin.USART_StopBits = USART_StopBits_1;														// Set Stop Bit
	USART_AtiBin.USART_WordLength = USART_WordLength_8b;											// Set data length
	
	USART_Init(USART2,&USART_AtiBin);																					// Initial USART_AtiBin struc
	
	// Configuration DMA	
	DMA_AtiBin.DMA_PeripheralBaseAddr = (uint32_t) &USART2->DR ;							// Source address for DMA
	DMA_AtiBin.DMA_MemoryBaseAddr = (uint32_t)DATA;  													// Destination address for DMA
	DMA_AtiBin.DMA_DIR = DMA_DIR_PeripheralDST; 															// Direction of Transfer
	DMA_AtiBin.DMA_BufferSize = 16;  																					// Number of Data for Transfer
	DMA_AtiBin.DMA_PeripheralInc = DMA_PeripheralInc_Disable;									// Disable Peripheral increment address
	DMA_AtiBin.DMA_MemoryInc = DMA_MemoryInc_Enable;													// Enable Memory increment address
	DMA_AtiBin.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;					// Data size of source
	DMA_AtiBin.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;									// Data size of destination
	DMA_AtiBin.DMA_Mode = DMA_Mode_Normal; 																		// Teansfer mode(Normal)
	DMA_AtiBin.DMA_Priority = DMA_Priority_Medium;														// Priority of transfer in DMA
	DMA_AtiBin.DMA_M2M = DMA_M2M_Disable;																			// Memory to Memory disable
	
	DMA_Init(DMA1_Channel7, &DMA_AtiBin);																			// Initial DMA1 Channel7 (Transer UART2) 
	
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);															// Enable DMA request bit for UART2
	DMA_Cmd(DMA1_Channel7,ENABLE);																						// Enable DMA1 Channel7 
	USART_Cmd(USART2,ENABLE);																									// Enables USART
	
	delayInit();
	
	while(1) {
		USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
		delayMsecond(4000);
	}
}
