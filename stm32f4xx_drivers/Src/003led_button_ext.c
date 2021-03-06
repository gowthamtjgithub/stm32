/*
 * 003led_button_ext.c
 *
 *  Created on: 19-May-2022
 *      Author: gowth
 */
#include "stm32f4xx.h"

#define HIGH 1
#define LOW 0
#define BTN_PRESSED LOW

void delay(void){
	for(uint32_t i=0; i<50000/2; i++);
}

int main(void)
{
	GPIO_Handle_t GPIOBtn;
	GPIOBtn.pGPIO_PinConfig->GPIO_PinNumber = GPIO_PIN_2;
	GPIOBtn.pGPIO_PinConfig->GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.pGPIO_PinConfig->GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.pGPIO_PinConfig->GPIO_PinOPType = GPIO_OP_TYPE_OD;
	GPIOBtn.pGPIO_PinConfig->GPIO_PinPupdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(GPIOA,ENABLE);

	GPIO_Init(&GPIOBtn);

		GPIO_Handle_t GPIOLed;
		GPIOLed.pGPIO_PinConfig->GPIO_PinNumber = GPIO_PIN_6;
		GPIOLed.pGPIO_PinConfig->GPIO_PinMode = GPIO_MODE_OUT;
		GPIOLed.pGPIO_PinConfig->GPIO_PinSpeed = GPIO_SPEED_FAST;
		GPIOLed.pGPIO_PinConfig->GPIO_PinOPType = GPIO_OP_TYPE_PP;
		GPIOLed.pGPIO_PinConfig->GPIO_PinPupdControl = GPIO_PIN_PU;

		GPIO_PeriClockControl(GPIOB,ENABLE);

		GPIO_Init(&GPIOLed);

	while(1)
	{
		int value = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_2);
		if(value == 0){
			//delay();
			GPIO_ToggleOutputPin(GPIOB, GPIO_PIN_6);
		}



	}
	return 0;
}



