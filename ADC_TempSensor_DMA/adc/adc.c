
#include "adc.h"



 

uint16_t ADC_ConvertedValue[3];

 void ADC1GPIOConfig(void){
	GPIO_InitTypeDef GPIO_InitStructure;    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
  GPIO_Init(GPIOB, &GPIO_InitStructure);   
}


void DMA1ModeConfig(void) {
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	/* DMA channel1 configuration */
	DMA_DeInit(DMA1_Channel1);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr =  (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) &ADC_ConvertedValue;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	
	DMA_InitStructure.DMA_BufferSize = 3;
	
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	DMA_Cmd(DMA1_Channel1, ENABLE);
}


 void ADC1ModeConfig(void) {

  ADC_InitTypeDef ADC_InitStructure;	


  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
     
  /* ADC1 configuration */
 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
 
	ADC_InitStructure.ADC_ScanConvMode = ENABLE; 
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel =3;
  ADC_Init(ADC1, &ADC_InitStructure);

 //configure each channel
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_41Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 2, ADC_SampleTime_41Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 3, ADC_SampleTime_41Cycles5);
		
  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  

	ADC_TempSensorVrefintCmd(ENABLE);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
  
  ADC_ResetCalibration(ADC1);
  while(ADC_GetResetCalibrationStatus(ADC1));


  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1));
	
	
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}





void ADC1Init(void)
{
	ADC1GPIOConfig();
	DMA1ModeConfig();
	ADC1ModeConfig();

}




