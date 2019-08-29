#include "Serial.h"
uint8_t recive_byte[600];
extern uint8_t time_out;
#define Tiempo_Espera 8 // equivale a 10 seg
#define Tiempo_Espera_UART 4 // equivale a 10 seg


void Serial_Begin(unsigned int baudios){
	   Chip_SCU_PinMuxSet(0x2, 3, (SCU_MODE_PULLDOWN|SCU_MODE_FUNC2));									//TXD
	   Chip_SCU_PinMuxSet(0x2, 4, (SCU_MODE_INACT|SCU_MODE_INBUFF_EN|SCU_MODE_ZIF_DIS|SCU_MODE_FUNC2));


      Chip_UART_Init(LPC_USART3); //Inicializar UART

      Chip_UART_SetBaud(LPC_USART3,baudios);	//Tasa de Bits
      Chip_UART_SetupFIFOS(LPC_USART3, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);
      Chip_UART_TXEnable(LPC_USART3);

      //Serial_String("AT+RST\r\n");for(uint32_t i=0; i < 500000000; i++);

      //Serial_String("AT+UART_CUR=9600,8,1,0,0\r\n"); for(uint32_t i=0; i < 100000000; i++);
/*
      Chip_UART_Init(LPC_USART3); //Inicializar UART
      Chip_UART_SetBaud(LPC_USART3,baudios);	//Tasa de Bits
      Chip_UART_SetupFIFOS(LPC_USART3, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);
      Chip_UART_TXEnable(LPC_USART3);
     // Chip_UART_IntEnable(LPC_USART3, UART_IER_RBRINT);	//Interrupt Habilitada
      //NVIC_EnableIRQ(USART3_IRQn);

*/

      Chip_SCU_PinMux (2,12,MD_PUP,FUNC3); // CS
      Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT,1, 12);

      Chip_SCU_PinMux (2,11,MD_PUP,FUNC3); // CS
      Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT,1, 11);

      Chip_SCU_PinMux (2,10,MD_PUP,FUNC3); // CS
      Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT,0, 14);

}

void Serial_Send( uint8_t send_byte){
while ((Chip_UART_ReadLineStatus(LPC_USART3) & UART_LSR_THRE) == 0) {}   // Wait for space in FIFO
      Chip_UART_SendByte(LPC_USART3,send_byte);
}


void Serial_String(char* str ){
	while(*str != 0){
	  Serial_Send((uint8_t)*str );
	  str++;
   }

}

void Serial_read( uint8_t *recive_byte){
	static char i=0;
	char dim;
	unsigned char datos;

	if ( Chip_UART_ReadLineStatus(LPC_USART3) & UART_LSR_RDR ) {
	 datos = Chip_UART_ReadByte(LPC_USART3);
	 if(0 < datos){
		 i++;

		recive_byte[i]=datos;


	 }

  }


}

void ESP8266_waitFor(const unsigned char *string) {
    unsigned char so_far = 0;
    unsigned char received;
    static unsigned int i=0;
    uint16_t counter = 0;

    do {
    	if ( Chip_UART_ReadLineStatus(LPC_USART3) & UART_LSR_RDR ) {
    		time_out=0;
    		received  = Chip_UART_ReadByte(LPC_USART3);
    		recive_byte[i]=received;  i++;

            if (received == string[so_far]) {so_far++;}
            else {so_far = 0;}

    	}
    } while ((string[so_far] != 0)&&(Tiempo_Espera_UART > time_out )) ;



   // return counter;
}

void UART3_IRQHandler(void){

	static char i=0;
		unsigned char datos;
		if ( Chip_UART_ReadLineStatus(LPC_USART3) & UART_LSR_RDR ) {

			 datos = Chip_UART_ReadByte(LPC_USART3);
			 if(0 < datos){

				 recive_byte[i]=datos;
				 i++;


			 }
	   }
		else i=0;

		NVIC_ClearPendingIRQ(USART3_IRQn);
}



unsigned char ESP8266_wait(  unsigned char *string1, unsigned  char *string2) {
    unsigned char so_far1 = 0,so_far2 = 0;
    unsigned char received;
    static unsigned int i=0;
    time_out=0;

    do {
    	if ( Chip_UART_ReadLineStatus(LPC_USART3) & UART_LSR_RDR ) {
    		received  = Chip_UART_ReadByte(LPC_USART3);
    		recive_byte[i]=received;  i++;

        if (received == string1[so_far1]) { so_far1++;}
        else { so_far1 = 0;}

        if (received == string2[so_far2]) { so_far2++;}
        else { so_far2 = 0;}

    	}
    } while ( (string2[so_far2] != 0) && (string1[so_far1] != 0)&&(Tiempo_Espera > time_out ) );

    Modulo_Delay_X1();
     if(time_out >= Tiempo_Espera){ return 0;}
     if(string1[so_far1] != 0){return 0 ;}
     else {return 1;}


}

void Modulo_Delay_X1(void){
	for(uint32_t i=0; i < 100000000; i++);

}

void Modulo_Delay_X2(void){

	for(uint32_t i=0; i < 200000000; i++);

}


