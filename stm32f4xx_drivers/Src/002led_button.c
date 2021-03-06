/*
 * 002led_button.c
 *
 *  Created on: 19-May-2022
 *      Author: gowth
 */

#include "stm32f4xx.h"

void delay(void){
	for(uint32_t i=0; i<50000/2; i++);
}

int main(void)
{
	GPIO_Handle_t GPIOBtn;
	GPIOBtn.pGPIO_PinConfig->GPIO_PinNumber = GPIO_PIN_4;
	GPIOBtn.pGPIO_PinConfig->GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.pGPIO_PinConfig->GPIO_PinSpeed = GPIO_SPEED_FAST;
	//GPIOBtn.pGPIO_PinConfig->GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOBtn.pGPIO_PinConfig->GPIO_PinPupdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(GPIOA,ENABLE);
	GPIO_PeriClockControl(GPIOE,ENABLE);
	GPIO_Init(&GPIOBtn);

	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOE, GPIO_PIN_4)){
			delay();
			GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_7);
		}



	}
	return 0;
}

