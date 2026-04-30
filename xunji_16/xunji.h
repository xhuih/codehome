#ifndef _xunji_H
#define _xunji_H
//#include "Task.h"

/*
P0 SH
P1 CLK
P2 DA
*/

/*
#define SET_left_SH DL_GPIO_setPins(TRACE_SH_L_PORT,TRACE_SH_L_PIN)//高
#define CLR_left_SH DL_GPIO_clearPins(TRACE_SH_L_PORT,TRACE_SH_L_PIN)//低
#define SET_left_CL DL_GPIO_setPins(TRACE_CL_L_PORT,TRACE_CL_L_PIN)//高
#define CLR_left_CL DL_GPIO_clearPins(TRACE_CL_L_PORT,TRACE_CL_L_PIN)//低
#define left_DA_GET()   ((DL_GPIO_readPins(TRACE_DA_L_PORT,TRACE_DA_L_PIN)>0)?1:0)

//Right定义
#define SET_right_SH DL_GPIO_setPins(TRACE_SH_R_PORT,TRACE_SH_R_PIN)//高
#define CLR_right_SH DL_GPIO_clearPins(TRACE_SH_R_PORT,TRACE_SH_R_PIN)//低
#define SET_right_CL DL_GPIO_setPins(TRACE_CL_R_PORT,TRACE_CL_R_PIN)//高
#define CLR_right_CL DL_GPIO_clearPins(TRACE_CL_R_PORT,TRACE_CL_R_PIN)//低
#define right_DA_GET()   ((DL_GPIO_readPins(TRACE_DA_R_PORT,TRACE_DA_R_PIN)>0)?1:0)

//51定义
#define SET_left_SH 	P0_0 = 1//高
#define CLR_left_SH 	P0_0 = 0//低
#define SET_left_CL 	P0_1 = 1//高
#define CLR_left_CL 	P0_1 = 0//低
#define left_DA_GET()   ((DL_GPIO_readPins(TRACE_DA_L_PORT,TRACE_DA_L_PIN)>0)?1:0)
*/



#define SET_left_SH HAL_GPIO_WritePin(SH_GPIO_Port,SH_Pin,GPIO_PIN_SET)//高
#define CLR_left_SH HAL_GPIO_WritePin(SH_GPIO_Port,SH_Pin,GPIO_PIN_RESET)//低
#define SET_left_CL HAL_GPIO_WritePin(CL_GPIO_Port,CL_Pin,GPIO_PIN_SET)//高
#define CLR_left_CL HAL_GPIO_WritePin(CL_GPIO_Port,CL_Pin,GPIO_PIN_RESET)//低
#define left_DA_GET()   ((HAL_GPIO_ReadPin(DA_GPIO_Port,DA_Pin)>0)?1:0)


extern unsigned char LED_left;
extern unsigned char LED_right;
extern unsigned short temp_left_w,temp_right_w;
extern  short WuCha_Munber,temp_abs;
void  Inrared_Get(void);
void XunJi_Jugde(void);
#endif 
