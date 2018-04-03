#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "inv_mpu.h"
#include "pid.h"
#include "Motor.h"
#include "Encoder.h"
#include "mpu6050.h"

#define ERECT_ERR 1

float pitch,yaw,roll;
pid_struct angle_pid={-142,0.05,0,{0,0},0,0,0,0,100000},
w_pid={1.0,0,0,{0,0},0,0,0,0,10000000},
w1_pid={-0.15,0,0,{0,0},0,0,0,0,100000};
//w2_pid={-0.18,0,0,{0,0},0,0,0,0,100000};
extern float w1,w2;

 int main(void){
	float Erect_Angle=0;
	short int gx,gy,gz;
	short int ax=ERECT_ERR+1,ay,az;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为9600
	 
	TIM4_Configuration();
	Quad_Encoder_Configuration1();
	Quad_Encoder_Configuration2();
	Encoder_Start1();
	Encoder_Start2();
	Motor_Init();
	delay_ms(10);
	while(MPU_Init());
	delay_ms(10);
	while(mpu_dmp_init());
	 
	while(pitch==0){
		mpu_dmp_get_data(&pitch,&roll,&yaw);
	}
	while(!(ax<ERECT_ERR&&ax>-ERECT_ERR)){
		MPU_Get_Accelerometer(&ax,&ay,&az);
		mpu_dmp_get_data(&pitch,&roll,&yaw);
	}
	Erect_Angle=pitch-1.3;
	
	while(1){
		mpu_dmp_get_data(&pitch,&roll,&yaw);
		MPU_Get_Gyroscope(&gx,&gy,&gz);
		Get_speed();
		if((pitch-Erect_Angle)>70||(pitch-Erect_Angle)<-70) break;
		angle_pid.fdb=pitch;
		angle_pid.ref=Erect_Angle;
		Pid_calc(&angle_pid);
		
		w_pid.ref=angle_pid.output;
		w_pid.fdb=-gy;
		Pid_calc(&w_pid);
		
		
		
		w1_pid.ref=w_pid.output;
		w1_pid.fdb=w1;
		Pid_calc(&w1_pid);
		
//		w2_pid.ref=w_pid.output;
//		w2_pid.fdb=w2;
//		Pid_calc(&w2_pid);
		
		Motor_Set_Current(w1_pid.output,-w1_pid.output);
		
		delay_ms(1);
		//ANO_DT_Send_Senser((s16)angle_pid.output,(s16)w_pid.output,0,gx,gy,gz,0,0,0);
		//ANO_DT_Send_Status(roll, pitch-Erect_Angle, yaw, 0, 0,0);
	}
	Motor_Set_Current(0,0);
 }
