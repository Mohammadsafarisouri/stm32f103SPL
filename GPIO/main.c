#include "stm32f10x.h"                  // Device header


int main(void) {
	uint32_t i = 0;
	GPIO_InitTypeDef GPIO_Init_Struct_1;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);		// Set Port C Clock
	GPIO_Init_Struct_1.GPIO_Mode = GPIO_Mode_Out_PP;				// Set as Output Push-Pull
	GPIO_Init_Struct_1.GPIO_Pin = GPIO_Pin_13;							// Select data Pins
	GPIO_Init_Struct_1.GPIO_Speed = GPIO_Speed_50MHz;				// Select Pin speed
	
	GPIO_Init(GPIOC,&GPIO_Init_Struct_1);										// Configuratin Port C
	

	while(1) {
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		for(i = 0;i<7200000;i++);
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		for(i = 0;i<7200000;i++);
		
	}
}

