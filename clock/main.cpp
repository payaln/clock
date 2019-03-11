/*
 * clock.cpp
 *
 * Created: 08.03.2019 19:07:46
 * Author : payaln
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "I2C.h"
#include "RTC.h"

char dig1 = 0;
char dig2 = 1;
char dig3 = 2;
char dig4 = 3;
char dig5 = 4;
char dig6 = 5;
char dig_num = 0;

void port_init() {
	PORTB = 0x00;
	DDRB = 0b00111110;

	PORTC = 0b111111;
	DDRC = 0b111111;

	PORTD = 3<<4;
	DDRD = 0b11110000;
}

void pwmBegin(unsigned freq) {
	
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1A |= (1 << COM1B1) | (1 << WGM10);
	TCCR1B |= (1 << WGM13) | (1 << CS10); 
	OCR1A = F_CPU / 2 / freq;
	OCR1B = F_CPU / 4 / freq;
}

void timer_init() {
	TCCR0 = (1 << CS01);
	TIMSK |= (1 << TOIE0);
}

ISR (TIMER0_OVF_vect) {
	PORTC &= 0b000000;
	switch (dig_num) {
	case 0:
		PORTD = dig1<<4;
		PORTC |= (1<<5);
		break;
	case 1:
		PORTD = dig2<<4;
		PORTC = (1<<4);
		break;
	case 2:
		PORTD = dig3<<4;
		PORTC |= (1<<3);
		break;
	case 3:
		PORTD = dig4<<4;
		PORTC |= (1<<2);
		break;
	case 4:
		PORTD = dig5<<4;
		PORTC |= (1<<1);
		break;
	case 5:
		PORTD = dig6<<4;
		PORTC |= (1<<0);
		break;
	}
	++dig_num;
	if (dig_num > 5) {
		dig_num = 0;
	}
	
}

int main(void)
{
	//pwmBegin(30000);
	port_init();
	timer_init();

	I2C_init();
	I2C_startCondition();
	I2C_sendByte(0b11010000);
	I2C_sendByte(0);
	I2C_sendByte(RTC_ConvertFromDecToBin(0));
	I2C_sendByte(RTC_ConvertFromDecToBin(58));
	I2C_sendByte(RTC_ConvertFromDecToBin(23));
	I2C_sendByte(RTC_ConvertFromDecToBin(7));
	I2C_sendByte(RTC_ConvertFromDecToBin(10));
	I2C_sendByte(RTC_ConvertFromDecToBin(3));
	I2C_sendByte(RTC_ConvertFromDecToBin(19));
	I2C_stopCondition();
	sei();


    while (1) 
    {
		_delay_ms(500);
		if (dig6 == 9) {
			dig6 = 0;
		} else {
			++dig6;
		}
		
    }
}

