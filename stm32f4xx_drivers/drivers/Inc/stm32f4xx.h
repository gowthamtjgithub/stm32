/*
 * stm32f4xx.h
 *
 *  Created on: May 12, 2022
 *      Author: gowth
 */

#ifndef INC_STM32F4XX_H_
#define INC_STM32F4XX_H_

#include "stdio.h"
#include "stdlib.h"

#define _vo volatile

/*
 * ARM Cortex MX Processor NVIC ISERx register addresses
 */
#define NVIC_ISER0  ((_vo uint32_t*)0xE000E100)
#define NVIC_ISER1	((_vo uint32_t*)0xE000E104)
#define NVIC_ISER2	((_vo uint32_t*)0xE000E108)
#define NVIC_ISER3	((_vo uint32_t*)0xE000E10C)

/*
 * ARM Cortex Mx Processor NVIC ICERx register addresses
 */
#define NVIC_ICER0	((_vo uint32_t*)0xE000E180)
#define NVIC_ICER1  ((_vo uint32_t*)0xE000E184)
#define NVIC_ICER2	((_vo uint32_t*)0xE000E188)
#define NVIC_ICER3	((_vo uint32_t*)0xE000E18C)

/*
 * ARM Cortex Mx Processor Priority Register Address Calculation
 */
#define NVIC_PR_BASE_ADDR ((_vo uint32_t*)0xE000E400)

#define NO_PR_BITS_IMPLEMENTED 	4


/**
 	 	 Base addresses of flash and SRAM memories
 * */



#define FLASH_BASEADDR 0X08000000U //Base address of Flash Memory
#define SRAM1_BASEADDR 0X20000000U //112KB Base address of SRAM1
#define SRAM2_BASEADDR 0X20001C00U //16KB  Base address of SRAM2
#define ROM			   0x1FFF0000  //Base address of System memory or ROM
#define SRAM 		   SRAM1_BASEADDR //Base address of SRAM

/**
 * 		AHBx and APBx Bus Peripheral base addresses
 * **/

#define PERIPH_BASEADDR		 0x40000000U
#define APB1PERIPH_BASEADDR  PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR  0x40010000U
#define AHB1PERIPH_BASEADDR  0x40020000U
#define AHB2PERIPH_BASEADDR  0x50000000U


/**
 * 	Base addresses of peripherals on AHB1 bus
 * **/
#define GPIOA_BASEADDR    (AHB1PERIPH_BASEADDR + 0X0000)
#define GPIOB_BASEADDR	  (AHB1PERIPH_BASEADDR + 0X0400)
#define GPIOC_BASEADDR    (AHB1PERIPH_BASEADDR + 0X0800)
#define GPIOD_BASEADDR    (AHB1PERIPH_BASEADDR + 0X0C00)
#define GPIOE_BASEADDR    (AHB1PERIPH_BASEADDR + 0X1000)
#define GPIOF_BASEADDR    (AHB1PERIPH_BASEADDR + 0X1400)
#define GPIOG_BASEADDR    (AHB1PERIPH_BASEADDR + 0X1800)
#define GPIOH_BASEADDR    (AHB1PERIPH_BASEADDR + 0X1C00)
#define GPIOI_BASEADDR    (AHB1PERIPH_BASEADDR + 0X2000)
#define RCC_BASEADDR	  (AHB1PERIPH_BASEADDR + 0X3800)
/**
 * Base addresses of peripherals on APB1 bus
 * **/
#define I2C1_BASEADDR  (APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR	(APB1PERIPH_BASEADDR + 0X5800)
#define I2C3_BASEADDR   (APB1PERIPH_BASEADDR + 0X5C00)
#define USART2_BASEADDR  (APB1PERIPH_BASEADDR + 0X4400)
#define USART3_BASEADDR  (APB1PERIPH_BASEADDR + 0X4800)
#define UART4_BASEADDR  (APB1PERIPH_BASEADDR + 0X4C00)
#define UART5_BASEADDR  (APB1PERIPH_BASEADDR + 0X5000)
#define SPI2_BASEADDR    (APB1PERIPH_BASEADDR + 0X3800)
#define SPI3_BASEADDR    (APB1PERIPH_BASEADDR + 0X3C00)

/**
		Base addresses of peripherals on APB2 bus
**/
#define USART1_BASEADDR  (APB2PERIPH_BASEADDR + 0X1000)
#define USART6_BASEADDR  (APB2PERIPH_BASEADDR + 0X1400)
#define SPI1_BASEADDR  (APB2PERIPH_BASEADDR + 0X3000)
#define SYSCONFIG_BASEADDR  (APB2PERIPH_BASEADDR + 0X3800)
#define EXT1_BASEADDR  (APB2PERIPH_BASEADDR + 0X3C00)

/**************peripheral register definition structures***********************/
typedef struct {
	_vo uint32_t MODER;   /*GPIO port mode register,					 Address offset: 0x00*/
	_vo uint32_t OTYPER;  /*GPIO port output type register 				 Address offset: 0X04*/
	_vo uint32_t OSPEEDR; /*GPIO port output speed register 			 Address offset::0X08*/
	_vo uint32_t PUPDR;   /*GPIO port pull-up/pull-down register 		 Address offset::0X0C*/
	_vo uint32_t IDR;     /*GPIO port input data register   			 Address offset:0X10*/
	_vo uint32_t ODR;     /*GPIO port output data register  			 Address offset:0X14*/
	_vo uint32_t BSRR;    /*GPIO port bit set/reset register 			 Address offset:0X18*/
	_vo uint32_t LCKR;    /*GPIO port configuration lock register 		 Address offset:0X1A*/
	_vo uint32_t AFR[2];  /*AFR[0]: GPIO alternate function low register Address offset:0X20-0X24
	 	 	 	 	 	AFR[1]: GPIO alternate function high register
	 	 	 	 	 	*/
}GPIO_RegDef_t;

#define GPIOA (GPIO_RegDef_t*)GPIOA_BASEADDR
#define GPIOB (GPIO_RegDef_t*)GPIOB_BASEADDR
#define GPIOC (GPIO_RegDef_t*)GPIOC_BASEADDR
#define GPIOD (GPIO_RegDef_t*)GPIOD_BASEADDR
#define GPIOE (GPIO_RegDef_t*)GPIOE_BASEADDR



typedef struct {
	_vo uint32_t I2C_CR1;  /**I2C Control register 1 	  Address offset:0X00**/
	_vo uint32_t I2C_CR2;  /**I2C Control register 2      Address offset:0X04**/
	_vo uint32_t I2C_OAR1; /**I2C Own address register 1  Address offset:0X08**/
	_vo uint32_t I2C_OAR2; /**I2C Own address register 2  Address offset:0X0C**/
	_vo uint32_t I2C_DR;   /**I2C Data register			  Address offset:0X10 **/
	_vo uint32_t I2C_SR1;  /**I2C Status register 1 	  Address offset:0X14**/
	_vo uint32_t I2C_SR2;  /**I2C Status register 2 	  Address offset:0X18**/
	_vo uint32_t I2C_CCR;  /**I2C Clock control register  Address offset:0X1C**/
	_vo uint32_t I2C_TRISE;/**I2C TRISE register		  Address offset:0X20**/
	_vo uint32_t I2C_FLTR; /**I2C FLTR register			  Address offset:0X24**/
}I2C_RegDef_t;

#define I2C1 (I2C_RegDef_t*)I2C1_BASEADDR
#define I2C2 (I2C_RegDef_t*)I2C2_BASEADDR
#define I2C3 (I2C_RegDef_t*)I2C3_BASEADDR


typedef struct {
	_vo uint32_t USART_SR;	/**Status register		Address offset:0X00**/
	_vo uint32_t USART_DR;	/**data register		Address offset:0X04**/
	_vo uint32_t USART_BRR;	/**Baud rate register	Address offset:0X08**/
	_vo uint32_t USART_CR1;	/**Control register 1	Address offset:0X0C**/
	_vo uint32_t USART_CR2;	/**Control register 2	Address offset:0X10**/
	_vo uint32_t USART_CR3;	/**Control register 3	Address offset:0X14**/
	_vo uint32_t USART_GTPR;/**Guard time and prescaler register Address offset:0X18**/
}USART_RegDef_t;

#define USART1  (USART_RegDef_t*)USART1_BASEADDR
#define USART2  (USART_RegDef_t*)USART2_BASEADDR
#define USART3  (USART_RegDef_t*)USART3_BASEADDR
#define UART4   (USART_RegDef_t*)UART4_BASEADDR
#define UART5   (USART_RegDef_t*)UART5_BASEADDR
#define USART6  (USART_RegDef_t*)USART6_BASEADDR

typedef struct {
	_vo uint32_t SPI_CR1; 		/**SPI control register 1 			Address offset:0X00**/
	_vo uint32_t SPI_CR2;		/**SPI control register 2 			Address offset:0X04**/
	_vo uint32_t SPI_SR;		/**SPI status register				Address offset:0X08**/
	_vo uint32_t SPI_DR;		/**SPI data register				Address offset:0X0C**/
	_vo uint32_t SPI_CRCPR;		/**SPI CRC polynomial register		Address offset:0X10**/
	_vo uint32_t SPI_RXCRCR;	/**SPI RX CRC register				Address offset:0X14**/
	_vo uint32_t SPI_TXCRCR;	/**SPI TX CRC register				Address offset:0X18**/
	_vo uint32_t SPI_I2SCFGR;	/**SPI_I2S configuration register	Address offset:0X1C**/
	_vo uint32_t SPI_I2SPR;		/**SPI_I2S prescaler register		Address offset:0X20**/
}SPI_RegDef_t;

#define SPI1 (SPI_RegDef_t*)SPI1_BASEADDR
#define SPI2 (SPI_RegDef_t*)SPI2_BASEADDR
#define SPI3 (SPI_RegDef_t*)SPI3_BASEADDR


typedef struct {
	_vo uint32_t RCC_CR;	   /**RCC clock control register  Address offset:0x00**/
	_vo uint32_t RCC_PLLCFGR;  /**RCC PLL configuration register**/
	_vo uint32_t RCC_CFGR;	   /**RCC clock configuration register**/
	_vo uint32_t RCC_CIR;	   /**RCC clock interrupt register**/
	_vo uint32_t RCC_AHB1RSTR; /**RCC AHB1 peripheral reset register**/
	_vo uint32_t RCC_AHB2RSTR; /**RCC AHB2 peripheral reset register**/
	_vo uint32_t RCC_AHB3RSTR; /**RCC AHB3 peripheral reset register**/
	uint32_t Reserved_1;

	_vo uint32_t RCC_APB1RSTR; /**RCC APB1 peripheral reset register**/
	_vo uint32_t RCC_APB2RSTR; /**RCC APB2 peripheral reset register**/
	uint32_t Reserved_2;	   /****/
	uint32_t Reserved_3;	   /****/
	_vo uint32_t RCC_AHB1ENR;  /**RCC AHB1 peripheral clock enable register**/
	_vo uint32_t RCC_AHB2ENR;  /**RCC AHB2 peripheral clock enable register**/
	_vo uint32_t RCC_AHB3ENR;  /**RCC AHB3 peripheral clock enable register**/
	uint32_t Reserved_4;	   /****/

	_vo uint32_t RCC_APB1ENR;	 /**RCC APB1 peripheral clock enable register**/
	_vo uint32_t RCC_APB2ENR;	 /**RCC APB2 peripheral clock enable register**/
	uint32_t Reserved_5;		 /****/
	uint32_t Reserved_6;		 /****/
	_vo uint32_t RCC_AHB1LP_ENR; /**RCC AHB1 peripheral clock enable in low power mode register**/
	_vo uint32_t RCC_AHB2LP_ENR; /**RCC AHB2 peripheral clock enable in low power mode register**/
	_vo uint32_t RCC_AHB3LP_ENR; /**RCC AHB3 peripheral clock enable in low power mode register**/
	uint32_t Reserved_7;		 /****/
	_vo uint32_t RCC_APB1LP_ENR; /**RCC APB1 peripheral clock enable in low power mode register**/
	_vo uint32_t RCC_APB2LP_ENR; /**RCC APB2 peripheral clock enable in low power mode register**/
	uint32_t Reserved_8;		 /****/
	uint32_t Reserved_9;		 /****/
	_vo uint32_t RCC_BDCR;		 /**RCC Backup domain control register**/
	_vo uint32_t RCC_CSR;		 /**RCC clock control & status register**/
	uint32_t Reserved_10;		 /****/
	uint32_t Reserved_11;		 /****/
	_vo uint32_t RCC_SSCGR;		 /**RCC spread spectrum clock generation register**/
	_vo uint32_t RCC_PLLI2SCFGR; /**RCC PLLI2S configuration register**/
}RCC_RegDef_t;
#define RCC ((RCC_RegDef_t*)RCC_BASEADDR)

/*
 * register structure for SYSCFG
 */
typedef struct{
	_vo uint32_t MEMRMP;/*SYSCFG memory remap register							Address offset:0X00*/
	_vo uint32_t PMC;   /*SYSCFG peripheral mode configuration register			Address offset:0X04*/
	_vo uint32_t EXTICR[4];/*SYSCFG external interrupt configuration register 1	Address offset:0X08*/
	_vo uint32_t CMPCR;	/*Compensation cell control register					Address offset:0X20*/
}SYSCFG_RegDef_t;

#define SYSCFG ((SYSCFG_RegDef_t*)SYSCONFIG_BASEADDR)


/*
 * peripheral register definition structure for EXTI
 */
typedef struct
{
	_vo uint32_t IMR;		/*Interrupt mask register				Address offset:0x00*/
	_vo uint32_t EMR;		/*Event mask register					Address offset:0x04*/
	_vo uint32_t RTSR;		/*Rising trigger selection register		Address offset:0x08*/
	_vo uint32_t FTSR;		/*Falling trigger selection register	Address offset:0x0C*/
	_vo uint32_t SWIER;		/*Software interrupt event register		Address offset:0x10*/
	_vo uint32_t PR;		/*Pending register						Address offset:0x14*/
}EXTI_RegDef_t;

#define EXTI ((EXTI_RegDef_t*)EXT1_BASEADDR)




/**
 * Clock Enable Macros for GPIOx peripherals
 * */

#define GPIOA_PCLK_EN() (RCC->RCC_AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN() (RCC->RCC_AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN() (RCC->RCC_AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN() (RCC->RCC_AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN() (RCC->RCC_AHB1ENR |= (1<<4))

/*
 * Clock Enable Macro for I2Cx peripherals
 * */
#define I2C1_PCLK_EN() (RCC->RCC_APB1ENR |= (1<<21))
#define I2C2_PCLK_EN() (RCC->RCC_APB1ENR |= (1<<22))
#define I2C3_PCLK_EN() (RCC->RCC_APB1ENR |= (1<<23))
/*
 * Clock Enable Macros for SPIx peripherals
 * */
#define SPI1_PCLK_EN()  (RCC->RCC_APB2ENR |= (1<<12))
#define SPI2_PCLK_EN()  (RCC->RCC_APB1ENR |= (1<<14))
#define SPI3_PCLK_EN()  (RCC->RCC_APB1ENR |= (1<<15))
/*
 * Clock Enable Macros for USARTx peripherals
 * */
#define USART1_PCLK_EN() (RCC->RCC_APB2ENR |= (1<<4))
#define USART2_PCLK_EN() (RCC->RCC_APB1ENR |= (1<<17))
#define USART3_PCLK_EN() (RCC->RCC_APB1ENR |= (1<<18))
#define UART4_PCLK_EN()  (RCC->RCC_APB1ENR |= (1<<19))
#define UART5_PCLK_EN()  (RCC->RCC_APB1ENR |= (1<<20))
#define USART6_PCLK_EN() (RCC->RCC_APB2ENR |= (1<<5))

/*
 * Clock Enable Macros for SYSCFG peripheral
 * */
#define SYSCFG_PCLK_EN() (RCC->RCC_APB2ENR |= (1<<14))

/**
 * Clock Disable Macros for GPIOx peripherals
 * */

#define GPIOA_PCLK_DI() (RCC->RCC_AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI() (RCC->RCC_AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI() (RCC->RCC_AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI() (RCC->RCC_AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI() (RCC->RCC_AHB1ENR &= ~(1<<4))

/*
 * Clock Disable Macro for I2Cx peripherals
 * */
#define I2C1_PCLK_DI() (RCC->RCC_APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI() (RCC->RCC_APB1ENR &= ~(1<<22))
#define I2C3_PCLK_DI() (RCC->RCC_APB1ENR &= ~(1<<23))
/*
 * Clock Disable Macros for SPIx peripherals
 * */
#define SPI1_PCLK_DI()  (RCC->RCC_APB2ENR &= ~(1<<12))
#define SPI2_PCLK_DI()  (RCC->RCC_APB1ENR &= ~(1<<14))
#define SPI3_PCLK_DI()  (RCC->RCC_APB1ENR &= ~(1<<15))
/*
 * Clock Disable Macros for USARTx peripherals
 * */
#define USART1_PCLK_DI() (RCC->RCC_APB2ENR &= ~(1<<4))
#define USART2_PCLK_DI() (RCC->RCC_APB1ENR &= ~(1<<17))
#define USART3_PCLK_DI() (RCC->RCC_APB1ENR &= ~(1<<18))
#define UART4_PCLK_DI()  (RCC->RCC_APB1ENR &= ~(1<<19))
#define UART5_PCLK_DI()  (RCC->RCC_APB1ENR &= ~(1<<20))
#define USART6_PCLK_DI() (RCC->RCC_APB2ENR &= ~(1<<5))

/*
 * Clock Disable Macros for SYSCFG peripheral
 * */
#define SYSCFG_PCLK_DI() (RCC->RCC_APB2ENR &= ~(1<<14))

/*
 *This macro returns a code (between 0 to 7) for a given GPIO base address(x)
 */
#define GPIO_BASEADDR_TO_CODE(x) ((x == GPIOA)?0:\
								  (x == GPIOB)?1:\
								  (x == GPIOC)?2:\
								  (x == GPIOD)?3:\
								  (x == GPIOE)?4:0)
/*
 * Macros to reset GPIOx peripherals
 */
#define GPIOA_REG_RESET() do{ (RCC->RCC_AHB1RSTR |= (1<<0)); (RCC->RCC_AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOB_REG_RESET() do{ (RCC->RCC_AHB1RSTR |= (1<<1)); (RCC->RCC_AHB1RSTR &= ~(1<<1)); }while(0)
#define GPIOC_REG_RESET() do{ (RCC->RCC_AHB1RSTR |= (1<<2)); (RCC->RCC_AHB1RSTR &= ~(1<<2)); }while(0)
#define GPIOD_REG_RESET() do{ (RCC->RCC_AHB1RSTR |= (1<<3)); (RCC->RCC_AHB1RSTR &= ~(1<<3)); }while(0)
#define GPIOE_REG_RESET() do{ (RCC->RCC_AHB1RSTR |= (1<<4)); (RCC->RCC_AHB1RSTR &= ~(1<<4)); }while(0)

/*
 * IRQ(Interrupt Request) Numbers of STM32F407x MCU
 * NOTE: update these macros wth valid values according to your MCU
 * TODO: You may complete this list for other peripherals
 */
#define IRQ_NO_EXTI0	 6
#define IRQ_NO_EXTI1	 7
#define IRQ_NO_EXTI2	 8
#define IRQ_NO_EXTI3	 9
#define IRQ_NO_EXTI4	 10
#define IRQ_NO_EXTI9_5	 23
#define IRQ_NO_EXTI15_10 40

#define IRQ_NO_WWDG		  0
#define IRQ_NO_PVD		  1
#define IRQ_NO_TAMP_STAMP 2
#define IRQ_NO_RTC_WKUP   3
#define IRQ_NO_FLASH	  4
#define IRQ_NO_RCC		  5

#define IRQ_NO_DMA1_Stream0 11
#define IRQ_NO_DMA1_Stream1 12
#define IRQ_NO_DMA1_Stream3 13
#define IRQ_NO_DMA1_Stream4 14
#define IRQ_NO_DMA1_Stream5 15
#define IRQ_NO_DMA1_Stream6 16
#define IRQ_NO_DMA1_Stream7 47

#define IRQ_NO_DMA2_Stream0 56
#define IRQ_NO_DMA2_Stream1 57
#define IRQ_NO_DMA2_Stream2 58
#define IRQ_NO_DMA2_Stream3 59
#define IRQ_NO_DMA2_Stream4 60
#define IRQ_NO_DMA2_Stream5 68
#define IRQ_NO_DMA2_Stream6 69
#define IRQ_NO_DMA2_Stream7 70


#define IRQ_NO_ADC			18
#define IRQ_NO_CAN1_TX		19
#define IRQ_NO_CAN1_RX0     20
#define IRQ_NO_CAN1_RX1     21
#define IRQ_NO_CAN1_SCE     22
#define IRQ_NO_CAN2_TX		63
#define IRQ_NO_CAN2_RX0     64
#define IRQ_NO_CAN2_RX1     65
#define IRQ_NO_CAN2_SCE     66

#define IRQ_NO_ETH			61
#define IRQ_NO_ETH_WKUP		62

#define IRQ_NO_TIM1_BRK_TIM9 24
#define IRQ_NO_TIM1_UP_TIM10 25
#define IRQ_NO_TIM1_TRG_COM_TIM11 26
#define IRQ_NO_TIM1_CC		 27

#define IRQ_NO_TIM2			 28
#define IRQ_NO_TIM3    		 29
#define IRQ_NO_TIM4			 30
#define IRQ_NO_TIM5   		 50

#define IRQ_NO_I2C1_EV		 31
#define IRQ_NO_I2C1_ER		 32
#define IRQ_NO_I2C2_EV		 33
#define IRQ_NO_I2C2_ER       34
#define IRQ_NO_I2C3_EV		 72
#define IRQ_NO_I2C3_ER       73

#define IRQ_NO_SPI1			 35
#define IRQ_NO_SPI2			 36
#define IRQ_NO_SPI3			 51

#define IRQ_NO_USART1		 37
#define IRQ_NO_USART2		 38
#define IRQ_NO_USART3		 39
#define IRQ_NO_UART4		 52
#define IRQ_NO_UART5		 53
#define IRQ_NO_USART6 		 71


#define IRQ_NO_TIM6_DAC		  54
#define IRQ_NO_TIM7			  55
#define IRQ_NO_TIM8_BRK_TIM12 43
#define IRQ_NO_TIM8_UP_TIM13  44
#define IRQ_NO_TIM8_TRG_COM_TIM14 45
#define IRQ_NO_TIM8_CC		  46

#define IRQ_NO_OTG_WKUP		  42
#define IRQ_NO_OTG_FS		  67
#define IRQ_NO_OTG_HS_EP1_OUT 74
#define IRQ_NO_OTG_HS_EP1_IN  75
#define IRQ_NO_OTG_HS_WKUP	  76
#define IRQ_NO_OTG_HS		  77

#define IRQ_NO_RTC_ALARM	41
#define IRQ_NO_DCMI			78
#define IRQ_NO_CRYP			79
#define IRQ_NO_HASH_RNG		80
#define IRQ_NO_FPU			81
#define IRQ_NO_FSMC			48
#define IRQ_NO_SDIO			49


/*
 * macros for all the possible priority levels
 */
#define NVIC_IRQ_PRI0	0
#define NVIC_IRQ_PRI4	10



//some generic macros

#define ENABLE		   1
#define DISABLE 	   0
#define SET 		   ENABLE
#define RESET 		   DISABLE
#define GPIO_PIN_SET   SET
#define GPIO_PIN_RESET RESET
#define FLAG_SET	   SET
#define FLAG_RESET	   RESET


/*************************************************************
 * 		Bit position definitions of SPI peripheral
 ***************************************************************/
#define SPI_CR1_BIDIMODE 15
#define SPI_CR1_MSTR	 2
#define SPI_CR1_BR 		 3
#define SPI_CR1_DFF		 11
#define SPI_CR1_CPOL	 1
#define SPI_CR1_CPHA	 0
#define SPI_CR1_SPE	     6
#define SPI_CR1_LSBFIRST 7
#define SPI_CR1_SSI	8
#define SPI_CR1_SSM 9
#define SPI_CR1_RXONLY	10
#define SPI_CR1_CRCNEXT	12
#define SPI_CR1_CRCEN	13
#define SPI_CR1_BIDIOE	14

#define SPI_CR2_RXDMAEN	0
#define SPI_CR2_TXDMAEN	1
#define SPI_CR2_SSOE	2
#define SPI_CR2_FRF		4
#define SPI_CR2_ERRIE	5
#define SPI_CR2_RXNEIE  6
#define SPI_CR2_TXEIE	7

#define SPI_SR_RXNE	0
#define SPI_SR_TXE	1
#define SPI_SR_CHSIDE 2
#define SPI_SR_UDR    3
#define SPI_SR_CRCERR 4
#define SPI_SR_MODF	5
#define SPI_SR_OVR  6
#define SPI_SR_BSY  7
#define SPI_SR_FRE  8

#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"

#endif /* INC_STM32F4XX_H_ */
