#include "Motor.h"
void Motor_Init(){
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//��ʹ������IO PORTCʱ�� 
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_2|GPIO_Pin_3;	 // �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIO 
	
  GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_2|GPIO_Pin_3);	
  TIM1_PWM_Init();
}
void Motor_Set_Current(float C1,float C2){ //��Ӧ���1�͵��2,����50�������ɸ�
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
