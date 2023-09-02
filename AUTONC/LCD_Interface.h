/*
 * LCD_Interface.h
 *
 * Created: 9/11/2022 11:28:56 AM
 *  Author: Ammar
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define LCD_8_BIT_MODE        1
#define LCD_4_BIT_MODE        2

/* Macros For LCD Line Id */
#define LCD_LINE_ONE            1
#define LCD_LINE_TWO            2

/* Macros For LCD Shifting Direction */
#define LCD_SHIFT_LEFT          0
#define LCD_SHIFT_RIGHT         1

static void WriteHalfPort(u8 Value);
void LCD_Init (void);
void LCD_SendCom(u8 Com);
void LCD_SendChar(u8 Char);
void LCD_SendString(u8*);
void LCD_AmitSendString(u8*);
void LCD_clear(void);
void LCD_shift(u8 shifttingDirection);
void LCD_goToSpecificPosition(u8 LineNumber, u8 Position);
void LCD_writeNumber(u32 number);


void LCD_Start_AMIT(void);







#endif /* LCD_INTERFACE_H_ */