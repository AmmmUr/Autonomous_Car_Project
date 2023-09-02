/*
 * TMR_interface.h
 *
 * Created: 9/25/2022 5:56:21 AM
 *  Author: Mohamed Nabil 
 */ 


#ifndef TMR_INTERFACE_H_
#define TMR_INTERFACE_H_


//TIMER 0 MODE MACROS
#define TMR_TMR0_NORMAL_MODE		1
#define TMR_TMR0_CTC_MODE			2
#define TMR_TMR0_FAST_PWM_MODE		3

//TIMER 0 PRESCALER MODE MACROS [CS0x pins]

#define TMR_TMR0_PRESCALER_1	  	    1	
#define TMR_TMR0_PRESCALER_8		    2
#define TMR_TMR0_PRESCALER_64	  	    3 
#define TMR_TMR0_PRESCALER_256		    4
#define TMR_TMR0_PRESCALER_1024		    5
#define TMR_TMR0_PRESCALER_EXT_FE	    6
#define TMR_TMR0_PRESCALER_EXT_RE		7

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//		

//TIMER 1 MODE MACROS
#define TMR_TMR1_NORMAL_MODE		0
#define TMR_TMR1_CTC_MODE			4
#define TMR_TMR1_FAST_PWM_MODE      14	

//TIMER 1 PRESCALER MODE MACROS [CS1x pins]

#define TMR_TMR1_PRESCALER_1	  	    1
#define TMR_TMR1_PRESCALER_8		    2
#define TMR_TMR1_PRESCALER_64	  	    3
#define TMR_TMR1_PRESCALER_256		    4
#define TMR_TMR1_PRESCALER_1024		    5
#define TMR_TMR1_PRESCALER_EXT_FE	    6
#define TMR_TMR1_PRESCALER_EXT_RE		7

//Timer 2
#define TMR_TMR2_PRELOAD_VALUE		0

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

//ICU MACROS

#define TMR_ICU_FALLING_EDGE         0
#define TMR_ICU_RISING_EDGE          1




		/*TIMER 0*/
		
void TMR_timer0init(void);
void TMR_timer0start(void);
void TMR_timer0stop(void);
// TMR0_NORMAL_MODE 
void TMR_timer0_OVF_setCallBack		(void(*ptr)(void));
// TMR0_CTC_MODE
void TMR_timer0SetCompareMatchValue (u8 OCR0_Value);
void TMR_timer0_CTC_setCallBack		(void(*ptr)(void));


		/*TIMER 1*/

void TMR_timer1init(void);
void TMR_timer1start(void);
void TMR_timer1stop(void);

void TMR_timer1SetCompareMatchAValue(u16 OCR1A_Value );
void TMR_timer1SetCompareMatchBValue(u16 OCR1B_Value );


void TMR_timer1_OVF_setCallBack		(void(*ptr)(void));
void TMR_timer1_CTC_setCallBack		(void(*ptr)(void));


					/*TIMER 2*/
					
					
void TMR_timer2init(void);
void TMR_timer2start(void);
void TMR_timer2stop(void);
void TMR_timer2SetCompareMatchValue(u8 OCR2_Value);



		/* ICU */
		
void TMR_ICU_init(void);
void TMR_ICU_getTotalPeriod(u32* totalPeriod);
void TMR_ICU_getDutyCycle(u8* dutyCycle);


#endif /* TMR_INTERFACE_H_ */