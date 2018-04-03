#ifndef __Encoder_H__
#define __Encoder_H__
#include "sys.h"

#define SEC_PER_CLK 0.000001
#define ARC_PER_PLS 360/390.0

void TIM4_Configuration(void);
void Quad_Encoder_Configuration1(void);
void Encoder_Start1(void);
int32_t GetQuadEncoderDiff1(void);
void Quad_Encoder_Configuration2(void);
void Encoder_Start2(void);
int32_t GetQuadEncoderDiff2(void);
void TIM4_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
long int Get_time(void);
void Get_speed(void);
#endif
