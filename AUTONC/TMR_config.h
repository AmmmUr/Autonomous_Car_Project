/*
 * TMR_config.h
 *
 * Created: 9/25/2022 5:56:33 AM
 *  Author: Mohamed Nabil 
 */ 


#ifndef TMR_CONFIG_H_
#define TMR_CONFIG_H_



			/*TIMER 0*/
			
/*
	[Timer 0 Modes] 
Options for Timer 0 mode:
1- TMR_TMR0_NORMAL_MODE  
2- TMR_TMR0_CTC_MODE
3- TMR_TMR0_FAST_PWM_MODE	  
*/

#define TMR_TMR0_MODE		TMR_TMR0_CTC_MODE

/*       	[Timer 0 Clock Select Mode]
*/
#define  TMR_TMR0_PRESCALER_FACTOR		TMR_TMR0_PRESCALER_64

/*
NORMAL MODE MACROS
*/
//in this calculation action is called after --> 1 second

#define TMR_TMR0_PRELOAD_VALUE		112
//counter of number of OVFs in ISR function  [set due to time calculations]
#define TMR_TMR0_OVF_COUNTER		977


/*
CTC MODE MACROS
*/
	//set to number of desired ms 
#define TMR_TMR0_CTC_COUNTER		1000 


/************************************************************************/
/*                                                                      */
/************************************************************************/
				
					/*TIMER 1*/

/*
	[Timer 1 Modes] 
Options for Timer 1 mode:
1- TMR_TMR1_NORMAL_MODE  
2- TMR_TMR1_CTC_MODE
3- TMR_TMR1_FAST_PWM_MODE	  
*/

#define TMR_TMR1_MODE		TMR_TMR1_NORMAL_MODE 

/*       	[Timer 1 Clock Select Mode]
*/
#define  TMR_TMR1_PRESCALER_FACTOR		TMR_TMR1_PRESCALER_64


/*
NORMAL MODE MACROS
*/
//in this calculation ISR action is called after --> 1 second

#define TMR_TMR1_PRELOAD_VALUE		0
//counter of number of OVFs in ISR function  [set due to time calculations]
#define TMR_TMR1_OVF_COUNTER		4


/*
CTC MODE MACROS
*/
	
	//set to number of desired ms
#define TMR_TMR1A_CTC_COUNTER		10    //you should set OCR1A to 25,000 tick here
	
#define TMR_TMR1B_CTC_COUNTER		10   ////you should set OCR1B to 25,000 tick here


	//MACRO FOR ICR1 REG VALUE [FAST_PWM_MODE]
#define TMR_TMR1_OVF_VALUE			4999    //20 ms ovf time


/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/* Options FOR ICU STARTING EDGE:
1- TMR_ICU_RISING_EDGE
2- TMR_ICU_FALLING_EDGE*/

#define TMR_ICU_STARTING_EDGE           TMR_ICU_RISING_EDGE








#endif /* TMR_CONFIG_H_ */