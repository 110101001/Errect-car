#include "pid.h"
#include "usart.h"

//#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
//#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
//#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
//#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

//u8 data_to_send[256];

float absf(float x){return (x>0)?x:-x;}
float ValLimit(float x,float Limit)
{
if (x>Limit)x=Limit;
	else if(x<-Limit)x=-Limit;
	return x;
}
void Pid_calc(pid_struct *pid){
	//static long int time;
//	pid->output=pid->kp*((pid->ref-pid->fdb)+pid->kd*(pid->err[0]-pid->err[1])/(SEC_PER_CLK*(Get_time()-time))+pid->ki*pid->in);
	pid->output+=(pid->ref-pid->fdb)*pid->kp*(1+pid->ki+pid->kd)-pid->err[0]*pid->kp*(1+2*pid->kd)+pid->err[1]*pid->kp*pid->kd;
	pid->err[1]=pid->err[0];
	pid->err[0]=pid->ref-pid->fdb;
	pid->output=ValLimit(pid->output,pid->limit);
}

//void ANO_DT_Send_Senser(s16 a_x,s16 a_y,s16 a_z,s16 g_x,s16 g_y,s16 g_z,s16 m_x,s16 m_y,s16 m_z)
//{
//	u8 _cnt=0;
//	vs16 _temp;
//		u8 sum = 0;
//	u8 i;
//	data_to_send[_cnt++]=0xAA;
//	data_to_send[_cnt++]=0xAA;
//	data_to_send[_cnt++]=0x02;
//	data_to_send[_cnt++]=0;
//	
//	_temp = a_x;
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);
//	_temp = a_y;
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);
//	_temp = a_z;	
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);
//	
//	_temp = g_x;	
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);
//	_temp = g_y;	
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);
//	_temp = g_z;	
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);
//	
//	_temp = m_x;	
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);
//	_temp = m_y;	
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);
//	_temp = m_z;	
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);
///////////////////////////////////////////
//	_temp = 0;	
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);	
//	
//	data_to_send[3] = _cnt-4;
//	

//	for(i=0;i<_cnt;i++)
//		sum += data_to_send[i];
//	data_to_send[_cnt++] = sum;
//	
//	for(i=0;i<_cnt;i++) {
//		USART_SendData(USART1,*(data_to_send+i));
//		while((USART1->SR&0X40)==0);
//	}
//}
//void ANO_DT_Send_Status(float angle_rol, float angle_pit, float angle_yaw, s32 alt, u8 fly_model, u8 armed)
//{
//	u8 _cnt=0;
//	vs16 _temp;
//	vs32 _temp2 = alt;
//	u8 sum = 0;
//	u8 i;
//	data_to_send[_cnt++]=0xAA;
//	data_to_send[_cnt++]=0xAA;
//	data_to_send[_cnt++]=0x01;
//	data_to_send[_cnt++]=0;
//	
//	_temp = (int)(angle_rol*100);
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);
//	_temp = (int)(angle_pit*100);
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);
//	_temp = (int)(angle_yaw*100);
//	data_to_send[_cnt++]=BYTE1(_temp);
//	data_to_send[_cnt++]=BYTE0(_temp);
//	
//	data_to_send[_cnt++]=BYTE3(_temp2);
//	data_to_send[_cnt++]=BYTE2(_temp2);
//	data_to_send[_cnt++]=BYTE1(_temp2);
//	data_to_send[_cnt++]=BYTE0(_temp2);
//	
//	data_to_send[_cnt++] = fly_model;
//	
//	data_to_send[_cnt++] = armed;
//	
//	data_to_send[3] = _cnt-4;
//	

//	for(i=0;i<_cnt;i++)
//		sum += data_to_send[i];
//	data_to_send[_cnt++]=sum;
//	
//	for(i=0;i<_cnt;i++) {
//		USART_SendData(USART1,*(data_to_send+i));
//		while((USART1->SR&0X40)==0);
//	}
//}
