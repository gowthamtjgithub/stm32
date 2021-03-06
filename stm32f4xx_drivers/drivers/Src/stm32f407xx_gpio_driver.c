/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: 15-May-2022
 *      Author: gowth
 */

#include "stm32f407xx_gpio_driver.h"
#include "stm32f4xx.h"

/*
 *Peripheral Clock setup
 */
/*************************************************************
 * @fn				- GPIO_PeriClockControl
 *
 * @brief			- This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]		- base address of the gpio peripheral
 * @param[in]		- ENABLE or DISABLE macros
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
	}
}

/*
 	 Init and De-Init
 */
/*************************************************************
 * @fn				- GPIO_Initialisation
 *
 * @brief			- This function initialises the register values of  GPIO port
 *
 * @param[in]		- macros for GPIO initialistion handler
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{

		uint32_t temp = 0;

		//enable the peripheral clock
		GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

		//1.configure the mode of gpio pin
		if(pGPIOHandle->pGPIO_PinConfig->GPIO_PinMode <= GPIO_MODE_ANALOG)
		{
			//the non-interrupt mode
			temp = (pGPIOHandle->pGPIO_PinConfig->GPIO_PinMode << (2 * pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber));
			pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber);//clearing
			pGPIOHandle->pGPIOx->MODER |= temp;//setting

		}
		else
		{
			//this part will code later. (interrupt mode)

			if((pGPIOHandle->pGPIO_PinConfig->GPIO_PinMode) == GPIO_MODE_IT_FT)
			{
				//configure the FTSR
				EXTI->FTSR |= (1<< pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber);
				//Clear the corresponding RTSR bit
				EXTI->RTSR &= ~(1<< pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber);
			}
			else if(pGPIOHandle->pGPIO_PinConfig->GPIO_PinMode == GPIO_MODE_IT_RT)
			{
				//configure the RTSR
				EXTI->RTSR |= (1<< pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber);
				//Clear the corresponding FTSR bit
				EXTI->FTSR &= ~(1<< pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber);
			}
			else if(pGPIOHandle->pGPIO_PinConfig->GPIO_PinMode == GPIO_MODE_IT_RFT)
			{
				//configure both FTSR and RTSR
				EXTI->FTSR |= (1<< pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber);
				EXTI->RTSR |= (1<< pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber);

			}

			//2. configure the GPIO port selection in SYSCFG_EXTICR
			uint8_t temp1 = pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber / 4;
			uint8_t temp2 = pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber % 4;
			uint8_t portCode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
			SYSCFG_PCLK_EN();
			SYSCFG->EXTICR[temp1] = portCode << (temp2 * 4);

			//3. enable the exti interrupt delivery using IMR
			EXTI->IMR |= (1<< pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber);

		}

		temp = 0;

		//2. configure the speed
		temp = (pGPIOHandle->pGPIO_PinConfig->GPIO_PinSpeed << (2 * pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber));
		pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber);//clearing
		pGPIOHandle->pGPIOx->OSPEEDR |= temp;//setting

		temp = 0;

		//3. configure the pupd settings
		temp = (pGPIOHandle->pGPIO_PinConfig->GPIO_PinPupdControl << (2 * pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber));
		pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber);//clearing
		pGPIOHandle->pGPIOx->PUPDR |= temp;//setting

		temp = 0;

		//4. configure the output type
		temp = (pGPIOHandle->pGPIO_PinConfig->GPIO_PinOPType << (pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber));
		pGPIOHandle->pGPIOx->OTYPER &= ~(0x3 << pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber);//clearing
		pGPIOHandle->pGPIOx->OTYPER |= temp;//	setting

		temp = 0;

		//5. configure the alternate functionality
		if(pGPIOHandle->pGPIO_PinConfig->GPIO_PinMode == GPIO_MODE_ALTFN)
		{
			//Configure the alternate function registers
			 if(pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber){

				 //configure the alt function registers
				 uint8_t temp1, temp2;

				 temp1 = pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber / 8;
				 temp2 = pGPIOHandle->pGPIO_PinConfig->GPIO_PinNumber % 8;
				 pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));
				 pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->pGPIO_PinConfig->GPIO_PinAltFunMode << (4 * temp2));
			 }
		}
}
/*************************************************************
 * @fn				- GPIO_DeInitialisation
 *
 * @brief			- This function resets the register values of  GPIO port
 *
 * @param[in]		- macros for GPIO Reset handler
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 */

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
			if(pGPIOx == GPIOA)
			{
				GPIOA_REG_RESET();
			}
			else if(pGPIOx == GPIOB)
			{
				GPIOB_REG_RESET();
			}
			else if(pGPIOx == GPIOC)
			{
				GPIOC_REG_RESET();
			}
			else if(pGPIOx == GPIOD)
			{
				GPIOD_REG_RESET();
			}
			else if(pGPIOx == GPIOE)
			{
				GPIOE_REG_RESET();
			}
}

/*
 *	Data read and write
 **/
/*************************************************************
 * @fn				- GPIO_ReadFromInputPin
 *
 * @brief			- This function reads the value of the given pin no of a port
 *
 * @param[in]		- base address of gpio peripheral
 * @param[in]		- pin number which value to be read from
 * @param[in]		-
 *
 * @return			- bit value of the register corresponding to the pin number
 *
 * @Note			- none
 */

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = ((pGPIOx->IDR>>PinNumber) & 0x00000001);
	return value;
}
/*************************************************************
 * @fn				- GPIO_ReadFromInputPort
 *
 * @brief			- This function reads the value of the all the bits of gpio input register
 *
 * @param[in]		- base address of gpio peripheral
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- register value of gpio port
 *
 * @Note			- none
 */

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = pGPIOx->IDR;
	return value;
}
/*************************************************************
 * @fn				- GPIO_WriteToOutputPin
 *
 * @brief			- This function sets or resets a particular pin/bit of a gpio port
 *
 * @param[in]		- base address of gpio
 * @param[in]		- pin number
 * @param[in]		- value to be written into the pin
 *
 * @return			- none
 *
 * @Note			- none
 */

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1<<PinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1<<PinNumber);
	}
}
/*************************************************************
 * @fn				- GPIO_WriteToOutputPort
 *
 * @brief			- This function write the value to the entire register of a port
 *
 * @param[in]		- base address of gpio
 * @param[in]		- value to be written to the gpio register
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 */

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{

	pGPIOx->ODR = Value;

}
/*************************************************************
 * @fn				- GPIO_ToggleOutputPin
 *
 * @brief			- This function toggles the state of a pin in a gpio port
 *
 * @param[in]		- base address of gpio
 * @param[in]		- pin number
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 */

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1<<PinNumber);
}

/*
 *	IRQ Configuration and ISR handling
 **/

/*************************************************************
 * @fn				- GPIO_InterruptConfiguration
 *
 * @brief			- This function configures the interrupt request of all gpio ports
 *
 * @param[in]		- Interrupt Request Number
 * @param[in]		- Interrupt Request priority
 * @param[in]		- interrupt enable or disable
 *
 * @return			- none
 *
 * @Note			- none
 */

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			//program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber );
		}
		else if(IRQNumber > 31 && IRQNumber < 64)//32 to 63
		{
			//program ISER1 register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32 ));
		}
		else if(IRQNumber >= 64 && IRQNumber <96)
		{
			//program ISER2 register
			*NVIC_ISER2 |= (1 << (IRQNumber % 64));
		}
	}
	else
	{
				if(IRQNumber <= 31)
				{
					//program ICER0 register
					*NVIC_ICER0 |= (1 << IRQNumber );
				}
				else if(IRQNumber > 31 && IRQNumber <64)
				{
					//program ICER1 register
					*NVIC_ICER1 |= (1 << (IRQNumber % 32 ));
				}
				else if(IRQNumber >= 64 && IRQNumber <96)
				{
					//program ICER2 register
					*NVIC_ICER2 |= (1 << (IRQNumber % 64));
				}
	}
}

/*************************************************************
 * @fn				- GPIO_IRQPriorityConfig
 *
 * @brief			- This function configures the priority interrupt request of all gpio ports
 *
 * @param[in]		- Interrupt Request Number
 * @param[in]		- Interrupt Request priority
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority ){

	//1. first lets find out the ipr register
	uint8_t iprx = IRQNumber /4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + (iprx)) |= (IRQPriority << shift_amount);
}


/*************************************************************
 * @fn				- GPIO_InterruptRequestHandling
 *
 * @brief			- This function handles the interrupt request
 *
 * @param[in]		- pin number
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 */

void GPIO_IRQHandling(uint8_t PinNumber)
{
	//clear the exti pr register corresponding to the pin number
	if(EXTI->PR & (1 << PinNumber))
	{
		//clear
		EXTI->PR |= (1 << PinNumber);
	}
}
