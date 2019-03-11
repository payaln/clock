/*
 * PWM.cpp
 *
 * Created: 08.03.2019 19:14:15
 *  Author: payaln
 */ 

 #include "PWM.h"

 void init_PWM_timer() {
	ASSR = 0x00;
	TCCR2 = 0b01101110;
	TCNT2 = 0x30;
	OCR2 = 0x00;

 }
