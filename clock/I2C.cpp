/*
 * I2C.cpp
 *
 * Created: 10.03.2019 23:10:18
 *  Author: payaln
 */ 

 #include "I2C.h"

 void I2C_init() {
	 TWBR = 0x20;
 }

 void I2C_startCondition() {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
 }

 void I2C_stopCondition() {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
 }

 void I2C_sendByte(unsigned char c) {
	TWDR = c;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
 }