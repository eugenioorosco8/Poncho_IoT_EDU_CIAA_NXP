/*
 * ESP8266.h
 *
 *  Created on: 25 ago. 2018
 *      Author: samu_
 */

#ifndef ESP8266_H_
#define ESP8266_H_

#include "chip.h"
#include "Serial.h"
#include "stdlib.h"
#include "string.h"


#define ESP8266_STATION 0x01
#define ESP8266_SOFTAP 0x02

#define ESP8266_TCP 1
#define ESP8266_UDP 0

#define ESP8266_OK 1
#define ESP8266_READY 2
#define ESP8266_FAIL 3
#define ESP8266_NOCHANGE 4
#define ESP8266_LINKED 5
#define ESP8266_UNLINK 6


uint8_t ESP8266_begin(const char* ssid, const char* password);
void    ESP266_mode(unsigned char *mode);
uint8_t ESP266_ConnectThingSpeak(void);
uint8_t    ESP8266_WriteChannel(char* APIKey,int field1, int field2, int field3, int field4, int field5 );
void    ESP8266_echoCmds(char echo);
void    ESP8266_disconnect(void);



#endif /* ESP8266_H_ */
