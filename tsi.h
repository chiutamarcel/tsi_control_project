#ifndef TSI_MANAGER_H
#define TSI_MANAGER_H


#include "MKL25Z4.h"

extern uint16_t TSI_Readings;
//extern uint8_t status;

void TSI_init();
void TSI_update();

#endif
