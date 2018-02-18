#include "servo_driver.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"



/**
 * @brief Servo_Cmd
 * @param none
 * @return none
 */

void Servo_Cmd()
{
    TIM1->CR1|=TIM_CR1_CEN;



}

/**
 * @brief get_CValfromAngle
 * @param angle from 0 degree to 180 degree
 * @return uint16_t
 */


uint16_t  get_CValfromAngle(uint16_t angle)
{
/*
 *parameter value from 0 to 180 match the impulse value from 1ms to 2ms
 *
*/
    float impulse;
    impulse=((float)angle*1000/180)+1000;    //angle value in ms
                //convert impluse to CCRx value, Clock frequency 1us
    return (uint16_t)impulse;

}

/**
 * @name Servo_set_angle();
 * @brief set the CCR1 value to control Servo angle
 *
 * */

void Servo_set_angle(uint16_t angle)
{
    angle= get_CValfromAngle(angle);        //get impulse value
    TIM1->CCR1=angle;                          //set impulse
//    angle=angle+PSC;                          //get updated PSC
//    TIM_PrescalerConfig(TIM1,angle,TIM_PSCReloadMode_Update);
}
