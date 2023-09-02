/*
 * AUTONC_Interface.h
 *
 * Created: 10/20/2022 7:26:02 PM
 *  Author: NoUr MD
 */ 


#ifndef AUTONC_INTERFACE_H_
#define AUTONC_INTERFACE_H_

#define AUTONC_STOP           0
#define AUTONC_FORWARD        1
#define AUTONC_BACKWARD       2
#define AUTONC_ROTATE_RIGHT   3
#define AUTONC_ROTATE_LEFT    4


void AUTONC_init(void);
void AUTONC_setMotorDirection(u8 Direction);



#endif /* AUTONC_INTERFACE_H_ */