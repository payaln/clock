/*
 * RTC.cpp
 *
 * Created: 10.03.2019 23:48:17
 *  Author: payaln
 */ 
 #include "RTC.h"

unsigned char RTC_ConvertFromDecToBin(unsigned char c) {
	unsigned char ch = ((c / 10) << 4) | (c % 10);
	return ch;
 }

unsigned char RTC_ConvertFromBinToDec(unsigned char c) {
	unsigned char ch = (c >> 4) * 10 + (0b1111 & c);
	return ch;
 }