#ifndef _PWM_H_
#define _PWM_H_
#include "sys.h"

#define PERIOD 1000
#define PSC 71

#define PWM_CH1_DUTY_CYCLE TIM1->CCR1
#define PWM_CH4_DUTY_CYCLE TIM1->CCR4

#define PWM_CH1 PAout(8)
#define PWM_CH4 PAout(11)

void TIM1_PWM_Init(void);

#endif
