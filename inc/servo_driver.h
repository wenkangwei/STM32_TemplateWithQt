#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H
#include "stm32f10x.h"

void Servo_Cmd();
uint16_t  get_CValfromAngle(uint16_t angle);
void Servo_set_angle(uint16_t angle);


#endif // SERVO_DRIVER_H

