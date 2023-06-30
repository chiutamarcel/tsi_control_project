#include "MKL25Z4.h"

#include "Uart.h"
#include "tsi.h"

#define BAUD_RATE (uint32_t)115200

uint16_t TSI_Readings = 0;

int main(){
	initUART0(BAUD_RATE);
	TSI_init();

	while(1) {
		
	}
	
	return 0;
}