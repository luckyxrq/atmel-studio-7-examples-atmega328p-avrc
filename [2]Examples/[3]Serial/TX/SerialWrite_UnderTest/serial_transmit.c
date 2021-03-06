/*
*Description: How to setup serial port in atmel studio and atmega328p-pu microcontroller.

*Special thanks:
thanks https://www.youtube.com/watch?v=3_omxGIL0kw for the tutorial.
I made the comments to be as clear as possible. Make sure you always check my previous examples on 
gitlab. https://gitlab.com/Basilisvirus/atmel-studio-examples-atmega328p-avrc

*Library used: Avr C library
*Microcontroller: a atmega328p-pu is used here.
*Atmel version: Atmel Studio 7 (Version: 7.0.1931 - )
*Extra software needed: Tera Term to see the serial port output on the computer.
*OS: Windows 10

 */ 

//==================================SERIAL START
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include <avr/interrupt.h>
#include <string.h>

//================================TX START========================
#define BUAD 9600
#define BRC ((F_CPU/16/BUAD)-1)

uint8_t len, i=0; //unsigned 8 bit integer

void sw(char c[]);
void swn(int num, int type, int ln);

//==================================TX END========================

int main(void)
{
//==================================TX START======================
	UBRR0H = (BRC >> 8); //Put BRC to UBRR0H and move it right 8 bits.
	UBRR0L = BRC;
	UCSR0B = (1 << TXEN0); //Trans enable
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //8 BIT data frame
	
	//ENABLE interrupts
	sei();	
//==================================TX END=======================
	while(1)
	{
		sw("TCCR0A is ");
		swn(TCCR0A,10,1);
		_delay_ms(1000);
	}
}


//==================================TX START======================================

void sw(char c[]){
	len = strlen(c); //take size of characters to be printed
	i=0;	//initialize i
	UDR0=0; //make sure UDR0 is 0
	
	while (i<len) //while i is less than the total length of the characters to be printed
	{
		if (  ((UCSR0A & 0B00100000) == 0B00100000)  ){ //if UDRE0 is 1 (aka UDR0 is ready to send)
			UDR0 = c[i]; //put the next character to be sent (now, UDRE0 is 0)
			i++;		//increase the position, and wait until UDRE0 is 1 again
		}
	}
}

void swn(int num, int type, int ln) //take an int and print it on serial
{
	char str[50];//declare a string of 50 characters
	
	itoa(num, str, type);//convert from int to char and save it on str
	
	sw(str); //serial write str
	
	if(ln == 1) //if we want a new line,
	{
		sw("\n\r");	
	}
	
}
//==================================TX END======================================