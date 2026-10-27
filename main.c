/*
 * TIMER07-Segment Display.c
 *
 * Created: 10/23/2026 7:22:25 PM
 * Author : 91989
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
int seg_cc[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x40};
volatile uint8_t flag = 0;
void display_Date(uint32_t date, uint8_t mode){   // ? uint32_t, not int
	uint8_t d1 = date / 100000;
	uint8_t d2 = (date / 10000) % 10;
	uint8_t m1 = (date / 1000) % 10;
	uint8_t m2 = (date / 100) % 10;
	uint8_t y1 = (date / 10) % 10;
	uint8_t y2 = date % 10;
	if(mode == 0){
	// Digit at PD7 (leftmost)
	PORTB = 0xFF;
	PORTB &= ~(1 << PB7);
	PORTC = seg_cc[d1];
	
	}
	else if(mode == 1){ 
	// PD6
	PORTB = 0xFF;
	PORTB &= ~(1 << PB6);
	PORTC = seg_cc[d2];
	}
	else if(mode == 2){
	// PD5 (dash)
	PORTB = 0xFF;
	PORTB &= ~(1 << PB5);
	PORTC = seg_cc[10];
	}
	else if(mode ==3){
	// PD4
	PORTB = 0xFF;
	PORTB &= ~(1 << PB4);
	PORTC = seg_cc[m1];
	}
	else if(mode == 4){
	// PD3
	PORTB = 0xFF;
	PORTB &= ~(1 << PB3);
	PORTC = seg_cc[m2];
	}
	else if(mode ==5){
	// PD2 (dash)
	PORTB = 0xFF;
	PORTB &= ~(1 << PB2);
	PORTC = seg_cc[10];
	}
	else if(mode ==6){
	// PD1 — year tens
	PORTB = 0xFF;
	PORTB &= ~(1 << PB1);
	PORTC = seg_cc[y1];
	}
	else if(mode == 7){
	// PD0 (rightmost) — year ones
	PORTB = 0xFF;
	PORTB &= ~(1 << PB0);
	PORTC = seg_cc[y2];
	}
}

volatile uint8_t mode;
ISR(TIMER0_OVF_vect){
	if(flag == 1){
	TCNT0 = 6;
	display_Date(120408, mode);
	mode++;
	if(mode ==8){
		mode = 0;
	}
	}
	else if (flag == 0){
		TCNT0 = 6;
		display_Date(142650, mode);
		mode++;
		if(mode ==8){
			mode = 0;
		}
	}
}

void Usart_Init(void){
	UCSRB  |= (1<<RXEN)|(1<<TXEN);
	UCSRC = (1<<URSEL)|(1<<UCSZ0) | (1<<UCSZ1);
	UBRRL = 103;
	UBRRH = 0;
}

char getChar(void){
	while(!(UCSRA & (1<<RXC)));
	return UDR;
}

int main(void)
{
	DDRC = 0xFF;
	DDRB = 0xFF;
	PORTB = 0XFE;
	PORTC = seg_cc[3];
    /* Replace with your application code */
	TCCR0 = (1<<CS01)|(1<<CS00);
	TCNT0 = 6;
	TIFR = (1<<TOV0);
	TIMSK |=(1<<TOIE0);
	Usart_Init();
	sei();
	char buffer[10];
	uint8_t index = 0;
	char curr;
    while (1)
    {
	    curr = getChar();

	    if (curr == '\r' || curr == '\n')
	    {
		    buffer[index] = '\0';

		    if (strcmp(buffer, "TIME") == 0)
		    flag = 1;
		    else if (strcmp(buffer, "DATE") == 0)
		    flag = 0;

		    index = 0;
	    }
	    else if (index < sizeof(buffer) - 1)
	    {
		    buffer[index++] = curr;
	    }
    }
}

