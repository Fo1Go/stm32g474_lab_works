#include "stm32g474xx.h"


//Условие: Реализовать 4-символьный кодовый замок. Каждой кнопке должен
//соответствовать светодиод. Каждая из 4 кнопок должна быть нажата ровно один раз для ввода
//комбинации. При нажатии кнопки первый раз, соответствующий светодиод должен загораться,
//демонстрируя, что введенный символ принят. После повторного нажатия на ту же кнопку не
//должно происходить изменений в комбинации и состоянии светодиодов. После ввода всех 4
//символов должна быть проверка правильности введения комбинации. Если комбинация введена
//неверно должна какое-то время демонстрироваться написанная в задании №1 анимация “ошибки”,
//после чего у пользователя должна быть новая попытка для того, чтобы ввести код. Если
//пользователь вводит неправильно код три раза подряд, анимация “ошибки” должна начать
//крутиться в бесконечном цикле. Если пользователь вводит последовательность правильно, в
//бесконечном цикле должна крутиться анимация “победы” из задания №1.
//

int temp = 0;
int current_elem = 0;
int lost_times = 0;
int win_times = 0;
int password[4] = {0,0,0,0};
int correct_password[4] = {1,4,3,2};
int btn1 = 0, btn2 = 0, btn3 = 0, btn4 = 0;

 void delay(int duration) {
	for(int i = 0; i < duration * 1700; i++);
}

void off() {
	GPIOE -> ODR &= ~GPIO_ODR_OD7;
	GPIOE -> ODR &= ~GPIO_ODR_OD15;
	GPIOD -> ODR &= ~GPIO_ODR_OD8;
	GPIOD -> ODR &= ~GPIO_ODR_OD0;
}

void victory() {
	delay(80);
	GPIOE -> ODR |= GPIO_ODR_OD7;
	delay(80);
	GPIOE -> ODR |= GPIO_ODR_OD15;
	delay(80);
	GPIOD -> ODR |= GPIO_ODR_OD8;
	delay(80);
	GPIOD -> ODR |= GPIO_ODR_OD0;
	delay(80);
	GPIOD -> ODR &= ~GPIO_ODR_OD0;
	delay(60);
	GPIOD -> ODR |= GPIO_ODR_OD0;
	delay(60);
	GPIOD -> ODR &= ~GPIO_ODR_OD0;
	delay(60);
	GPIOD -> ODR |= GPIO_ODR_OD0;
	delay(100);
	off();
}

void lost() {
	delay(300);
	GPIOE -> ODR |= GPIO_ODR_OD7;
	GPIOE -> ODR |= GPIO_ODR_OD15;
	GPIOD -> ODR |= GPIO_ODR_OD8;
	GPIOD -> ODR |= GPIO_ODR_OD0;
	delay(100);
	GPIOE -> ODR &= ~GPIO_ODR_OD7;
	delay(80);
	GPIOE -> ODR &= ~GPIO_ODR_OD15;
	delay(80);
	GPIOD -> ODR &= ~GPIO_ODR_OD8;
	delay(80);
	GPIOD -> ODR &= ~GPIO_ODR_OD0;
}

void checkpassword() {
//	if(
//		!(GPIOE -> ODR & ~GPIO_ODR_OD7 & ~GPIO_ODR_OD15) == 0
//		&&
//		!(GPIOD -> ODR & ~GPIO_ODR_OD0 & ~GPIO_ODR_OD8) == 0
//		) {
	if(btn1 == 1 && btn2 == 1 && btn3 == 1 && btn4 == 1) {
		temp++;
		for(int i = 0; i < 4; i++) {
			if(!(password[i] == correct_password[i])) {
				lost_times++;
				for(int i = 0; i < 4; i++) password[i] = 0;
				current_elem = 0;
				btn1 = 0, btn2 = 0, btn3 = 0, btn4 = 0;
				lost();
				return;
			}
		}
		win_times = 1;
	}
}

void EXTI15_10_IRQHandler() {
	if(EXTI -> PR1 & EXTI_PR1_PIF12) {
		if((GPIOB -> IDR & GPIO_IDR_ID12) == 0) {
			if((GPIOE -> ODR & GPIO_ODR_OD7) == 0) {
				GPIOE -> ODR |= GPIO_ODR_OD7;
				btn1 = 1;
				password[current_elem] = 1;
				current_elem++;
			}
		}
		EXTI->PR1 |= EXTI_PR1_PIF12;
	}

	if(EXTI -> PR1 & EXTI_PR1_PIF13) {
		if((GPIOB -> IDR & GPIO_IDR_ID13) == 0) {
			if((GPIOE -> ODR & GPIO_ODR_OD15) == 0) {
				GPIOE -> ODR |= GPIO_ODR_OD15;
				btn2 = 1;
				password[current_elem] = 2;
				current_elem++;
			}
		}
		EXTI->PR1 |= EXTI_PR1_PIF13;
	}

	if(EXTI -> PR1 & EXTI_PR1_PIF14) {
		if((GPIOB -> IDR & GPIO_IDR_ID14) == 0) {
			if((GPIOD -> ODR & GPIO_ODR_OD8) == 0) {
				GPIOD -> ODR |= GPIO_ODR_OD8;
				btn3 = 1;
				password[current_elem] = 3;
				current_elem++;
			}
		}
		EXTI->PR1 |= EXTI_PR1_PIF14;
	}

	if(EXTI -> PR1 & EXTI_PR1_PIF15) {
		if((GPIOB -> IDR & GPIO_IDR_ID15) == 0) {
			if((GPIOD -> ODR & GPIO_ODR_OD0) == 0) {
				GPIOD -> ODR |= GPIO_ODR_OD0;
				btn4 = 1;
				password[current_elem] = 4;
				current_elem++;
			}
		}
		EXTI->PR1 |= EXTI_PR1_PIF15;
	}
}


int main(void) {
	RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIODEN | RCC_AHB2ENR_GPIOEEN;
	RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	SYSCFG -> EXTICR[3] |= SYSCFG_EXTICR4_EXTI12_PB |
			SYSCFG_EXTICR4_EXTI13_PB |
			SYSCFG_EXTICR4_EXTI14_PB |
			SYSCFG_EXTICR4_EXTI15_PB;

	EXTI -> IMR1 |= EXTI_IMR1_IM12 |
			EXTI_IMR1_IM13 |
			EXTI_IMR1_IM14 |
			EXTI_IMR1_IM15;

	EXTI -> RTSR1 |= EXTI_RTSR1_RT12 |
			EXTI_RTSR1_RT13 |
			EXTI_RTSR1_RT14 |
			EXTI_RTSR1_RT15;

	EXTI -> FTSR1 |= EXTI_FTSR1_FT12 |
			EXTI_FTSR1_FT13 |
			EXTI_FTSR1_FT14 |
			EXTI_FTSR1_FT15;

	NVIC_EnableIRQ(EXTI15_10_IRQn);


	GPIOE -> MODER &= ~GPIO_MODER_MODE7_Msk &
			~GPIO_MODER_MODE15_Msk;

	GPIOE -> MODER |= 1 << GPIO_MODER_MODE7_Pos |
			1 << GPIO_MODER_MODE15_Pos;

	GPIOD -> MODER &= ~GPIO_MODER_MODE8_Msk &
			~GPIO_MODER_MODE0_Msk;

	GPIOD -> MODER |= 1 << GPIO_MODER_MODE8_Pos |
			1 << GPIO_MODER_MODE0_Pos;

	GPIOB -> MODER &= ~GPIO_MODER_MODE12_Msk &
			~GPIO_MODER_MODE13_Msk &
			~GPIO_MODER_MODE14_Msk &
			~GPIO_MODER_MODE15_Msk;

	GPIOB -> MODER |= 0 << GPIO_MODER_MODE12_Pos |
			0 << GPIO_MODER_MODE13_Pos |
			0 << GPIO_MODER_MODE14_Pos |
			0 << GPIO_MODER_MODE15_Pos;

	while(1) {
		if(win_times) {
			victory();
		}
		else if(lost_times >= 3) {
			lost();
		} else {
			checkpassword();
		}
	}
}
