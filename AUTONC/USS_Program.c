/*
 * USS_Program.c
 *
 * Created: 10/17/2022 10:02:34 PM
 *  Author: Ammar
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



#define F_CPU 16000000UL
#include <util/delay.h>


void USS_Init(void){
	

		DIO_SetPinDirection(USS_TriggerPort,USS_TriggerPin,DIO_PIN_OUTPUT);//trigger
		DIO_SetPinValue(USS_TriggerPort,USS_TriggerPin,DIO_PIN_LOW);
		DIO_SetPinDirection(USS_EchoPort,USS_EchoPin,DIO_PIN_INPUT);//echo
		DIO_SetPinValue(USS_EchoPort,USS_EchoPin,DIO_PIN_LOW);
		
        TMR_timer1init();

}


void USS_GetDistance(u32* Distance){
	
	    TCNT1_u16=0; 
        u8 Echo;
		u32 time;
        DIO_GetPinValue(USS_EchoPort,USS_EchoPin,&Echo);
	
		
		DIO_SetPinValue(USS_TriggerPort,USS_TriggerPin,DIO_PIN_HIGH);
		_delay_us(10);
		DIO_SetPinValue(USS_TriggerPort,USS_TriggerPin,DIO_PIN_LOW);
		
	    while(!Echo){DIO_GetPinValue(USS_EchoPort,USS_EchoPin,&Echo);}// block for echo = 0
			
		if(Echo){
			TMR_timer1start();
			DIO_GetPinValue(USS_EchoPort,USS_EchoPin,&Echo);
			while(Echo){DIO_GetPinValue(USS_EchoPort,USS_EchoPin,&Echo);}// block for echo = 1
			time=TCNT1_u16;// get time
			TMR_timer1stop();
			*Distance=(time*4*0.017);// convert time to cm
		}	
		
	}
		


