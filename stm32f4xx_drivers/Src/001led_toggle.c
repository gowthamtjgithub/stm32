/*
 * 001led_toggle.c
 *
 *  Created on: 18-May-2022
 *      Author: gowth
 */

#include "stm32f4xx.h"

void delay(void){
	for(uint32_t i=0; i<50000; i++);
}

int main(void)
{
	GPIO_Handle_t GPIOLed;
	GPIOLed.pGPIO_PinConfig->GPIO_PinNumber = GPIO_PIN_6;
	GPIOLed.pGPIO_PinConfig->GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLed.pGPIO_PinConfig->GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOLed.pGPIO_PinConfig->GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOLed.pGPIO_PinConfig->GPIO_PinPupdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA,ENABLE);
	GPIO_Init(&GPIOLed);

	while(1)
	{
		GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_7);

		delay();
	}
	return 0;
}
