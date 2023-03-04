#include "stm32g474xx.h"


int main(void) {

	int button_pressed_1 = 0;
	int button_pressed_2 = 0;
	int button_pressed_3 = 0;
	int button_pressed_4 = 0;

	RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOEEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIODEN;

	GPIOE -> MODER &= ~GPIO_MODER_MODE7_Msk; GPIOE -> MODER |= 1 << GPIO_MODER_MODE7_Pos;
	GPIOE -> MODER &= ~GPIO_MODER_MODE15_Msk; GPIOE -> MODER |= 1 << GPIO_MODER_MODE15_Pos;
	GPIOD -> MODER &= ~GPIO_MODER_MODE8_Msk; GPIOD -> MODER |= 1 << GPIO_MODER_MODE8_Pos;
	GPIOD -> MODER &= ~GPIO_MODER_MODE0_Msk; GPIOD -> MODER |= 1 << GPIO_MODER_MODE0_Pos;

	GPIOB->MODER &= ~GPIO_MODER_MODE12_Msk; GPIOB->MODER |= 0 << GPIO_MODER_MODE12_Pos;
	GPIOB->MODER &= ~GPIO_MODER_MODE13_Msk; GPIOB->MODER |= 0 << GPIO_MODER_MODE13_Pos;
	GPIOB->MODER &= ~GPIO_MODER_MODE14_Msk; GPIOB->MODER |= 0 << GPIO_MODER_MODE14_Pos;
	GPIOB->MODER &= ~GPIO_MODER_MODE15_Msk; GPIOB->MODER |= 0 << GPIO_MODER_MODE15_Pos;

	while(1) {
		if((GPIOB->IDR & GPIO_IDR_ID12) == 0 && button_pressed_1 == 0) {
			GPIOE -> ODR |= GPIO_ODR_OD7;
			button_pressed_1 = 1;
		} else if (GPIOB->IDR & GPIO_IDR_ID12) {
			GPIOE -> ODR &= ~GPIO_ODR_OD7;
			button_pressed_1 = 0;
		}

		if((GPIOB->IDR & GPIO_IDR_ID13) == 0 && button_pressed_2 == 0) {
			GPIOE -> ODR |= GPIO_ODR_OD15;
			button_pressed_2 = 1;
		} else if (GPIOB->IDR & GPIO_IDR_ID13) {
			GPIOE -> ODR &= ~GPIO_ODR_OD15;
			button_pressed_2 = 0;
		}

		if((GPIOB->IDR & GPIO_IDR_ID14) == 0 && button_pressed_3 == 0) {
			GPIOD -> ODR |= GPIO_ODR_OD8;
			button_pressed_3 = 1;
		} else if (GPIOB->IDR & GPIO_IDR_ID14) {
			GPIOD -> ODR &= ~GPIO_ODR_OD8;
			button_pressed_3 = 0;
		}

		if((GPIOB->IDR & GPIO_IDR_ID15) == 0 && button_pressed_4 == 0) {
			GPIOD -> ODR |= GPIO_ODR_OD0;
			button_pressed_4 = 1;
		} else if (GPIOB->IDR & GPIO_IDR_ID15) {
			GPIOD -> ODR &= ~GPIO_ODR_OD0;
			button_pressed_4 = 0;
		}

	}
}
