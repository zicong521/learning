
#include "bsp_led.h"   

#include "stm32f10x.h"
#include "stm32f10x_tim.h"


void GENERAL_TIM_Mode_Config(void)
{
    // �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    NVIC_InitTypeDef NVIC_InitStructure;
    
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  // ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;		
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
    NVIC_Init(&NVIC_InitStructure);//TIM3�ж�����
    
	GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);
    
    
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
    
    TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update);
    
    TIM_ITConfig(GENERAL_TIM,TIM_IT_Update,ENABLE);
   
	// ʹ�ܼ�����
	TIM_Cmd(GENERAL_TIM, ENABLE);
    
    
	
    
    
}
void KEY_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;
        //ROW
		/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( KEY_GPIO_CLK_ROW , ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = KEY_GPIO_PIN_ROW;	

		/*��������ģʽΪͨ���������*/
        //rowΪ�������
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(KEY_GPIO_PORT_ROW, &GPIO_InitStructure);	
    
    
    
    //COLUMN
		RCC_APB2PeriphClockCmd( KEY_GPIO_CLK_COL , ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = KEY_GPIO_PIN_COL;	

		/*��������ģʽΪͨ���������*/
        //COLΪ�������� 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(KEY_GPIO_PORT_COL, &GPIO_InitStructure);	

		
}


/*********************************************END OF FILE**********************/
