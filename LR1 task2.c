#include "stm32g474xx.h"


void delay(uint32_t time_delay) {
    uint32_t i;
    for(i = 0; i < time_delay; i++);
}

int main(void) {
	uint32_t button_is_pressed = 0;

	RCC -> AHB2ENR |= RCC_AHB2ENR_GPIODEN | RCC_AHB2ENR_GPIOEEN | RCC_AHB2ENR_GPIOBEN;

	GPIOD -> MODER &= ~GPIO_MODER_MODE11_Msk;
	GPIOD -> MODER |= 1 << GPIO_MODER_MODE11_Pos;

	GPIOE -> MODER &= ~GPIO_MODER_MODE11_Msk;
	GPIOE -> MODER |= 1 << GPIO_MODER_MODE11_Pos;


	GPIOB->MODER &= ~GPIO_MODER_MODE13_Msk;
	GPIOB->MODER |= 0 << GPIO_MODER_MODE13_Pos;

	GPIOB->MODER &= ~GPIO_MODER_MODE15_Msk;
	GPIOB->MODER |= 0 << GPIO_MODER_MODE15_Pos;


	while(1) {
		delay(10000);
		if((GPIOB->IDR & GPIO_IDR_ID15) == 0) {
			GPIOD->ODR |= GPIO_ODR_OD11;
		}
		else {
			GPIOD->ODR &= ~GPIO_ODR_OD11;
		}

		if((GPIOB->IDR & GPIO_IDR_ID13) == 0) {
			GPIOE->ODR |= GPIO_ODR_OD11;
		}
		else {
			GPIOE->ODR &= ~GPIO_ODR_OD11;
		}
	}
}

