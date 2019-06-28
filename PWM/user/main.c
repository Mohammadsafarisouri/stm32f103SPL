#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "delay.h"
#include "led.h"
#include <stdio.h>
char data[20] = "Ali Safari Souri\n";


void InitialTIMER2(void);
void InitialUART2(void);
void sendStringUART2(char * data);

void TIM2_IRQHandler(void) {
	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update)){
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
		sendStringUART2(data);
		LED0 = !LED0;
		LED1 =	!LED1;
	}
}

int main() {
	LEDInit();
	
	InitialUART2();
	InitialTIMER2();
	while(1) {
	}
}




void sendStringUART2(char * data) {
	
	while(*data != '\0') {
		USART2->DR = *data;
		while(((USART2->SR)&(USART_SR_TC))==0);
		data++;
	}
}


void InitialUART2(void) {
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
}




void InitialTIMER2(void) {
	TIM_TimeBaseInitTypeDef TIM_Init_Struct;																	// New Struct TIM_TimeBaseInitTypeDef type
	TIM_OCInitTypeDef TIM_Init_Channel;																				// New Struct TIM_OCInitTypeDef  type
	GPIO_InitTypeDef GPIO_Init_TIM;
	NVIC_InitTypeDef NVIC_Init_TIM2;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);											// Active Clock of GPIOA
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);												// Active Clock of Timer2
	
	// Configuration GPIOA Pin0 and Pin1 for PWM
	GPIO_Init_TIM.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init_TIM.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init_TIM.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_TIM);
	
	// Configuration base struct of Timer2
	TIM_Init_Struct.TIM_ClockDivision = TIM_CKD_DIV1;				// Set Clock division to 1
	TIM_Init_Struct.TIM_CounterMode = TIM_CounterMode_Up;		// Set as Up Counter
	TIM_Init_Struct.TIM_Period = 4000;											// Set Period of Timer
	TIM_Init_Struct.TIM_Prescaler = 36000-1;								// Set Prescaler
	
	TIM_TimeBaseInit(TIM2,&TIM_Init_Struct);								// Initail TIM_Init_Struct
	TIM_ARRPreloadConfig(TIM2,ENABLE);											// Enable Auto Preload register
	
	NVIC_Init_TIM2.NVIC_IRQChannel = TIM2_IRQn;							// Active Interrupt for Timer2 in NVIC
	NVIC_Init_TIM2.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_Init_TIM2);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);								// Active Interrupt bit in Timer2
	
	// Configuration Output of Timer2
	TIM_Init_Channel.TIM_OCMode = TIM_OCMode_PWM2;					// Select mode in PWM2
  TIM_Init_Channel.TIM_OutputState = TIM_OutputState_Enable;// Enable output of Timer2
  TIM_Init_Channel.TIM_Pulse = 3000;												// Set Puls width of Timer2(Dutycycle)
  TIM_Init_Channel.TIM_OCPolarity = TIM_OCPolarity_Low;			// Set Polarity of PWM
  TIM_Init_Channel.TIM_OCIdleState = TIM_OCIdleState_Reset;	// Set state of output Pin during Idle state
	TIM_OC1Init(TIM2,&TIM_Init_Channel);											// Initial Output Channel1
	TIM_OC2Init(TIM2,&TIM_Init_Channel);											// Initial Output Channel1
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);					// Enable Preload register on CCR1
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);					// Enable Preload register on CCR2
	
	
	TIM_Cmd(TIM2,ENABLE);																			// Enable Timer2

}


