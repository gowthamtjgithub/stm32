/*
 * main.c
 *
 *  Created on: 24-May-2022
 *      Author: gowth
 */

#include "stm32f4xx.h"
#include "stm32f407xx_gpio_driver.h"

#define HIGH 1
#define LOW 0
#define BTN_PRESSED LOW

void delay(void){
	for(uint32_t i=0; i<50000/2; i++);
}

int main(void)
{

	GPIO_Handle_t GPIOLed, GPIOBtn;

	memset(&GPIOLed,0,sizeof(GPIOLed));
	memset(&GPIOBtn,0, sizeof(GPIOBtn));


	GPIOLed.pGPIOx = GPIOA;
	GPIOLed.pGPIO_PinConfig->GPIO_PinNumber = GPIO_PIN_0;
	GPIOLed.pGPIO_PinConfig->GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLed.pGPIO_PinConfig->GPIO_PinSpeed = GPIO_SPEED_LOW;
	GPIOLed.pGPIO_PinConfig->GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOLed.pGPIO_PinConfig->GPIO_PinPupdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA,ENABLE);

	GPIO_Init(&GPIOLed);

	GPIOBtn.pGPIOx = GPIOC;
	GPIOBtn.pGPIO_PinConfig->GPIO_PinNumber = GPIO_PIN_13;
	GPIOBtn.pGPIO_PinConfig->GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBtn.pGPIO_PinConfig->GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.pGPIO_PinConfig->GPIO_PinPupdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(GPIOC,ENABLE);

	GPIO_Init(&GPIOBtn);



		GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10,47);

		GPIO_IRQConfig(IRQ_NO_EXTI15_10, ENABLE);

		while(1);
		//return 0;
}





void EXTI15_10_IRQHandler(void){
	//handle the interrupt
	delay();
	GPIO_IRQHandling(GPIO_PIN_13);
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_6);
}

