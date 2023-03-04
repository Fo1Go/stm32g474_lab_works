# stm32g474_lab_works
Short guide on stm32g4


RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIODEN | RCC_AHB2ENR_GPIOEEN; // ports IO
RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGEN; // port for interrupts

// Init output pin
GPIOE -> MODER &= ~GPIO_MODER_MODE7_Msk;
GPIOE -> MODER |= 1 << GPIO_MODER_MODE7_Pos;

// Init input pin
GPIOB -> MODER &= ~GPIO_MODER_MODE12_Msk;
GPIOB -> MODER |= 0 << GPIO_MODER_MODE12_Pos;

// Output register on port D
GPIOD -> ODR 

// Input register on port B
GPIOB -> IDR

// Value of register on pin7
GPIO_ODR_OD7

// Value of register on pin15
GPIO_IDR_ID15

// Turn on interrputs
SYSCFG -> EXTICR[3] |= SYSCFG_EXTICR4_EXTI12_PB;
EXTI -> IMR1 |= EXTI_IMR1_IM12;
EXTI -> RTSR1 |= EXTI_RTSR1_RT12;
EXTI -> FTSR1 |= EXTI_FTSR1_FT12;
	
NVIC_EnableIRQ(EXTI15_10_IRQn);

// Clean register interrputs
EXTI->PR1 |= EXTI_PR1_PIF14;
