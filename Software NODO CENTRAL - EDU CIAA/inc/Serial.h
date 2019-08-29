/*
 * Serial.h
 *
 *  Created on: 24 ago. 2018
 *      Author: samu_
 */

#ifndef SERIAL_H_
#define SERIAL_H_
#include "chip.h"


void Serial_Begin(unsigned int baudios);
void Serial_Send( uint8_t send_byte);
void Serial_read( uint8_t *recive_byte);
void ESP8266_waitFor(const unsigned char *string) ;
unsigned char ESP8266_wait(unsigned char *string1,  unsigned char *string2) ;

void Modulo_Delay_X1(void);
void Modulo_Delay_X2(void);

void Serial_String(char* str );

#endif /* SERIAL_H_ */
