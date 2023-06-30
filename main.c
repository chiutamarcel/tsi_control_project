//#include "MKL25Z4.h"
#include "Uart.h"
#include "Touch_Sen.h"

#define sampling_number 100
#define BAUD_RATE (uint32_t)115200

int main(){
	uint32_t sum = 0;
	uint16_t avg = 0;
	int count = 0;
	
	initUART0(BAUD_RATE);
	Touch_Init();
	uint32_t i;
	
	while(1) {
		if (count >= sampling_number) {
			avg = (uint16_t)(sum / sampling_number);
			UART0_Transmit(avg);
			UART0_Transmit(avg >> 8);
			sum = 0;
			count = 0;
		}
		
		sum += (uint32_t)Touch_Scan_LH();
		count++;
		

		for ( i = 0 ; i < 2900; i++); // Delay
	}
	
	return 0;
}