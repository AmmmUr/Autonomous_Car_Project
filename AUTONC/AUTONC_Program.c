/*
            ? ? ———————————————————————————————————————————————————————————————————??
        ? ??                        Autonomus Car                                      ???
       ? ?? 	       ????   Date        : 00/00/2022                    ????        ???
      ? ?? 	      ????    ?embers    : Ammar ?ahmoud ?ohammed	       ???? 	      ???
	 ? ??	    ????				   ?ohammed Khalid ?ohammed	        ????	        ???
	? ??		   ????				   ?ahmoud Hassan Abdullah		          ????	     ???
	? ?? 	   ????				   ?ohamed ElSayed Hussein		          ????	     ???
     ? ??	    ????   version     : 1.0                                 ????	        ???
      ? ?? 	      ????   SWC         :                                 ???? 	      ???
       ? ?? 	       ????   description :                              ????        ???
        ? ??                                                                          ???
            ? ?____________________________________________________________________??
		
*/


//UTILES
#include "TYPE_DEF.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

//MCAL
#include "DIO_Interface.h"
#include "TMR_Interface.h"


//HAL
#include "USS_Interface.h"
#include "USS_Config.h"
#include "LCD_Interface.h"
#include "LCD_Config.h"
#include "DCM_Interface.h"


//APP
#include "AUTONC_Interface.h"



void AUTONC_init(void){
	
	USS_Init();
	LCD_Start_AMIT();
	LCD_Init();
	DCM_Init();
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN7,DIO_PIN_OUTPUT);// servo PWM
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN3,DIO_PIN_OUTPUT);// BUZZER
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN2,DIO_PIN_OUTPUT);// Button  2
	
}

void AUTONC_setMotorDirection(u8 Direction){
	
	switch(Direction){
		
		case AUTONC_FORWARD:
		DCM_ON(DCM_MOTOR1,DCM_CW);
		DCM_ON(DCM_MOTOR2,DCM_CW);
		break;
		
		case AUTONC_BACKWARD:
		DCM_ON(DCM_MOTOR1,DCM_CCW);
		DCM_ON(DCM_MOTOR2,DCM_CCW);
		break;
		
		case AUTONC_ROTATE_RIGHT:
		DCM_ON(DCM_MOTOR1,DCM_CCW);
		DCM_ON(DCM_MOTOR2,DCM_CW);
		break;
		
		case AUTONC_ROTATE_LEFT:
		DCM_ON(DCM_MOTOR1,DCM_CW);
		DCM_ON(DCM_MOTOR2,DCM_CCW);
		break;
		
		case AUTONC_STOP:
		DCM_OFF(DCM_MOTOR1);
		DCM_OFF(DCM_MOTOR2);
		break;
			
	}
	
}


