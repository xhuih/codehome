#ifndef _PID_H
#define _PID_H

extern float Out,Target;
extern float Out_MPU,Target_MPU;

void pid(void);

void pid_MPU(float Actual);

float pid_Speed(float Target_Speed,int Actual_S);

#endif
