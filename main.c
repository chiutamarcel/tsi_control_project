#include "MKL25Z4.h"

#include "Uart.h"
#include "tsi.h"

#define BAUD_RATE (uint32_t)115200

int main(){
	//TSI_init();
	initUART0(BAUD_RATE);
	
	while(1) {
		//TSI_update();
	}
	
	return 0;
}