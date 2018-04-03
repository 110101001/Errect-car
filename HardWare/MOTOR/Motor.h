#ifndef MOTOR_H
#define MOTOR_H

#include "sys.h"
#include "pwm.h"

#define AIN1 PAout(4)
#define AIN2 PAout(5)
#define BIN1 PAout(2)
#define BIN2 PAout(3)

void Motor_Init(void);
void Motor_Set_Current(float C1,float C2);

#endif
