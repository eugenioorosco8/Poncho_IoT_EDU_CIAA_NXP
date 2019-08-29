/*
 * ESP8266.c
 *
 *  Created on: 25 ago. 2018
 *      Author: samu_
 */
#include"ESP8266.h"

uint8_t recive[200];
unsigned static int i=0, res=5;


uint8_t ESP8266_begin(const char* ssid, const char* password){

	    Serial_String("AT+RST\r\n");
	    ESP8266_waitFor("OK\0");

	    Serial_String("AT+CIPSTATUS\r\n");
	    Modulo_Delay_X1();

		ESP8266_echoCmds(0);
	    ESP266_mode("1");
	   // Configure el SSID y password para conexión WIFI
	    Serial_String( "AT+CWJAP=\"" );
	    Serial_String (ssid);
	    Serial_String( "\",\"" );
	    Serial_String(password);
	    Serial_String( "\"\r\n" );

	    return( ESP8266_wait("GOT IP\r\n\r\nOK\0","FAIL\0")  );




}



void ESP8266_disconnect(void) {
	Serial_String("AT+CWQAP\r\n");
    ESP8266_waitFor("OK\0");
}



void ESP8266_echoCmds(char echo) {
	Serial_String("ATE");
    if (echo) {
    	Serial_String("1");
    } else {
    	Serial_String("0");
    }
    Serial_String("\r\n");
    ESP8266_waitFor("OK\0");
}


void ESP266_mode(unsigned char *mode) {
	Serial_String("AT+CWMODE=");
	Serial_String(mode);
	Serial_String("\r\n");
	ESP8266_waitFor("OK\0");

}


uint8_t ESP266_ConnectThingSpeak(void){

   Serial_String ("AT+CIPSTART=\"TCP\",\"");                  // Conexión TCP
   Serial_String ("184.106.153.149");                         // api.thingspeak.com
   Serial_String ("\",80\r\n");

   return ( ESP8266_wait("OK\0","ERROR\0") );

   Modulo_Delay_X1();

}

uint8_t ESP8266_WriteChannel(char* APIKey,int field1, int field2, int field3, int field4, int field5 ){

 char valor[3]={0,0,0};



 Serial_String("AT+CIPSENDBUF=98\r\n");
 ESP8266_waitFor(">\0");
 Modulo_Delay_X2();

 Serial_String("GET /update?api_key=");   // Prepara el String GET a mandar
 Serial_String( APIKey);

 Serial_String("&field1=");
 itoa(field1,valor,10);
 Serial_String(valor);//convertir de flotante a String

 Serial_String("&field2=");valor[0,0,0];
 itoa(field2,valor,10);
 Serial_String(valor);

 Serial_String("&field3=");valor[0,0,0];
 itoa(field3,valor,10);
 Serial_String(valor);//convertir de flotante a String

 Serial_String("&field4=");valor[0,0,0];
 itoa(field4,valor,10);
 Serial_String(valor);//convertir de flotante a String

 Serial_String("&field5=");valor[0,0,0];
 itoa(field5,valor,10);
 Serial_String(valor);//convertir de flotante a String//convertir de flotante a String
 Serial_String("\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
 Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,0,14);

 return ( ESP8266_wait("SEND OK\0","SEND FAIL") );



 //Serial_String("AT+CIPCLOSE\r\n");


}




/*
inline unsigned char _esp8266_waitResponse(void) {
    unsigned char so_far[6] = {0,0,0,0,0,0};
    unsigned const char lengths[6] = {2,5,4,9,6,6};
    unsigned const char* strings[6] = {"OK", "ready", "FAIL", "no change", "Linked", "Unlink"};
    unsigned const char responses[6] = {ESP8266_OK, ESP8266_READY, ESP8266_FAIL, ESP8266_NOCHANGE, ESP8266_LINKED, ESP8266_UNLINK};
    unsigned char received;
    unsigned char response;
    char continue_loop = 0;
    while (continue_loop) {
        received = _esp8266_getch();

        for (unsigned char i = 0; i < 6; i++) {
            if (strings[i][so_far[i]] == received) {
                so_far[i]++;
                if (so_far[i] == lengths[i]) {
                    response = responses[i];
                    continue_loop = 0;
                }
            } else {
                so_far[i] = 0;
            }
        }

    }
    return response;
}
*/


