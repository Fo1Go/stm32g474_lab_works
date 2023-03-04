#include "stm32g474xx.h"


int main(void) {
	int number = 0, num, x, index, prev;
	int binary[4] = {0,0,0,0};
	int button_pressed_1 = 0;
	int button_pressed_2 = 0;
	int button_pressed_3 = 0;

	RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOEEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIODEN;

	GPIOE -> MODER &= ~GPIO_MODER_MODE7_Msk; GPIOE -> MODER |= 1 << GPIO_MODER_MODE7_Pos;
	GPIOE -> MODER &= ~GPIO_MODER_MODE15_Msk; GPIOE -> MODER |= 1 << GPIO_MODER_MODE15_Pos;
	GPIOD -> MODER &= ~GPIO_MODER_MODE8_Msk; GPIOD -> MODER |= 1 << GPIO_MODER_MODE8_Pos;
	GPIOD -> MODER &= ~GPIO_MODER_MODE0_Msk; GPIOD -> MODER |= 1 << GPIO_MODER_MODE0_Pos;

	GPIOB->MODER &= ~GPIO_MODER_MODE12_Msk; GPIOB->MODER |= 0 << GPIO_MODER_MODE12_Pos;
	GPIOB->MODER &= ~GPIO_MODER_MODE13_Msk; GPIOB->MODER |= 0 << GPIO_MODER_MODE13_Pos;
	GPIOB->MODER &= ~GPIO_MODER_MODE14_Msk; GPIOB->MODER |= 0 << GPIO_MODER_MODE14_Pos;

	while(1) {
		if((GPIOB->IDR & GPIO_IDR_ID12) == 0 && button_pressed_1 == 0) {
			if(number <= 14) {
				number++;
			}
			button_pressed_1 = 1;
		} else if (GPIOB->IDR & GPIO_IDR_ID12) {
			button_pressed_1 = 0;
		}
		if((GPIOB->IDR & GPIO_IDR_ID13) == 0 && button_pressed_2 == 0) {
			if(number >= 1) {
				number--;
			}
			button_pressed_2 = 1;
		} else if (GPIOB->IDR & GPIO_IDR_ID13) {
			button_pressed_2 = 0;
		}
		if((GPIOB->IDR & GPIO_IDR_ID14) == 0 && button_pressed_3 == 0) {
			number = 0;
			button_pressed_3 = 1;
		} else if (GPIOB->IDR & GPIO_IDR_ID14) {
			button_pressed_3 = 0;
		}

		if(number != prev) {
			x = number;
			index = 0;
			num = 0;
			for(int i = 0; i < 4; i++) binary[i] = 0;

			while(x != 0) {
				num = x % 2;
				x = x / 2;
				binary[index] = num;
				index++;
			}
			prev = number;
		}

		if(binary[3] == 1) {
			GPIOE -> ODR |= GPIO_ODR_OD7;
		} else if (binary[3] == 0) {
			GPIOE -> ODR &= ~GPIO_ODR_OD7;
		}
		if(binary[2] == 1) {
			GPIOE -> ODR |= GPIO_ODR_OD15;
		} else if (binary[2] == 0) {
			GPIOE -> ODR &= ~GPIO_ODR_OD15;
		}
		if(binary[1] == 1) {
			GPIOD -> ODR |= GPIO_ODR_OD8;
		} else if (binary[1] == 0) {
			GPIOD -> ODR &= ~GPIO_ODR_OD8;
		}
		if(binary[0] == 1) {
			GPIOD -> ODR |= GPIO_ODR_OD0;
		} else if (binary[0] == 0) {
			GPIOD -> ODR &= ~GPIO_ODR_OD0;
		}
	}
}
