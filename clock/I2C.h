/*
 * I2C.h
 *
 * Created: 10.03.2019 23:09:55
 *  Author: payaln
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

void I2C_init();
void I2C_startCondition();
void I2C_stopCondition();
void I2C_sendByte(unsigned char c);

#endif /* I2C_H_ */