#ifndef __LED_H
#define	__LED_H


#include "stm32f10x.h"


/* 定义KEY的GPIO端口*/
// ROW
#define KEY_GPIO_PORT_ROW    	GPIOB			              /* GPIO端口 */
#define KEY_GPIO_CLK_ROW 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define KEY_GPIO_PIN_ROW  GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15		      

// COLUMN
#define KEY_GPIO_PORT_COL    	GPIOA			              /* GPIO端口 */
#define KEY_GPIO_CLK_COL 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define KEY_GPIO_PIN_COL GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7        


#define            GENERAL_TIM                   TIM3
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
#define            GENERAL_TIM_Period            10000 //ARR的值
#define            GENERAL_TIM_Prescaler         72-1 //时钟分频

/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define ON  0
#define OFF 1

/* 使用标准的固件库控制IO*/
#define LED1(a)	if (a)	\
					GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN)

#define LED2(a)	if (a)	\
					GPIO_SetBits(LED2_GPIO_PORT,LED2_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED2_GPIO_PORT,LED2_GPIO_PIN)

#define LED3(a)	if (a)	\
					GPIO_SetBits(LED3_GPIO_PORT,LED3_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED3_GPIO_PORT,LED3_GPIO_PIN)


/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态



void KEY_GPIO_Config(void);
void GENERAL_TIM_Mode_Config(void);
void KeyScan(void);
float Calculator(char *a);

#endif /* __LED_H */
