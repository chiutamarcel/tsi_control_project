#include "MKL25Z4.h"

#include "Uart.h"
#include "tsi.h"

#define BAUD_RATE (uint32_t)115200

uint8_t UART_output = 0;
uint16_t TSI_Readings = 0;
//uint8_t status = 0;

int main(){
	TSI_init();
	initUART0(BAUD_RATE);
	
	while(1) {
		//status = 0;
		TSI_update();
		UART_output = TSI_Readings;
	}
	
	return 0;
}