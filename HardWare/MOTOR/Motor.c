#include "Motor.h"
void Motor_Init(){
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//先使能外设IO PORTC时钟 
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_2|GPIO_Pin_3;	 // 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIO 
	
  GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_2|GPIO_Pin_3);	
  TIM1_PWM_Init();
}
void Motor_Set_Current(float C1,float C2){ //对应电机1和电机2,上限50，可正可负
	int Current1=(int)C1;
	int Current2=(int)C2;
	if(Current1>999) Current1=999;
	if(Current1<-999) Current1=-999;
	
	if(Current2>999) Current2=999;
	if(Current2<-999) Current2=-999;
	
	if(Current1==0){
		AIN1=0;
		AIN2=0;
	}
	else if(Current1>0){
		AIN1=1;
		AIN2=0;
		PWM_CH1_DUTY_CYCLE=Current1;
	}
	else if(Current1<0){
		AIN1=0;
		AIN2=1;
		PWM_CH1_DUTY_CYCLE=-Current1;
	}
	if(Current2==0){
		BIN1=0;
		BIN2=0;
	}
	else if(Current2>0){
		BIN1=1;
		BIN2=0;
		PWM_CH4_DUTY_CYCLE=Current2;
	}
	else if(Current2<0){
		BIN1=0;
		BIN2=1;
		PWM_CH4_DUTY_CYCLE=-Current2;
	}
}
