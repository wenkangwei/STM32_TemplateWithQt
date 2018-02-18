

//******************************************************************************
//name:             GUA_Timer1_PWM.c
//introduce:        定时器1的PWM驱动
//author:           甜甜的大香瓜
//email:            897503845@qq.com
//QQ group          香瓜单片机之STM8/STM32(164311667)
//changetime:       2017.01.14
//******************************************************************************
#include "stm32f10x.h"
#include "gua_timer1_pwm.h"



/*********************内部函数声明************************/
static void GUA_Timer1_PWM_IO_Init(void);
static void GUA_Timer1_PWM_Config_Init(GUA_U16 nGUA_Timer3_PWM_Prescaler);

//******************************************************************************
//name:             GUA_Timer1_PWM_IO_Init
//introduce:        定时器1的PWM的IO初始化
//parameter:        none
//return:           none
//author:           甜甜的大香瓜
//email:            897503845@qq.com
//QQ group          香瓜单片机之STM8/STM32(164311667)
//changetime:       2017.01.14
//******************************************************************************
static void GUA_Timer1_PWM_IO_Init(void)
{
    //IO结构体
    GPIO_InitTypeDef GPIO_InitStructure;

    //时钟配置
    RCC_APB2PeriphClockCmd(GUA_TIMER1_PWM_GPIO_CLOCK, ENABLE);

    //IO初始化
    GPIO_InitStructure.GPIO_Pin = GUA_TIMER1_PWM_PIN;
    GPIO_InitStructure.GPIO_Mode = GUA_TIMER1_PWM_MODE;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GUA_TIMER1_PWM_PORT, &GPIO_InitStructure);
}

//******************************************************************************
//name:             GUA_Timer1_PWM_Config_Init
//introduce:        定时器1的PWM的配置初始化
//parameter:        nGUA_Timer1_PWM_Prescaler:预分频数值,如100则表示1000000/100=10000Hz
//return:           none
//author:           甜甜的大香瓜
//email:            897503845@qq.com
//QQ group          香瓜单片机之STM8/STM32(164311667)
//changetime:       2017.01.14
//******************************************************************************
static void GUA_Timer1_PWM_Config_Init(GUA_U16 nGUA_Timer1_PWM_Prescaler)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    //时钟配置
    RCC_APB2PeriphClockCmd(GUA_TIMER1_PWM_PERIPH_CLOCK, ENABLE);

    //定时器配置
    TIM_TimeBaseStructure.TIM_Period = GUA_TIMER1_PWM_PERIOD;                               //设置计数值
    TIM_TimeBaseStructure.TIM_Prescaler = nGUA_Timer1_PWM_Prescaler - 1;        //设置预分频
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                                                        //设置时钟分频系数：不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                         //向上计数溢出模式
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    //PWM配置
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                                               //配置为PWM模式1(小于计数值时为有效电平)
    //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                 //比较输出使能
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;                 //比较输出的互补输出使能
    TIM_OCInitStructure.TIM_Pulse = 0;                                                                          //设置待装入捕获比较寄存器的脉冲值
    //TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                          //当定时器计数值小于CCR1时为低电平
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;                          //当定时器计数值小于CCR1时互补输出为低电平
    //TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;                        //当MOE=0时，如果实现了OC*N，则死区后OC*=1
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;                        //当MOE=0时，如果实现了OC*N，则死区后OC*=1
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);                                                                //使能通道2

    //默认关闭PWM
    GUA_Timer1_PWM_Status(GUA_TIMER1_PWM_STATUS_OFF);

    //使能
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);                                               //CH2预装载使能
    TIM_ARRPreloadConfig(TIM1, ENABLE);                                                                         //使能TIM1重载寄存器ARR
    TIM_Cmd(TIM1, ENABLE);                                                                                                  //使能定时器1
}

//******************************************************************************
//name:             GUA_Timer1_PWM_Status
//introduce:        定时器1的PWM开关
//parameter:        nGUA_Timer1_PWM_Status: GUA_TIMER1_PWM_STATUS_ON or GUA_TIMER1_PWM_STATUS_OFF
//return:           none
//author:           甜甜的大香瓜
//email:            897503845@qq.com
//QQ group          香瓜单片机之STM8/STM32(164311667)
//changetime:       2017.01.14
//******************************************************************************
void GUA_Timer1_PWM_Status(GUA_U8 nGUA_Timer1_PWM_Status)
{
  //打开PWM
  if(nGUA_Timer1_PWM_Status == GUA_TIMER1_PWM_STATUS_ON)
  {
        TIM_SetCounter(TIM1, 0);
        TIM_CtrlPWMOutputs(TIM1, ENABLE);
  }
  //关闭PWM
  else
  {
        TIM_CtrlPWMOutputs(TIM1, DISABLE);
  }
}

//******************************************************************************
//name:             GUA_Timer1_PWM_SetDutyCycle
//introduce:        定时器1的PWM设置占空比
//parameter:        nGUA_Timer1_PWM_DutyCycle: 0~100为0%~100%
//return:           none
//author:           甜甜的大香瓜
//email:            897503845@qq.com
//QQ group          香瓜单片机之STM8/STM32(164311667)
//changetime:       2017.01.14
//******************************************************************************
void GUA_Timer1_PWM_SetDutyCycle(GUA_U8 nGUA_Timer1_PWM_DutyCycle)
{
  TIM_SetCompare2(TIM1, GUA_TIMER1_PWM_PERIOD*nGUA_Timer1_PWM_DutyCycle/100);
}

//******************************************************************************
//name:             GUA_Timer1_PWM_Init
//introduce:        定时器1的PWM初始化
//parameter:        nGUA_Timer1_PWM_Prescaler:预分频数值,如100则表示1000000/100=10000Hz
//return:           none
//author:           甜甜的大香瓜
//email:            897503845@qq.com
//QQ group          香瓜单片机之STM8/STM32(164311667)
//changetime:       2017.01.14
//******************************************************************************
void GUA_Timer1_PWM_Init(GUA_U16 nGUA_Timer1_PWM_Prescaler)
{
    //初始化IO
    GUA_Timer1_PWM_IO_Init();

    //初始化定时器配置
    GUA_Timer1_PWM_Config_Init(nGUA_Timer1_PWM_Prescaler);
}

