#include "stm32g474xx.h"

int button_pressed_1 = 0;
int victory_bool = 0;

int checkbutton() {
	if((GPIOB->IDR & GPIO_IDR_ID15) == 0 && button_pressed_1 == 0) {
		button_pressed_1 = 1;
		victory_bool = !victory_bool;
		return 1;
	} else if (GPIOB->IDR & GPIO_IDR_ID15)
		button_pressed_1 = 0;

	return 0;
}

void delay(uint32_t time_delay) {
    for(uint32_t i = 0; i < time_delay * 800; i++);
}

void victory() {
	if(checkbutton()) {
		return;
	}
	delay(100);
	GPIOE -> ODR ^= GPIO_ODR_OD12;
	GPIOE -> ODR ^= GPIO_ODR_OD13;
	delay(100);
	GPIOE -> ODR ^= GPIO_ODR_OD14;
	GPIOE -> ODR ^= GPIO_ODR_OD15;
	delay(200);
	GPIOE -> ODR ^= GPIO_ODR_OD15;
	GPIOE -> ODR ^= GPIO_ODR_OD14;
	delay(100);
	GPIOE -> ODR ^= GPIO_ODR_OD13;
	GPIOE -> ODR ^= GPIO_ODR_OD12;

}

void lose() {
	if(checkbutton()) {
		return;
	}
	delay(300);
	GPIOE -> ODR ^= GPIO_ODR_OD15;
	GPIOE -> ODR ^= GPIO_ODR_OD14;
	GPIOE -> ODR ^= GPIO_ODR_OD13;
	GPIOE -> ODR ^= GPIO_ODR_OD12;
	delay(100);
	GPIOE -> ODR ^= GPIO_ODR_OD12;
	delay(80);
	GPIOE -> ODR ^= GPIO_ODR_OD13;
	delay(80);
	GPIOE -> ODR ^= GPIO_ODR_OD14;
	delay(80);
	GPIOE -> ODR ^= GPIO_ODR_OD15;
}

int main(void) {

	RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOEEN | RCC_AHB2ENR_GPIOBEN;

	GPIOE -> MODER &= ~GPIO_MODER_MODE15_Msk;
	GPIOE -> MODER |= 1 << GPIO_MODER_MODE15_Pos;
	GPIOE -> MODER &= ~GPIO_MODER_MODE14_Msk;
	GPIOE -> MODER |= 1 << GPIO_MODER_MODE14_Pos;
	GPIOE -> MODER &= ~GPIO_MODER_MODE13_Msk;
	GPIOE -> MODER |= 1 << GPIO_MODER_MODE13_Pos;
	GPIOE -> MODER &= ~GPIO_MODER_MODE12_Msk;
	GPIOE -> MODER |= 1 << GPIO_MODER_MODE12_Pos;


	GPIOB->MODER &= ~GPIO_MODER_MODE15_Msk;
	GPIOB->MODER |= 0 << GPIO_MODER_MODE15_Pos;


	while(true) {
		if(victory_bool) {
			victory();
		} else {
			lose();
		}
	}
}
