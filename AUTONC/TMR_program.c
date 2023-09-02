/*
 * TMR_program.c
 *
 * Created: 9/25/2022 5:55:55 AM
 *  Author: Mohamed Nabil 
 */ 

		/* UTILS */
#include "TYPE_DEF.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"


		/* MCAL */
#include "TMR_interface.h"
#include "TMR_config.h"



static void(*TMR_timer0_OVF_pCallBack)(void) = NULL;
static void(*TMR_timer0_CTC_pCallBack)(void) = NULL;


static void(*TMR_timer1_OVF_pCallBack)(void) = NULL;
static void(*TMR_timer1_CTC_pCallBack)(void) = NULL;

volatile static u16 TMR_ICU_onPeriod,TMR_ICU_offPeriod;




/***************************************************************************************************************/
/*                                                                                                             */
/***************************************************************************************************************/


					/*TIMER 0*/



void TMR_timer0init(void)
{ 

#if TMR_TMR0_MODE == TMR_TMR0_NORMAL_MODE
//Select Mode = Normal Mode
CLR_BIT(TCCR0,3);
CLR_BIT(TCCR0,6);

//Set Preload value
TCNT0 = TMR_TMR0_PRELOAD_VALUE;

//Enable OVF0 Interrupt 
SET_BIT(TIMSK,0);

#elif TMR_TMR0_MODE == TMR_TMR0_CTC_MODE

//Select Mode = CTC Mode
SET_BIT(TCCR0,3);
CLR_BIT(TCCR0,6);

//Enable CTC Interrupt
SET_BIT(TIMSK,1);

#elif TMR_TMR0_MODE == TMR_TMR0_FAST_PWM_MODE

//Select Mode = FAST PWM MODE 
SET_BIT(TCCR0,3);
SET_BIT(TCCR0,6); 

//Select PWM MODE = Non Inverting (set on top /clear on compare match)
SET_BIT(TCCR0,5);
CLR_BIT(TCCR0,4);

#endif

}


void TMR_timer0start(void)
{
#if TMR_TMR0_PRESCALER_FACTOR == TMR_TMR0_PRESCALER_1

//Set Prescaller Value = controller input Frequency
SET_BIT(TCCR0,0);
CLR_BIT(TCCR0,1);
CLR_BIT(TCCR0,2);

#elif TMR_TMR0_PRESCALER_FACTOR == TMR_TMR0_PRESCALER_8	 

//Set Prescaller Value = 8
CLR_BIT(TCCR0,0);
SET_BIT(TCCR0,1);
CLR_BIT(TCCR0,2);
								   
#elif TMR_TMR0_PRESCALER_FACTOR == TMR_TMR0_PRESCALER_64	  

//Set Prescaller Value = 64
SET_BIT(TCCR0,0);
SET_BIT(TCCR0,1);
CLR_BIT(TCCR0,2);
								   
#elif TMR_TMR0_PRESCALER_FACTOR == TMR_TMR0_PRESCALER_256	 

//Set Prescaller Value = 256
CLR_BIT(TCCR0,0);
CLR_BIT(TCCR0,1);
SET_BIT(TCCR0,2);
								   
#elif TMR_TMR0_PRESCALER_FACTOR == TMR_TMR0_PRESCALER_1024	 

//Set Prescaller Value = 1024
SET_BIT(TCCR0,0);
CLR_BIT(TCCR0,1);
SET_BIT(TCCR0,2);
								   
#elif TMR_TMR0_PRESCALER_FACTOR == TMR_TMR0_PRESCALER_EXT_FE 

//Set Prescaller to External clock source on T0 pin. Clock on falling edge.
CLR_BIT(TCCR0,0);
SET_BIT(TCCR0,1);
SET_BIT(TCCR0,2);
								   
#elif TMR_TMR0_PRESCALER_FACTOR == TMR_TMR0_PRESCALER_EXT_RE 

//Set Prescaller to External clock source on T0 pin. Clock on rising edge.
SET_BIT(TCCR0,0);
SET_BIT(TCCR0,1);
SET_BIT(TCCR0,2);



#endif
	
}

void TMR_timer0stop(void)
{
//Set Prescaller bits = 000
CLR_BIT(TCCR0,0);
CLR_BIT(TCCR0,1);
CLR_BIT(TCCR0,2);	
}



void TMR_timer0SetCompareMatchValue(u8 OCR0_Value )
{
//	init timer HARDWARE with compare value [Output Compare REG]
OCR0 = OCR0_Value;
}

void TMR_timer0_OVF_setCallBack(void(*ptr)(void))
{
	if (ptr!=NULL)
	{
		TMR_timer0_OVF_pCallBack=ptr;
	}
}


void TMR_timer0_CTC_setCallBack(void(*ptr)(void))
{
if (ptr!=NULL)
{
	TMR_timer0_CTC_pCallBack=ptr;
}	

}




				/* ISR Functions */


// ISR Function Prototype for Timer0 OVF
void __vector_11(void) __attribute__ ((signal));
void __vector_11(void)
{
static u16 counterOVF=0;
counterOVF++;
if (TMR_TMR0_OVF_COUNTER == counterOVF)
{
//Set Preload value
TCNT0 = TMR_TMR0_PRELOAD_VALUE;

//reset counter 
counterOVF =0;	

	//call action
if (TMR_timer0_OVF_pCallBack!=NULL)
{
	TMR_timer0_OVF_pCallBack();
}

}
}


// ISR Function Prototype for Timer0 CTC
void __vector_10(void) __attribute__ ((signal));
void __vector_10(void)
{
static u16 counterCTC= 0;
counterCTC++;
if (TMR_TMR0_CTC_COUNTER == counterCTC)
{
	//reset counter
	counterCTC =0;


if (TMR_timer0_CTC_pCallBack!=NULL)
{			   
	TMR_timer0_CTC_pCallBack();
}

}
}


/***************************************************************************************************************/
/*                                                                                                             */
/***************************************************************************************************************/							


						
					/*TIMER 1*/
		
		
void TMR_timer1init(void)
{
#if TMR_TMR1_MODE == TMR_TMR1_NORMAL_MODE	

//Select Mode = Normal Mode  [MODE 0]
CLR_BIT(TCCR1A,0);
CLR_BIT(TCCR1A,1);
CLR_BIT(TCCR1B,3);
CLR_BIT(TCCR1B,4);

//Set Preload value
TCNT1_u16 = TMR_TMR1_PRELOAD_VALUE;

//Enable OVF1 Interrupt
SET_BIT(TIMSK,2);	
	
#elif TMR_TMR1_MODE == TMR_TMR1_CTC_MODE	

//Select Mode = CTC Mode  [MODE 4] TOP -->OCR1A
CLR_BIT(TCCR1A,0);
CLR_BIT(TCCR1A,1);
SET_BIT(TCCR1B,3);
CLR_BIT(TCCR1B,4);


//Timer1, Output Compare A Match Interrupt Enable
SET_BIT(TIMSK,4);

	
#elif TMR_TMR1_MODE == TMR_TMR1_FAST_PWM_MODE

//Select Mode = FAST PWM MODE  [MODE 14]
CLR_BIT(TCCR1A,0);
SET_BIT(TCCR1A,1);
SET_BIT(TCCR1B,3);
SET_BIT(TCCR1B,4);	

//Select PWM MODE = Non Inverting (set on top /clear on compare match) COM pins
CLR_BIT(TCCR1A,6);
SET_BIT(TCCR1A,7);

//ICR1 SET >> DESIRED OVF VALUE (ticks) 
ICR1_u16 = TMR_TMR1_OVF_VALUE;

#endif

}

void TMR_timer1start(void)
{
#if TMR_TMR1_PRESCALER_FACTOR == TMR_TMR1_PRESCALER_1

//Set Prescaller Value = controller input Frequency
SET_BIT(TCCR1B,0);
CLR_BIT(TCCR1B,1);
CLR_BIT(TCCR1B,2);

#elif TMR_TMR1_PRESCALER_FACTOR == TMR_TMR1_PRESCALER_8

//Set Prescaller Value = 8
CLR_BIT(TCCR1B,0);
SET_BIT(TCCR1B,1);
CLR_BIT(TCCR1B,2);

#elif TMR_TMR1_PRESCALER_FACTOR == TMR_TMR1_PRESCALER_64

//Set Prescaller Value = 64
SET_BIT(TCCR1B,0);
SET_BIT(TCCR1B,1);
CLR_BIT(TCCR1B,2);

#elif TMR_TMR1_PRESCALER_FACTOR == TMR_TMR1_PRESCALER_256

//Set Prescaller Value = 256
CLR_BIT(TCCR1B,0);
CLR_BIT(TCCR1B,1);
SET_BIT(TCCR1B,2);

#elif TMR_TMR1_PRESCALER_FACTOR == TMR_TMR1_PRESCALER_1024

//Set Prescaller Value = 1024
SET_BIT(TCCR1B,0);
CLR_BIT(TCCR1B,1);
SET_BIT(TCCR1B,2);

#elif TMR_TMR1_PRESCALER_FACTOR == TMR_TMR1_PRESCALER_EXT_FE

//Set Prescaller to External clock source on T0 pin. Clock on falling edge.
CLR_BIT(TCCR1B,0);
SET_BIT(TCCR1B,1);
SET_BIT(TCCR1B,2);

#elif TMR_TMR1_PRESCALER_FACTOR == TMR_TMR1_PRESCALER_EXT_RE

//Set Prescaller to External clock source on T0 pin. Clock on rising edge.
SET_BIT(TCCR1B,0);
SET_BIT(TCCR1B,1);
SET_BIT(TCCR1B,2);



#endif
		
}

void TMR_timer1stop(void)
{
//No clock source (Timer/Counter stopped).
CLR_BIT(TCCR1B,0);
CLR_BIT(TCCR1B,1);
CLR_BIT(TCCR1B,2);	
}

void TMR_timer1SetCompareMatchAValue(u16 OCR1A_Value )
{	
		//Init timer with Compare value	
	
OCR1A_u16 =	OCR1A_Value;
}


void TMR_timer1SetCompareMatchBValue(u16 OCR1B_Value )
{
		//Init timer with Compare value

OCR1B_u16 = OCR1B_Value;	
}


/********#####*********/


void TMR_timer1_OVF_setCallBack(void(*ptr)(void))
{
	if (ptr!=NULL)
	{
		TMR_timer1_OVF_pCallBack=ptr;
	}
	
}


void TMR_timer1_CTC_setCallBack(void(*ptr)(void))
{
	if (ptr!=NULL)
	{
		TMR_timer1_CTC_pCallBack = ptr;
	}

}





/********ISR FUNCTIONS FOR TIMER 1*********/

// ISR Function Prototype for Timer1 OVF
void __vector_9(void) __attribute__ ((signal));
void __vector_9(void)
{
	static u16 counterOVF=0;
	counterOVF++;
	if (TMR_TMR1_OVF_COUNTER == counterOVF)
	{
		//Set Preload value
		TCNT0 = TMR_TMR0_PRELOAD_VALUE;

		//reset counter
		counterOVF =0;

		//call action
		if (TMR_timer1_OVF_pCallBack!=NULL)
		{
			TMR_timer1_OVF_pCallBack();
		}

	}
}


// ISR Function Prototype for Timer1 Compare Match A in CTC
void __vector_7(void) __attribute__ ((signal));
void __vector_7(void)
{
	static u16 counterCTC= 0;
	counterCTC++;
	if (TMR_TMR1A_CTC_COUNTER == counterCTC)
	{
		//reset counter
		counterCTC =0;


		if (TMR_timer1_CTC_pCallBack!=NULL)
		{
			TMR_timer1_CTC_pCallBack();
		}

	}
}




/* ICU */
void TMR_ICU_init(void)
{
//Select Mode = Normal Mode  [MODE 0]
CLR_BIT(TCCR1A,0);
CLR_BIT(TCCR1A,1);
CLR_BIT(TCCR1B,3);
CLR_BIT(TCCR1B,4);

// select starting edge source of ICP1 interrupt
#if TMR_ICU_STARTING_EDGE == TMR_ICU_RISING_EDGE
	SET_BIT(TCCR1B,6);
#elif TMR_ICU_STARTING_EDGE == TMR_ICU_FALLING_EDGE
	CLR_BIT(TCCR1B,6);
#endif

	// activate ICU interrupt
SET_BIT(TIMSK,5);

	// Select Prescaler Value = 64
	//NOTE: ONCE WE SET PRESCALER VALUE TIMER STARTS TO COUNT TIME
	SET_BIT(TCCR1B,0);
	SET_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
}

void TMR_ICU_getTotalPeriod(u32* totalPeriod)
{
if (totalPeriod != NULL)
{
*totalPeriod = (u32)(TMR_ICU_onPeriod + TMR_ICU_offPeriod);
}
	
}

void TMR_ICU_getDutyCycle(u8* dutyCycle)
{
	if (dutyCycle != NULL)
	{
*dutyCycle= (u8)((TMR_ICU_onPeriod*100)/(TMR_ICU_onPeriod + TMR_ICU_offPeriod));	
	
	}
	
}

// ISR Function protoType for TMR1 ICU
void __vector_6(void) __attribute__ ((signal));
void __vector_6(void)
{
	
	static u8  flag = TMR_ICU_STARTING_EDGE;
	static u16 oldValue = 0;
	static u16 CounterValue;
	
	/* Read ICR1 value*/
	CounterValue = ICR1_u16;
	
	if (flag == TMR_ICU_RISING_EDGE) //calculate off period
	{
		TMR_ICU_offPeriod = (CounterValue - oldValue)*4;
		// change edge source of ICP1 interrupt to falling edge
		CLR_BIT(TCCR1B,6);
		// change flag value
		flag = TMR_ICU_FALLING_EDGE;
	}
	else if (flag == TMR_ICU_FALLING_EDGE) //calculate on period
	{
		TMR_ICU_onPeriod = (CounterValue - oldValue)*4;
		// change edge source of ICP1 interrupt to rising edge
		SET_BIT(TCCR1B,6);
		// change flag value
		flag = TMR_ICU_RISING_EDGE;
	}
	// Old value update
	oldValue = CounterValue;


}


					/*TIMER 2*/
					
					
void TMR_timer2init(void)
{
	
	//Select Mode = FAST PWM MODE  [MODE 3]
	SET_BIT(TCCR2,3);
	SET_BIT(TCCR2,6);

	//Select PWM MODE = Non Inverting (set on top /clear on compare match) COM pins
	CLR_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);

}

void TMR_timer2start(void)
{
	//clkT2S/64 (From prescaler)
	CLR_BIT(TCCR2,0);
	CLR_BIT(TCCR2,1);
	SET_BIT(TCCR2,2);
}

void TMR_timer2stop(void)
{
	//No clock source (Timer/Counter stopped).
	CLR_BIT(TCCR2,0);
	CLR_BIT(TCCR2,1);
	CLR_BIT(TCCR2,2);
}

void TMR_timer2SetCompareMatchValue(u8 OCR2_Value )
{
	//Init timer with Compare value
	
	OCR2 = OCR2_Value;
}