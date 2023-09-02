/*
 * GI_Program.c
 *
 * Created: 9/18/2022 9:44:41 AM
 *  Author: NoUr MD
 */ 

//UTILES
#include "TYPE_DEF.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

//MCAL
#include "GI_Interface.h"

void GI_Enable  (void){
	SET_BIT(SREG,7);
}
void GI_Disable (void){
	CLR_BIT(SREG,7);
}