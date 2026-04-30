//#include <REGX52.H>		//51引用
#include "xunji.h"
//#include <intrins.h>	//51引用

#include "main.h"

#include "stm32f1xx_hal.h"  // 根据你的型号选择：f1/f4/f7...【采用滴答时钟获取一微秒（暂时没用上）】
#include "core_cm3.h"       // STM32F1 用 core_cm3.h【采用滴答时钟获取一微秒（暂时没用上）】

unsigned short temp_left_w=0,temp_right_w=0;//左右循迹值各16位
short WuCha_Munber=0,temp_abs=0;
unsigned short Temp_Left[8],Temp_Right[8];		//存储循迹模块读取的值，因为只用了一个16路，分两段所以一个数组存8个
unsigned char LED_left=0;//左右循迹识别到的数
unsigned char LED_right=0;





/*************************************************

功能：读取循迹模块的值20ms进入

**************************************************/

/*		//通过滴答时钟中断读取一微秒，但因为与基础定时器冲突且优先级过高，暂时没用上
启用DWT时钟
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;  // 使能 DWT
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;             // 使能 CYCCNT 计数
  DWT->CYCCNT = 0;                                 // 清零计数器
*/

void Delay_us(uint32_t us)		//通过滴答时钟中断读取一微秒，但因为与基础定时器冲突且优先级过高，暂时没用上
{
    uint32_t start = DWT->CYCCNT;
    uint32_t cycles = us * 72;  // 72MHz → 72 cycles per us

    // 等待达到指定周期数
    while ((DWT->CYCCNT - start) < cycles)
    {
        __NOP();  // 可选：防止编译器优化
    }
}

void DDelay_us(void)		//循迹模块的芯片时序要求了一微秒的延时，不会，只能执行几个无意义函数体达到延时效果
{
	__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();
	
}

/*获取循迹值，该循迹模块是并行输入串行输出*/
void Inrared_Get(void)
{
	unsigned short temp_left=0,temp_right=0,LED_left=0,LED_right=0;
	int i=0;
	
	/*一次性获取循迹模块上读取的数值*/
	CLR_left_SH;
	
	DDelay_us();
	
	SET_left_SH;
	
	DDelay_us();
	
/*通过for循环一位一位地推送循迹值给单片机*/
	for(i=0; i<16; i++)
	{
		CLR_left_CL;
		
		if(i>8)		//因为只有一个16路循迹模块，所以后8位当作右边读数
		{			
			if(left_DA_GET()==1)			//**可能如果这个引脚输入进来的是1就执行，left_DA_GET()是读取引脚    0是亮1是灭最左边是第一个进来的
			{
				temp_right|=(0x01<<i);		//**可能读取到1也就是识别到（或没识别到）则把temp_right那一位为1
				LED_right++;				//**可能亮着的灯数加一，没识别到灯是亮的由上temp_right|=(0x01<<i)推理得没识别到的为1取代原来的0，而识别到黑线传给单片机的是0 ，但本来就是0
			}
		}
		if(i<7)		//因为只有一个16路循迹模块，所以前8位当作佐边读数
		{
			if(left_DA_GET()==1)
			{
				temp_left|=(0x01<<i);
				LED_left++;
			}
		}
		
		DDelay_us();

		SET_left_CL;

		DDelay_us();
	}
	temp_left_w = temp_left;//0000 0000 0000 0001
	temp_right_w = temp_right;//1000 0000 0000 0000
	
}

/*************************************************************

功能：设置循迹模块的权重//左边第一个不要//右边最后一个不要
     1000 0000 0000 0000 | 0000 0000 0000 0001

设置：中间两个循迹权重是0，当识别到时不予理会，往两边权重慢慢加大
      权重越大，要转的角度就越大

**************************************************************/

void XunJi_Jugde(void)
{
	int i;
	WuCha_Munber=0;
	for(i=1;i<=7;i++)
	{
		if(temp_left_w&0x80>>i)
		{
		  WuCha_Munber-=i*1;
		}
		if(temp_right_w&0x100<<i)
		{
		  WuCha_Munber+=i*1;
		}
	}
}




// 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16


/*
单循迹
Inrared_Get()取值时
if(i!=8||i!=9)
		{
			if(right_DA_GET()==1)
			{
				temp_left|=(0x01<<i);
				LED_left++;
			}
		}
*/

