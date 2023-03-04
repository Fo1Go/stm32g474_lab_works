#include "stm32g474xx.h"


int duration = 0;
int button_was_pressed = 0;

void EXTI15_10_IRQHandler() {
	if(EXTI -> PR1 & EXTI_PR1_PIF12) {
		if((GPIOB->IDR & GPIO_IDR_ID12) == 0) {
			duration++;
		} else if (GPIOB->IDR & GPIO_IDR_ID12) {
			EXTI -> PR1 |= EXTI_PR1_PIF12;
			button_was_pressed = 1;
		}
	}
}


int main(void) {
	int num, x, index, prev;
	int number = 0;
	int binary[4] = {0,0,0,0};

	RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOBEN |
				RCC_AHB2ENR_GPIODEN |
				RCC_AHB2ENR_GPIOEEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;


	SYSCFG -> EXTICR[3] |= SYSCFG_EXTICR4_EXTI12_PB;
	EXTI -> IMR1 |= EXTI_IMR1_IM12;
	EXTI -> RTSR1 |= EXTI_RTSR1_RT12;
	EXTI -> FTSR1 |= EXTI_FTSR1_FT12;
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	GPIOE -> MODER &= ~GPIO_MODER_MODE7_Msk &
			~GPIO_MODER_MODE15_Msk;
	GPIOE -> MODER |= 1 << GPIO_MODER_MODE7_Pos |
			1 << GPIO_MODER_MODE15_Pos;

	GPIOD -> MODER &= ~GPIO_MODER_MODE8_Msk &
			~GPIO_MODER_MODE0_Msk;
	GPIOD -> MODER |= 1 << GPIO_MODER_MODE8_Pos |
			1 << GPIO_MODER_MODE0_Pos;

	GPIOB -> MODER &= ~GPIO_MODER_MODE12_Msk;
	GPIOB -> MODER |= 0 << GPIO_MODER_MODE12_Pos;



	while(1) {
		if(button_was_pressed) {
			if(duration > 170000)
				number = 0;
			if(duration <= 170000 && duration > 0)
				if(number < 15)
					number++;
			button_was_pressed = 0;
			duration = 0;
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
		} else {
			GPIOE -> ODR &= ~GPIO_ODR_OD7;
		}
		if(binary[2] == 1) {
			GPIOE -> ODR |= GPIO_ODR_OD15;
		} else {
			GPIOE -> ODR &= ~GPIO_ODR_OD15;
		}
		if(binary[1] == 1) {
			GPIOD -> ODR |= GPIO_ODR_OD8;
		} else {
			GPIOD -> ODR &= ~GPIO_ODR_OD8;
		}
		if(binary[0] == 1) {
			GPIOD -> ODR |= GPIO_ODR_OD0;
		} else {
			GPIOD -> ODR &= ~GPIO_ODR_OD0;
		}
	}
}
