#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"
	 
void delayInit(void);
void delayMsecond(u16 nms);
void delayUsecond(u32 nus);

#endif
