#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

void GPIOA_Configure(){
	RCC -> APB2ENR |= 0x00000004;
	GPIOA -> CRL &= 0xFF0FFFFF;
	GPIOA -> CRL |= 0x00300000;
}
void delay_ms(uint16_t time){
	int i,j;
	for(i=0; i<time; i++){
		for(j=0; j<0x2AFF; j++);
	}
}
int main()
{
	GPIOA_Configure();
	while(1){
		GPIOA -> ODR |= 0x0020;
		delay_ms(1000);
		GPIOA -> ODR &=~ (0x0020);
		delay_ms(1000);
	}
}