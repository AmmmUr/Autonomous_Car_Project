/*
 * DCM_Interface.h
 *
 * Created: 9/27/2022 10:48:43 AM
 *  Author: Ammar
 */ 


#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_

//Motor Number
#define DCM_MOTOR1     1 
#define DCM_MOTOR2     2
//Direction
#define DCM_CW         1
#define DCM_CCW        2

void DCM_Init(void);
void DCM_ON(u8 MotorNumber,u8 Direction);
void DCM_OFF(u8 MotorNumber);
//void DCM_ControlSpeedRatio(u8 Speed);


#endif /* DCM_INTERFACE_H_ */