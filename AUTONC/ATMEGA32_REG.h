/*
 * ATMEGA32_REG.h
 *
 * Created: 9/6/2022 12:23:11 PM
 *  Author: 
 */ 


#ifndef ATMEGA32_REG_H_
#define ATMEGA32_REG_H_
 /* DIO REGISTERS*/
 
 /* DATA DIRCTION REGISTERS */
 #define DDRA           (*(volatile u8*)0x3A)
 #define DDRB           (*(volatile u8*)0x37)
 #define DDRC           (*(volatile u8*)0x34)
 #define DDRD           (*(volatile u8*)0x31)

 /* OUTPUT REGISTERS */
 #define PORTA          (*(volatile u8*)0x3B)
 #define PORTB          (*(volatile u8*)0x38)
 #define PORTC          (*(volatile u8*)0x35)
 #define PORTD          (*(volatile u8*)0x32)

 /* INPUT REGISTERS */
 #define PINA           (*(volatile u8*)0x39)
 #define PINB           (*(volatile u8*)0x36)
 #define PINC           (*(volatile u8*)0x33)
 #define PIND           (*(volatile u8*)0x30)

 
 /* EXTERNAL INTERRUPT REGISTERS */

 // MCU Control Register
 #define MCUCR          (*(volatile u8*)0x55)

 // MCU Control and Status Register
 #define MCUCSR         (*(volatile u8*)0x54)

 // General Interrupt Control Register
 #define GICR           (*(volatile u8*)0x5B)

 // General Interrupt Flag Register
 #define GIFR           (*(volatile u8*)0x5A)

 // Status Register
 #define SREG           (*(volatile u8*)0x5F)
 
                       /* ADC REGISTER*/
//ADC Multiplexer Selection Register
#define ADMUX           (*(volatile u8*)0x27)
//ADC Control and Status Register A
#define ADCSRA          (*(volatile u8*)0x26)
//ADC Data Registers
#define ADCL            (*(volatile u8*)0x24)
#define ADCH            (*(volatile u8*)0x25)
#define ADC_u16         (*(volatile u16*)0x24)
//Special FunctionIO Register
#define SFIOR           (*(volatile u8*)0x50)

                       /* Timers REGISTER*/
	 
//Timer0

//Timer/Counter Control Register
#define TCCR0           (*(volatile u8*)0x53)
//Timer/Counter Register
#define TCNT0           (*(volatile u8*)0x52)
//Output Compare Register
#define OCR0            (*(volatile u8*)0x5C)
//Timer/Counter Interrupt Mask
#define TIMSK           (*(volatile u8*)0x59)
//Timer/Counter Interrupt Flag Register
#define TIFR            (*(volatile u8*)0x58)

//Timer1
//Timer/Counter1 Control Register A
#define TCCR1A          (*(volatile u8*)0x4F)
//Timer/Counter1 Control Register B
#define TCCR1B          (*(volatile u8*)0x4E)
//Timer/Counter1
#define TCNT1_u16           (*(volatile u16*)0x4C)
//Output Compare Register 1 A
#define OCR1A_u16           (*(volatile u16*)0x4A)
//Output Compare Register 1 B
#define OCR1B_u16           (*(volatile u16*)0x48)
//Input Capture Register 1 
#define ICR1_u16            (*(volatile u16*)0x46)

//Timer2

//Timer/Counter Control Register
#define TCCR2           (*(volatile u8*)0x45)
//Timer/Counter Register
#define TCNT2           (*(volatile u8*)0x44)
//Output Compare Register
#define OCR2            (*(volatile u8*)0x43)




//WDT 
#define WDTCR               (*(volatile u8*)0x41)

/* UART REGISTERS*/

//UASRT I/O Data Register
#define UDR            (*(volatile u8*)0x2C)
//UASRT Control and Statues Register A
#define UCSRA          (*(volatile u8*)0x2B)
//UASRT Control and Statues Register B
#define UCSRB          (*(volatile u8*)0x2A)
//UASRT Control and Statues Register C
#define UCSRC          (*(volatile u8*)0x40)
//UASRT Baud Rate Registers
#define UBRRL          (*(volatile u8*)0x29)
#define UBRRH          (*(volatile u8*)0x40)

                     /* SPI REGISTERS*/
typedef struct {
	u8 SPCR;
	u8 SPSR;
	u8 SPDR;
	}SPI_REGS;
	
#define SPI   ((volatile SPI_REGS*)0x2D)	

                     /* TWI REGISTERS*/
					 
//TWI Bit Rate Register
#define TWBR          (*(volatile u8*)0x20)
//TWI Control Register
#define TWCR          (*(volatile u8*)0x56)
//TWI Status Register
#define TWSR          (*(volatile u8*)0x21)
//TWI Data Register
#define TWDR          (*(volatile u8*)0x23)
//TWI Slave Address Register
#define TWAR          (*(volatile u8*)0x22)



 
					   

#endif /* ATMEGA32_REG_H_ */