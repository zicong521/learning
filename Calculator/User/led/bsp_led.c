
#include "bsp_led.h"   

#include "stm32f10x.h"
#include "stm32f10x_tim.h"


void GENERAL_TIM_Mode_Config(void)
{
    // 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    NVIC_InitTypeDef NVIC_InitStructure;
    
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  // 开启定时器时钟,即内部时钟CK_INT=72M
    
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;		
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
    NVIC_Init(&NVIC_InitStructure);//TIM3中断配置
    
	GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);
    
    
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	
	// 初始化定时器
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
    
    TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update);
    
    TIM_ITConfig(GENERAL_TIM,TIM_IT_Update,ENABLE);
   
	// 使能计数器
	TIM_Cmd(GENERAL_TIM, ENABLE);
    
    
	
    
    
}
void KEY_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;
        //ROW
		/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( KEY_GPIO_CLK_ROW , ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = KEY_GPIO_PIN_ROW;	

		/*设置引脚模式为通用推挽输出*/
        //row为推挽输出
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(KEY_GPIO_PORT_ROW, &GPIO_InitStructure);	
    
    
    
    //COLUMN
		RCC_APB2PeriphClockCmd( KEY_GPIO_CLK_COL , ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = KEY_GPIO_PIN_COL;	

		/*设置引脚模式为通用推挽输出*/
        //COL为下拉输入 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(KEY_GPIO_PORT_COL, &GPIO_InitStructure);	

		
}


/*********************************************END OF FILE**********************/
