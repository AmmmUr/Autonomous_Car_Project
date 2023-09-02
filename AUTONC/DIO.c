/*
 * DIO.c
 *
 * Created: 9/6/2022 11:32:32 AM
 *  Author: Ammar
 */ 

//UTILES
#include "TYPE_DEF.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

//MCAL
#include "DIO_Interface.h"


void DIO_SetPinDirection(u8 PortId,u8 PinId,u8 PinDirction)
{
	if( (PortId<=3) && (PinId<=7) && ((PinDirction==DIO_PIN_INPUT) || (PinDirction==DIO_PIN_OUTPUT)) ){
	switch(PortId){
		case 0://DIO PORTA
		if(PinDirction==DIO_PIN_OUTPUT){
			SET_BIT(DDRA,PinId);
		}
		else{
			CLR_BIT(DDRA,PinId);
		}
		break;
	case 1://DIO PORTB
	if(PinDirction==DIO_PIN_OUTPUT){
		SET_BIT(DDRB,PinId);
	}
	else{
		CLR_BIT(DDRB,PinId);
	}
	break;
	case 2://DIO PORTC
	if(PinDirction==DIO_PIN_OUTPUT){
		SET_BIT(DDRC,PinId);
	}
	else{
		CLR_BIT(DDRC,PinId);
	}
	break;
	case 3://DIO PORTD
	if(PinDirction==DIO_PIN_OUTPUT){
		SET_BIT(DDRD,PinId);
	}
	else{
		CLR_BIT(DDRD,PinId);
	}
	break;
}
}
}


void DIO_SetPinValue (u8 PortId,u8 PinId,u8 PinValue){
		if( (PortId<=3) && (PinId<=7) && ((PinValue==DIO_PIN_HIGH) || (PinValue==DIO_PIN_LOW)) ){
				switch(PortId){
		           case 0://DIO PORTA
				   if(PinValue==DIO_PIN_HIGH){
					 	SET_BIT(PORTA,PinId); 
				   }
				   else{
					  		CLR_BIT(PORTA,PinId);
				   }
				   	break;

				   case 1://DIO PORTB
				   if(PinValue==DIO_PIN_HIGH){
					   SET_BIT(PORTB,PinId);
				   }
				   else{
					   CLR_BIT(PORTB,PinId);
				   }
				   	break;

				   case 2://DIO PORTC
				   if(PinValue==DIO_PIN_HIGH){
					   SET_BIT(PORTC,PinId);
				   }
				   else{
					   CLR_BIT(PORTC,PinId);
				   }
				   	break;

				   case 3://DIO PORTD
				   if(PinValue==DIO_PIN_HIGH){
					   SET_BIT(PORTD,PinId);
				   }
				   else{
					   CLR_BIT(PORTD,PinId);
				   }
				   	break;
				}
			
		}
}


void DIO_GetPinValue (u8 PortId,u8 PinId,u8* PinValue){
	if((PortId<=3) && (PinId<=7) && (PinValue!=NULL)){
		switch(PortId){
			case 0://DIO PORTA
			if(DIO_PIN_HIGH==GET_BIT(PINA,PinId)){
				*PinValue = DIO_PIN_HIGH;
			}
			else{
				*PinValue = DIO_PIN_LOW;
			}
			break;
			case 1://DIO PORTB
			if(DIO_PIN_HIGH==GET_BIT(PINB,PinId)){
				*PinValue = DIO_PIN_HIGH;
			}
			else{
				*PinValue = DIO_PIN_LOW;
			}
			break;
			case 2://DIO PORTC
			if(DIO_PIN_HIGH==GET_BIT(PINC,PinId)){
				*PinValue = DIO_PIN_HIGH;
			}
			else{
				*PinValue = DIO_PIN_LOW;
			}
			break;
			case 3://DIO PORTD
			if(DIO_PIN_HIGH==GET_BIT(PIND,PinId)){
				*PinValue = DIO_PIN_HIGH;
			}
			else{
				*PinValue = DIO_PIN_LOW;
			}
			break;
			
		}
	}
}


void DIO_TogglePinValue (u8 PortId,u8 PinId){
	if( (PortId<=3) && (PinId<=7)){
		switch(PortId){
			case 0://DIO PORTA
			TOG_BIT(PORTA,PinId);
			break;
			
			case 1://DIO PORTB
			TOG_BIT(PORTB,PinId);
			break;
			
			case 2://DIO PORTC
			TOG_BIT(PORTC,PinId);
			break;
			
			case 3://DIO PORTD
			TOG_BIT(PORTD,PinId);
			break;
		}
	}
}

void DIO_SetInputPinResistance(u8 PortId,u8 PinId){
	if((PortId<=3) && (PinId<=7)){
	switch(PortId){
	case 0:
	SET_BIT(PORTA,PinId);
	break;
	
	case 1:
	SET_BIT(PORTB,PinId);
	break;
	
	case 2:
	SET_BIT(PORTC,PinId);
	break;
	
	case 3:
	SET_BIT(PORTD,PinId);
	break;
	
	}
	}
}

void DIO_SetInputPortResistance(u8 PortId){
	if(PortId<=3){
		switch(PortId){
			case 0:
			PORTA = 0xff;
			break;
			
			case 1:
			PORTB = 0xff;
			break;
			
			case 2:
			PORTC = 0xff;
			break;
			
			case 3:
			PORTD = 0xff;
			break;
	}
	}
}


void DIO_SetPortDirection(u8 PortId,u8 PortDirction){
	if( (PortId<=3) && ((PortDirction==DIO_PORT_HIGH) || (PortDirction==DIO_PORT_LOW)) ){
		switch(PortId){
			case 0://DIO PORTA
			if(PortDirction==DIO_PORT_OUTPUT){
				DDRA = 0xff;
			}
			else{
				DDRA = 0x00;
			}
			break;
			case 1://DIO PORTB
			if(PortDirction==DIO_PORT_OUTPUT){
				DDRB = 0xff;
			}
			else{
				DDRB = 0x00;
			}
			break;
			case 2://DIO PORTC
			if(PortDirction==DIO_PORT_OUTPUT){
				DDRC = 0xff;
			}
			else{
				DDRC = 0x00;
			}
			break;
			case 3://DIO PORTD
			if(PortDirction==DIO_PORT_OUTPUT){
				DDRD = 0xff;
			}
			else{
				DDRD = 0x00;
			}
			break;
		}
		}
}

void DIO_SetPortValue (u8 PortId,u8 PortValue){
	if(PortId<=3){
		switch(PortId){
			case 0://DIO PORTA
			PORTA=PortValue;
			break;
			
			case 1://DIO PORTB
			PORTB=PortValue;
			break;
			
			case 2://DIO PORTC
			PORTC=PortValue;
			break;
			
			case 3://DIO PORTD
			PORTD=PortValue;
			break;
		}
	}
}

void DIO_GetPortValue (u8 PortId,u8*PortValue){
	if((PortId<=3) && (PortValue!=NULL)){
		switch(PortId){
			case 0://DIO PORTA
			*PortValue=PINA;
			break;
			
			case 1://DIO PORTB
			*PortValue=PINB;
			break;
			
			case 2://DIO PORTC
			*PortValue=PINC;
			break;
			
			case 3://DIO PORTD
			*PortValue=PIND;
			break;
		}
	}
	
}
void DIO_TogglePortValue (u8 PortId){
	if(PortId<=3){
		switch(PortId){
			case 0://DIO PORTA
			PORTA= (~PORTA);
			break;
			
			case 1://DIO PORTB
			PORTB= (~PORTB);
			break;
			
			case 2://DIO PORTC
			PORTC= (~PORTC);
			break;
			
			case 3://DIO PORTD
			PORTD= (~PORTD);
			break;
		}
	}
}