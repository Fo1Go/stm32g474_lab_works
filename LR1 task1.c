#include "stm32g474xx.h"

// if my number is 10, i = 9, then pe(i + 7) = pe(16) = pe(0) and pd(i - 7) = pd(2)

void delay(uint32_t);


int main(void) {
	RCC -> AHB2ENR |= RCC_AHB2ENR_GPIODEN | RCC_AHB2ENR_GPIOEEN;

	GPIOD -> MODER &= ~GPIO_MODER_MODE2_Msk;
	GPIOD -> MODER |= 1 << GPIO_MODER_MODE2_Pos;

	GPIOE -> MODER &= ~GPIO_MODER_MODE0_Msk;
	GPIOE -> MODER |= 1 << GPIO_MODER_MODE0_Pos;

   while(1) {
   	// port E, light 2
   	GPIOD -> ODR ^= GPIO_ODR_OD2;
   	delay(350000);
   	// port E, light 0
   	GPIOE -> ODR ^= GPIO_ODR_OD0;
   }
}


void delay(uint32_t time_delay) {
    for(uint32_t i = 0; i < time_delay; i++);
}
