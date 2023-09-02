/*
 * AUTONC.c
 *
 * Created: 10/20/2022 7:23:37 PM
 * Author : NoUr MD
 */ 


#define F_CPU 16000000UL
#include <util/delay.h>

//UTILES
#include "TYPE_DEF.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

//MCAL
#include "DIO_Interface.h"
#include "TMR_Interface.h"
#include "GI_Interface.h"
#include "EXTI_Interface.h"

//HAL
#include "USS_Interface.h"
#include "LCD_Interface.h"
#include "DCM_Interface.h"
#include "Servo_Interface.h"

//APP
#include "AUTONC_Interface.h"

void STOP_Function(void);

int main(void)
{
	u32 distance,distanceRight,distanceLeft; // to get USS distances
	AUTONC_init(); // Directions and initialization modules
	GI_Enable();
	EXTI_INT0SetCallBack(&STOP_Function);// external interrupt to stop the program
	EXTI_Enable(EXTI_INT0,EXTI_FALLING_EDGE);// direct when pressing button 2 
	//Project Details 
	LCD_AmitSendString((u8*) " Autonomous Car");
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	LCD_AmitSendString((u8*) " Final Project");
	_delay_ms(1000);
	LCD_clear();
	LCD_AmitSendString((u8*) " Group Members:");
	_delay_ms(1000);
	LCD_clear();
	LCD_AmitSendString((u8*) "-Ammar Mahmoud");
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	LCD_AmitSendString((u8*) "-Mahmoud Tahoun");
	_delay_ms(1000);
	LCD_clear();
	LCD_AmitSendString((u8*) "-Mohamed ElSayed");
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	LCD_AmitSendString((u8*) "-Mohammed Khalid");
	_delay_ms(1000);
	LCD_clear();
//Start
Move:
	USS_GetDistance(&distance);
	while(distance>=30){
		AUTONC_setMotorDirection(AUTONC_FORWARD);
		LCD_clear();
		USS_GetDistance(&distance);	
		LCD_AmitSendString((u8*)"Nearest obj. after:");
		LCD_writeNumber(distance);
		LCD_AmitSendString((u8*)" cm (FWD)");
		//servo on right
		Servo_RotateDegree(30);//servo rotate right
		_delay_ms(50);
		AUTONC_setMotorDirection(AUTONC_STOP);// to control speed
		_delay_ms(100);// time for servo hardware rotate
		USS_GetDistance(&distanceRight);
		LCD_clear();
		LCD_AmitSendString((u8*)"Nearest obj. after:");
		LCD_writeNumber(distanceRight);
		LCD_AmitSendString((u8*)" cm (FWD)");
		//servo on center
		AUTONC_setMotorDirection(AUTONC_FORWARD);
		Servo_RotateDegree(0);//servo rotate to center
		_delay_ms(50);
		AUTONC_setMotorDirection(AUTONC_STOP);
		_delay_ms(100);
		USS_GetDistance(&distance);
		LCD_clear();
		LCD_AmitSendString((u8*)"Nearest obj. after:");
		LCD_writeNumber(distance);
		LCD_AmitSendString((u8*)" cm (FWD)");
		//servo on Left
		AUTONC_setMotorDirection(AUTONC_FORWARD);
		Servo_RotateDegree(-30);//servo rotate Left
		_delay_ms(50);
		AUTONC_setMotorDirection(AUTONC_STOP);
		_delay_ms(100);
		USS_GetDistance(&distanceLeft);
		LCD_clear();
		LCD_AmitSendString((u8*)"Nearest obj. after:");
		LCD_writeNumber(distanceLeft);
		LCD_AmitSendString((u8*)" cm (FWD)");
		
		Servo_RotateDegree(0);// servo back to center
		if((distanceRight>=distanceLeft)&&(distanceRight>=distance)){
			AUTONC_setMotorDirection(AUTONC_ROTATE_RIGHT);
			LCD_clear();
			LCD_AmitSendString((u8*)"Rotate Right -->");
			_delay_ms(300);
		}
		else if((distanceLeft>=distanceRight)&&(distanceLeft>=distance)){
			AUTONC_setMotorDirection(AUTONC_ROTATE_LEFT);
			LCD_clear();
			LCD_AmitSendString((u8*)"Rotate Left <--");
			_delay_ms(300);
		}
		else{
			
			//continue
		}

		AUTONC_setMotorDirection(AUTONC_STOP);// to control speed
		_delay_ms(200);// for LCD and repeatability and servo
		USS_GetDistance(&distance);	
	}
	
		USS_GetDistance(&distance);
		while(distance<30){
			AUTONC_setMotorDirection(AUTONC_BACKWARD);
			LCD_clear();
			USS_GetDistance(&distance);
			LCD_AmitSendString((u8*)"Nearest obj. after:");
			LCD_writeNumber(distance);
			LCD_AmitSendString((u8*)" cm (Back)");
			_delay_ms(200);
			AUTONC_setMotorDirection(AUTONC_STOP);
			USS_GetDistance(&distance);
			_delay_ms(500);
		}
		goto Move;

}
void STOP_Function(void){//force stop
	AUTONC_setMotorDirection(AUTONC_STOP);
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,3);
	LCD_AmitSendString((u8*)"Thank you");
	while(1){}
}

