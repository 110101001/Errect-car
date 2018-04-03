#include "Encoder.h"

//encoder.INPUT_B---PB4(TIM3_CH1)
//encoder.INPUT_A---PB5(TIM3_CH2)
float w1,w2;
float timer_count=0;

void TIM4_Configuration(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef tim;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    tim.TIM_Period = 0xFFFF;
    tim.TIM_Prescaler = 72 - 1;	 //1M 的时钟  
    tim.TIM_ClockDivision = TIM_CKD_DIV1;	
    tim.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_ARRPreloadConfig(TIM4, ENABLE);	
    TIM_TimeBaseInit(TIM4, &tim);
	
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM4, //TIM4
		TIM_IT_Update ,
		ENABLE  //使能
		);
	
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM5中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
		NVIC_Init(&NVIC_InitStructure);  

    TIM_Cmd(TIM4,ENABLE);	
}

void Quad_Encoder_Configuration1(void)
{
//	  TIM_TimeBaseInitTypeDef tim;
    GPIO_InitTypeDef gpio;
//		NVIC_InitTypeDef NVIC_InitStructure;
//		TIM_ICInitTypeDef TIM_ICInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

		gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
		gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA,&gpio);
	
//		TIM_DeInit(TIM2);
//    tim.TIM_Period = 0xFFFF;
//    tim.TIM_Prescaler = 84 - 1;	 //1M 的时钟  
//    tim.TIM_ClockDivision = TIM_CKD_DIV1;	
//    tim.TIM_CounterMode = TIM_CounterMode_Up;  
//    TIM_ARRPreloadConfig(TIM2, ENABLE);	
//    TIM_TimeBaseInit(TIM2, &tim);
//	
//		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM5中断
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//		NVIC_Init(&NVIC_InitStructure);  
	
    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
		
		
//		TIM_ICStructInit(&TIM_ICInitStructure);
//		TIM_ICInitStructure.TIM_ICFilter = 6;
//		TIM_ICInit(TIM2, &TIM_ICInitStructure);
//		
//		TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM3的更新标志位
//    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//运行更新中断
    TIM2->CNT = 0;//
		
    TIM_Cmd(TIM2,ENABLE);	 
}

void Encoder_Start1(void)
{
    TIM2->CNT = 0x7FFF;
}

static char Encoder_Dir1 = 0;
  
int32_t GetQuadEncoderDiff1(void)
{
    int32_t cnt = 0;    
    cnt = TIM2->CNT-0x7fff;
    TIM2->CNT = 0x7fff;    
    if(Encoder_Dir1 == 1)
	{
		return cnt;	
	}
	else
	{
		return -cnt;            
	}
}

void Quad_Encoder_Configuration2(void)
{
    GPIO_InitTypeDef gpio;
//		TIM_TimeBaseInitTypeDef tim;
//		TIM_ICInitTypeDef TIM_ICInitStructure;
//		NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

		gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOB,&gpio);
	
//		tim.TIM_Period = 0xFFFF;
//    tim.TIM_Prescaler = 84 - 1;	 //1M 的时钟  
//    tim.TIM_ClockDivision = TIM_CKD_DIV1;	
//    tim.TIM_CounterMode = TIM_CounterMode_Up;  
//    TIM_ARRPreloadConfig(TIM3, ENABLE);	
//    TIM_TimeBaseInit(TIM3, &tim);
//	
//		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM5中断
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//		NVIC_Init(&NVIC_InitStructure);  
		
		TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
//		TIM_ICStructInit(&TIM_ICInitStructure);
//		TIM_ICInitStructure.TIM_ICFilter = 6;
//		TIM_ICInit(TIM3, &TIM_ICInitStructure);
//		
//		TIM_ClearFlag(TIM3, TIM_FLAG_Update);//清除TIM3的更新标志位
//    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//运行更新中断
//    TIM3->CNT = 0;//
		
		TIM_Cmd(TIM3,ENABLE);	 
}

void Encoder_Start2(void)
{
    TIM3->CNT = 0x7FFF;
}

static char Encoder_Dir2 = 0;
  
int32_t GetQuadEncoderDiff2(void)
{
    int32_t cnt = 0;    
    cnt = TIM3->CNT-0x7FFF;
    TIM3->CNT = 0x7fff; 
    if(Encoder_Dir2 == 1)
	{
		return cnt;	
	}
	else
	{
		return -cnt;            
	}
}

void TIM4_IRQHandler(void){
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET){
		timer_count++;
	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );
}

void TIM2_IRQHandler(void){
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){
	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );
}

void TIM3_IRQHandler(void){
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){
	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );
}

long int Get_time(){
	return timer_count*0xFFFF+TIM4->CNT;
}

void Get_speed(){
	static long int time;
	w1=ARC_PER_PLS*GetQuadEncoderDiff1()/(SEC_PER_CLK*(Get_time()-time));
	w2=ARC_PER_PLS*GetQuadEncoderDiff2()/(SEC_PER_CLK*(Get_time()-time));
	time = Get_time();
}
