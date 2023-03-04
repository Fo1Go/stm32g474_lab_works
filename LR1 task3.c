#include "stm32g474xx.h"
#define true 1
#define false 0

// if my number is 10, i = 9, button = 3 pb14, button 1 pb12


int main(void) {

	int numberdiod = 0;
	int button_pressed_1 = 0;
	int button_pressed_2 = 0;

	RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOEEN | RCC_AHB2ENR_GPIOBEN;

	GPIOE -> MODER &= ~GPIO_MODER_MODE7_Msk;
	GPIOE -> MODER |= 1 << GPIO_MODER_MODE7_Pos;
	GPIOE -> MODER &= ~GPIO_MODER_MODE8_Msk;
	GPIOE -> MODER |= 1 << GPIO_MODER_MODE8_Pos;
	GPIOE -> MODER &= ~GPIO_MODER_MODE9_Msk;
	GPIOE -> MODER |= 1 << GPIO_MODER_MODE9_Pos;
	GPIOE -> MODER &= ~GPIO_MODER_MODE10_Msk;
	GPIOE -> MODER |= 1 << GPIO_MODER_MODE10_Pos;


	GPIOB->MODER &= ~GPIO_MODER_MODE14_Msk;
	GPIOB->MODER |= 0 << GPIO_MODER_MODE14_Pos;

	GPIOB->MODER &= ~GPIO_MODER_MODE12_Msk;
	GPIOB->MODER |= 0 << GPIO_MODER_MODE12_Pos;


	while(1) {
		if((GPIOB->IDR & GPIO_IDR_ID14) == 0 && button_pressed_1 == 0) {
			button_pressed_1 = 1;
			if(numberdiod < 4)
				numberdiod++;
		}
		else if (GPIOB->IDR & GPIO_IDR_ID14) {
			button_pressed_1 = 0;
		}

		if((GPIOB->IDR & GPIO_IDR_ID12) == 0 && button_pressed_2 == 0) {
			button_pressed_2 = 1;
			numberdiod = 0;
			if(GPIO_ODR_OD7)
				GPIOE -> ODR &= GPIO_ODR_OD7;
			if(GPIO_ODR_OD8)
				GPIOE -> ODR &= GPIO_ODR_OD8;
			if(GPIO_ODR_OD9)
				GPIOE -> ODR &= GPIO_ODR_OD9;
			if(GPIO_ODR_OD10)
				GPIOE -> ODR &= GPIO_ODR_OD10;
		}
		else if (GPIOB->IDR & GPIO_IDR_ID12) {
			button_pressed_2 = 0;
		}


		if(numberdiod >= 1){
			GPIOE -> ODR ^= GPIO_ODR_OD7;
		}
		if(numberdiod >= 2){
			GPIOE -> ODR ^= GPIO_ODR_OD8;
		}
		if(numberdiod >= 3){
			GPIOE -> ODR ^= GPIO_ODR_OD9;
		}
		if(numberdiod >= 4){
			GPIOE -> ODR ^= GPIO_ODR_OD10;
		}
	}
}
