#include "tsi.h"
#include "Uart.h"

#define TSI_CH_MAIN (uint8_t)9
#define TSI_CH_SECONDARY (uint8_t)10

void selectChannel(uint8_t channel);
uint16_t scan();


/*
void selectChannel(uint8_t channel){
		// Select channel i
		TSI0->DATA = TSI_DATA_TSICH(channel) | TSI_DATA_SWTS_MASK;
}
*/

uint16_t scan(){
	//NVIC_DisableIRQ();
	
	//selectChannel(TSI_CH_MAIN);
	
	uint16_t cnt = 0;
	
	// Reset out of range bit
	TSI0->GENCS |= TSI_GENCS_OUTRGF_MASK;
	
	// Start scan
	TSI0->DATA |= TSI_DATA_SWTS_MASK;
	
	/*
	
	// Wait until scan has ended
	while((TSI0->GENCS & TSI_GENCS_EOSF_MASK) == 0);
	cnt = (TSI0->DATA & TSI_DATA_TSICNT_MASK) >> TSI_DATA_TSICNT_SHIFT;
	
	*/
	
	
	return cnt;
}

void TSI_init(){
	// Enable TSI from SIM
	SIM->SCGC5 |= 	SIM_SCGC5_TSI_MASK	|	// Enable TSI
									SIM_SCGC5_PORTB_MASK; // Enable PortB
	
	// Config TSI
	TSI0->GENCS |= 	TSI_GENCS_TSIEN_MASK 	| // Enable TSI
									TSI_GENCS_STPE_MASK 	| // Enable TSI low power functioning ( just in case )
									TSI_GENCS_ESOR_MASK  	;	// End of scan interrupt ( not end of range )
	
	TSI0->GENCS |=	TSI_GENCS_TSIIEN_MASK ; // enable tsi interrupts to enable dma
	
	PORTB->PCR[16] = PORT_PCR_MUX(0);
	PORTB->PCR[17] = PORT_PCR_MUX(0);
	
	TSI0->GENCS &=	~TSI_GENCS_STM_MASK;		// Enable software interrupt mode
	
	NVIC_EnableIRQ(TSI0_IRQn);
	NVIC_SetPriority(TSI0_IRQn, 0);
	
	TSI0->DATA = TSI_DATA_TSICH(TSI_CH_MAIN) | TSI_DATA_SWTS_MASK;
}

/*
void TSI_update(){
	//TSI_Readings = scan();
	// if no scan is in progress, start one
	//if ( ( TSI0->GENCS & TSI_GENCS_SCNIP_MASK ) == 0 )
		scan();
}
*/

void TSI0_IRQHandler() {
	// if a scan has ended, read the tsicnt
	//while ( ( TSI0-> GENCS & TSI_GENCS_SCNIP_MASK ) != 0 );
	
	if ( TSI0->GENCS & TSI_GENCS_EOSF_MASK ) {
		TSI0->GENCS |= TSI_GENCS_EOSF_MASK;
		TSI_Readings = (TSI0->DATA & TSI_DATA_TSICNT_MASK) >> TSI_DATA_TSICNT_SHIFT;
		UART0_Transmit((uint8_t) TSI_Readings);
		TSI0->DATA = TSI_DATA_TSICH(TSI_CH_MAIN) | TSI_DATA_SWTS_MASK;
	}
}

