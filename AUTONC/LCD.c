/*
 * LCD.c
 *
 * Created: 9/11/2022 11:28:36 AM
 *  Author: Ammar
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

//UTILES
#include "TYPE_DEF.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

//MCAL
#include "DIO_Interface.h"

//HAL
#include "LCD_Interface.h"
#include "LCD_Config.h"

void LCD_Init (void){
	
	_delay_ms(35);
	
	#if LCD_MODE == LCD_8_BIT_MODE
	LCD_SendCom(0b00111000); // Function Set command 2*16 LCD
	#elif LCD_MODE == LCD_4_BIT_MODE
	// set Rs pin = 0 (write command)
	DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	// set Rw pin = 0 (write)
	DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);

	WriteHalfPort(0b0010);
	
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	LCD_SendCom(0b00101000);
	#endif
	_delay_us(45);
	// Display on off Control (DisplayOn, Cursor off, Blink off)
	LCD_SendCom(0b00001100);
	_delay_us(45);
	//Clear Display
	LCD_SendCom(0b00000001);
	_delay_ms(2);
	//Set Entry Mode
	LCD_SendCom(0b00000110);
	_delay_ms(2);

}

static void WriteHalfPort(u8 value){
	
	if(GET_BIT(value,0)==DIO_PIN_HIGH){
		DIO_SetPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_HIGH);
	}
	else{
		DIO_SetPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_LOW);
	}
	
	if(GET_BIT(value,1)==DIO_PIN_HIGH){
		DIO_SetPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_HIGH);
	}
	else{
		DIO_SetPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_LOW);
	}
	
	if(GET_BIT(value,2)==DIO_PIN_HIGH){
		DIO_SetPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_HIGH);
	}
	else{
		DIO_SetPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_LOW);
	}
	
	if(GET_BIT(value,3)==DIO_PIN_HIGH){
		DIO_SetPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_HIGH);
	}
	else{
		DIO_SetPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_LOW);
	}
	
}


void LCD_SendCom(u8 Com){
    // set Rs pin = 0 (write command)
    DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
    // set Rw pin = 0 (write)
    DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	#if LCD_MODE == LCD_8_BIT_MODE
	DIO_SetPortValue(LCD_DATA_PORT,Com);
	/* Enable Pulse *//* H => L */
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	
	#elif LCD_MODE == LCD_4_BIT_MODE
	//Write Most 4 Bits OF Command on Data Pins
	WriteHalfPort(Com>>4);
	/* Enable Pulse *//* H => L */
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	//Write Least 4 Bits OF Command on Data Pins
	WriteHalfPort(Com);
	/* Enable Pulse *//* H => L */
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	#endif
}

void LCD_SendChar(u8 Char){
	// set Rs pin = 1 (write data)
	DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_HIGH);
	// set Rw pin = 0 (write)
	DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
#if LCD_MODE == LCD_8_BIT_MODE
	DIO_SetPortValue(LCD_DATA_PORT,Char);
    /* Enable Pulse *//* H => L */
    DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
    _delay_ms(1);
    DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
#elif LCD_MODE == LCD_4_BIT_MODE
	//Write Most 4 Bits OF Command on Data Pins
	WriteHalfPort(Char>>4);
	//Enable Pulse H => L    
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	//Write Least 4 Bits OF Command on Data Pins
	WriteHalfPort(Char);
	//Enable Pulse H => L
    DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
    _delay_ms(1);
    DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
#endif
}

void LCD_SendString(u8 *String){
	u8 StringLength=0;
	if(String!=NULL){
	while (String[StringLength]!='\0')
	{
		LCD_SendChar(String[StringLength]);
		StringLength++;
	}
}
}
void LCD_AmitSendString(u8*String){
if(String!=NULL){
	
u8 StringLength=0,j,flag=0;
while (String[StringLength]!='\0'){
	StringLength++;
}
if(StringLength<=16)goto Normal;
for(j=16;j>=0;j--){
	if(String[j]!=' ') flag++;
		else{break;}
}

if (StringLength<=16||flag==16) {goto Normal;}
else {goto WithSpace;}
	
Normal:
if(StringLength<=32){
	StringLength=0;
	while (String[StringLength]!='\0')
	{
		if(StringLength==16) LCD_goToSpecificPosition(LCD_LINE_TWO,0);
		LCD_SendChar(String[StringLength]);
		StringLength++;
	}
}

else LCD_AmitSendString((u8*)"No Space To Print your txt");
		return;
		
WithSpace:
flag=0;
for(j=16;j>=0;j--){
	if(String[j]!=' ') flag++;
	else{break;}
}
if((StringLength+flag-1)<=32){
	StringLength=0;
	while (String[StringLength]!='\0')
	{
	if((StringLength+flag-1)==16){
		LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	}
		LCD_SendChar(String[StringLength]);
		StringLength++;
	}
}
else LCD_AmitSendString((u8*)"No Space To Print your txt");	
}
}


void LCD_Start_AMIT(void){
		DIO_SetPinDirection(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_OUTPUT);
		DIO_SetPinDirection(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_OUTPUT);
		DIO_SetPinDirection(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_OUTPUT);
		DIO_SetPinDirection(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_OUTPUT);
		
		DIO_SetPinDirection(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_OUTPUT);
		DIO_SetPinDirection(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_OUTPUT);
		DIO_SetPinDirection(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_OUTPUT);
}

void LCD_clear(void)
{
	// Clear Display
	LCD_SendCom(0b00000001);
	_delay_ms(2);
}


void LCD_shift(u8 shifttingDirection){
	if (shifttingDirection == LCD_SHIFT_LEFT)
	{
		LCD_SendCom(0b00011000);
		_delay_ms(10);
	}
	else if (shifttingDirection == LCD_SHIFT_RIGHT)
	{
		LCD_SendCom(0b00011100);
		_delay_ms(10);
	}
}


void LCD_goToSpecificPosition(u8 LineNumber, u8 Position){
	
	if(LineNumber == LCD_LINE_ONE){
		if(LineNumber <= 15)
		{
			LCD_SendCom(0x80 + Position);
		}
	}

	else if (LineNumber == LCD_LINE_TWO)
	{
		if(Position <= 15)
		{
			LCD_SendCom(0xc0 + Position);
		}
	}
}

void LCD_writeNumber(u32 number)
{
	u32 Local_reversed = 1;
	if (number == 0)
	{
		LCD_SendChar('0');
	}
	else
	{
		// Reverse Number
		while (number != 0)
		{
			Local_reversed = Local_reversed*10 + (number%10);
			number /= 10;
		}
		
		do
		{
			LCD_SendChar((Local_reversed%10)+'0');
			Local_reversed /= 10;
		}while (Local_reversed != 1);
	}
}
