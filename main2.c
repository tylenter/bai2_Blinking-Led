#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void GPIOA_Configure(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void delay_ms(uint16_t time){
    int i,j;
    for(i=0; i<time; i++){
        for(j=0; j<0x2AFF; j++);
    }
}

int main(){
    GPIOA_Configure();
    uint8_t led_state = 0;

    while(1){
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0){
            delay_ms(20);
            if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0){
                led_state = !led_state;
                if(led_state){
                    GPIO_SetBits(GPIOA, GPIO_Pin_5);
                }else{
                    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
                }
                while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0);
            }
        }
    }
}