#include "tsi.h"

#define TSI_CH_MAIN (uint8_t)9
#define TSI_CH_SECONDARY (uint8_t)10

void selectChannel(uint8_t channel);
uint16_t scan();


void selectChannel(uint8_t channel){
		// Reset TSICH
		TSI0->DATA &= ~TSI_DATA_TSICH_MASK;
	
		// Select channel i
		TSI0->DATA |= ( TSI_DATA_TSICH_MASK & ( channel << TSI_DATA_TSICH_SHIFT ) );
}

uint16_t scan(){
	//NVIC_DisableIRQ();
	
	selectChannel(TSI_CH_MAIN);
	
	uint16_t cnt;
	
	// Reset out of range bit
	TSI0->GENCS &= ~TSI_GENCS_OUTRGF_MASK;
	
	// Start scan
	TSI0->DATA |= TSI_DATA_SWTS_MASK;
	
	// Wait until scan has ended
	while((TSI0->GENCS & TSI_GENCS_EOSF_MASK) == 0);
	
	cnt = (TSI0->DATA & TSI_DATA_TSICNT_MASK) >> TSI_DATA_TSICNT_SHIFT;
	
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
	
	TSI0->GENCS &=	~TSI_GENCS_STM_MASK;		// Enable software interrupt mode
}

void TSI_update(){
	TSI_Readings = scan();
}

