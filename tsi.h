#ifndef TSI_MANAGER_H
#define TSI_MANAGER_H


#include "MKL25Z4.h"

static volatile uint16_t TSI_Readings = 0;

void TSI_init();
void TSI_update();

#endif
