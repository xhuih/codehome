#include "main.h"	
#include "tim.h"

#include "xunji.h"

#include "IIC.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
#include "stdio.h"



float Target = 0,Out = 0;

float Out_MPU = 0,Target_MPU = 0;

float Out_Speed = 0,Target_Speed = 0;


/*循迹环，控制小车循迹*/
/*通过16路循迹模块获取误差值进行pid计算*/
void pid(void)
{
	static float Error0,Error1,ErrorInt;
	static float kp = 360,ki = 3.5,kd = 58;
	
		/*获取本次误差和上次误差*/
	Error1 = Error0;
//	Error0 = Target - Actual;
	Error0 = WuCha_Munber  ;
	
	/*误差积分(误差累加)*/
	ErrorInt += Error0;
	
	/*误差积分限幅(不一定用到)*/
	if(ErrorInt > 130){ErrorInt = 130;}
	if(ErrorInt < -130){ErrorInt = -130;}
	
	/*PID计算*/
	Out = kp * Error0 + ki * ErrorInt + kd * (Error0 - Error1);
	
	/*输出限幅*/
	if(Out > 7200){Out = 7200;}
	if(Out < -7200){Out = -7200;}
}

/*角度环，控制小车按一定角度行驶*/
/*Actual：实际角度，本次用MPU6050进行测试（不好用，老是④，也可能是哪里没用对）*/
void pid_MPU(float Actual)
{
	static float Error0_MPU,Error1_MPU,ErrorInt_MPU;
	static float kp = 160,ki = 0,kd = 10;
	
		/*获取本次误差和上次误差*/
	Error1_MPU = Error0_MPU;
	Error0_MPU = Target_MPU - Actual;
	
	/*误差积分(误差累加)*/
	ErrorInt_MPU += Error0_MPU;
	
	/*误差积分限幅(不一定用到)*/
	if(ErrorInt_MPU > 30){ErrorInt_MPU = 30;}
	if(ErrorInt_MPU < -30){ErrorInt_MPU = -30;}
	
	/*PID计算*/
	Out_MPU = kp * Error0_MPU + ki * ErrorInt_MPU + kd * (Error0_MPU - Error1_MPU);
	
	/*输出限幅*/
	if(Out_MPU > 7200){Out_MPU = 7200;}
	if(Out_MPU < -7200){Out_MPU = -7200;}
}




/*速度环，对电机进行定速控制*/
/*Target_Speed：目标速度    Actual_Speed：实际速度（用编码器对电机进行测速）*/
float pid_Speed(float Target_Speed,int Actual_Speed)
{
	static float Error0,Error1,ErrorInt;
	static float kp = 130,ki = 5,kd = 20;
	
		/*获取本次误差和上次误差*/
	Error1 = Error0;
	Error0 = Target_Speed - Actual_Speed;
	
	/*误差积分(误差累加)*/
	ErrorInt += Error0;
	
	/*误差积分限幅(不一定用到)*/
	if(ErrorInt > 200){ErrorInt = 200;}
	if(ErrorInt < -200){ErrorInt = -200;}
	
	/*PID计算*/
	Out_Speed = kp * Error0 + ki * ErrorInt + kd * (Error0 - Error1);
	
	/*输出限幅*/
	if(Out_Speed > 7200){Out_Speed = 7200;}
	if(Out_Speed < -7200){Out_Speed = -7200;}
	
	return  Out_Speed;
}
