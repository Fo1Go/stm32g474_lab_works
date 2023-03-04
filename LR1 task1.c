#include "stm32g474xx.h"

void delay(uint32_t time_delay) {
    for(uint32_t i = 0; i < time_delay; i++);
}

int main(void) {
	RCC -> AHB2ENR |= RCC_AHB2ENR_GPIODEN | RCC_AHB2ENR_GPIOEEN;

	GPIOD -> MODER &= ~GPIO_MODER_MODE2_Msk;
	GPIOD -> MODER |= 1 << GPIO_MODER_MODE2_Pos;

	GPIOE -> MODER &= ~GPIO_MODER_MODE0_Msk;
	GPIOE -> MODER |= 1 << GPIO_MODER_MODE0_Pos;

   while(1) {
   	GPIOD -> ODR ^= GPIO_ODR_OD2;
   	delay(350000);
   	GPIOE -> ODR ^= GPIO_ODR_OD0;
   }
}


