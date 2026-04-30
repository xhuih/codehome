#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "Car.h"


unsigned char dir_Car;

void Set_SpeedB(float speed)
{
	
	if(dir_Car==0)		//正转	
	{
		HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);
	}
	
	if(speed>=0)
		{
			dir_Car = 0;
			speed = speed;
		}
		else
		{
			dir_Car = 1;
			speed = -speed;
		}
	
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,speed);
	
	
}

void Set_SpeedA(float speed)
{
	
	if(dir_Car==0)		//正转	
	{
		HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);
	}
	
	if(speed>=0)
		{
			dir_Car = 0;
			speed = speed;
		}
		else
		{
			dir_Car = 1;
			speed = -speed;
		}
	
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,speed);
}

/*读取编码器*/
int getTIMx_DetaCnt(TIM_HandleTypeDef *htim)
{
    int cnt;
//    cnt = htim->Instance->CNT;		//07fff
//    htim->Instance->CNT = 0;
	cnt = __HAL_TIM_GET_COUNTER(htim) - 0x7FFF;
	__HAL_TIM_SET_COUNTER(htim,0x7FFF);
    return cnt;
}



