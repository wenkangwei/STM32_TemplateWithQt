
//******************************************************************************
//name:             GUA_Timer1_PWM.h
//introduce:        定时器1的PWM驱动的头文件
//author:           甜甜的大香瓜
//email:            897503845@qq.com
//QQ group          香瓜单片机之STM8/STM32(164311667)
//changetime:       2017.01.14
//******************************************************************************
#ifndef _GUA_TIMER1_PWM_H_
#define _GUA_TIMER1_PWM_H_

/*********************宏定义************************/
//类型宏
#ifndef GUA_U8
typedef unsigned char GUA_U8;
#endif

#ifndef GUA_8
typedef signed char GUA_8;
#endif

#ifndef GUA_U16
typedef unsigned short GUA_U16;
#endif

#ifndef GUA_16
typedef signed short GUA_16;
#endif

#ifndef GUA_U32
typedef unsigned long GUA_U32;
#endif

#ifndef GUA_32
typedef signed long GUA_32;
#endif

#ifndef GUA_U64
typedef unsigned long long GUA_U64;
#endif

#ifndef GUA_64
typedef signed long long GUA_64;
#endif


/*********************宏定义************************/
//引脚宏
#define GUA_TIMER1_PWM_PORT             GPIOB
#define GUA_TIMER1_PWM_PIN              GPIO_Pin_14
#define GUA_TIMER1_PWM_MODE             GPIO_Mode_AF_PP
#define GUA_TIMER1_PWM_GPIO_CLOCK               RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO
#define GUA_TIMER1_PWM_PERIPH_CLOCK         RCC_APB2Periph_TIM1

//计数值
#define GUA_TIMER1_PWM_PERIOD                       (72 - 1)


//PWM的开关宏
#define GUA_TIMER1_PWM_STATUS_ON                0       //PWM打开
#define GUA_TIMER1_PWM_STATUS_OFF               1       //PWM关闭

/*********************外部函数声明************************/
void GUA_Timer1_PWM_Status(GUA_U8 nGUA_Timer1_PWM_Status);
void GUA_Timer1_PWM_SetDutyCycle(GUA_U8 nGUA_Timer1_PWM_DutyCycle);
void GUA_Timer1_PWM_Init(GUA_U16 nGUA_Timer1_PWM_Prescaler);



#endif // GUA_TIMER1_PWM_H

