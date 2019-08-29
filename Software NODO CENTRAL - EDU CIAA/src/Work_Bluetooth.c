#include <Work_Bomba.h>
#include "Work_Bluetooth.h"
#include "WorkApp.h"
#include "TriAc.h"
//---------------------------------- Varibles Locales de archivo Work_Bluetooth --------------------
#define DELAY()	for(int p=0;p<100000;p++);
#define CANT 24

int *HumAmbp, *TempAmbp, *HumSuelop, *TempSuelop, *Horap;
int Mediciones1[5]={0};
int Mediciones2[5]={0};

//-------------------------------------------Funcion de inicializacion de UART Bluetooth---------
void Bluetooth_Init(void){

     Chip_SCU_PinMuxSet(0x1, 15, (SCU_MODE_PULLDOWN|SCU_MODE_FUNC1));									//TXD
     Chip_SCU_PinMuxSet(0x1, 16, (SCU_MODE_INACT|SCU_MODE_INBUFF_EN|SCU_MODE_ZIF_DIS|SCU_MODE_FUNC1));	//RXD

     Chip_UART_Init(LPC_USART2); //Inicializar UART

     Chip_UART_SetBaud(LPC_USART2,9600);	//Tasa de Bits
     //Chip_UART_SetupFIFOS(LPC_USART3, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);
     Chip_UART_TXEnable(LPC_USART2);
     Chip_UART_IntEnable(LPC_USART2, UART_IER_RBRINT);	//Interrupt Habilitada
     NVIC_EnableIRQ(USART2_IRQn);// Interrupt Enable
}

void Bluetooth_GetData1(int *Datos_Nodo1, unsigned char n_datos){

	for(unsigned char i=0; i<n_datos ; i++){

		Mediciones1[i]=Datos_Nodo1[i]; //copio los datos recibidos via RF a una variable local de este archivo para ser empleada en interrup. UART

	}

}

void Bluetooth_GetData2(int *Datos_Nodo2, unsigned char n_datos){

	for(unsigned char i=0; i<n_datos ; i++){

		Mediciones2[i]=Datos_Nodo2[i]; //copio los datos recibidos via RF a una variable local de este archivo para ser empleada en interrup. UART

	}

}

//---------------------------------Interrupcion por UART---------------------------------------------
void UART2_IRQHandler(void){
   	uint8_t receivedByte=0;

  static 	char banderaTemp=0;
  static 	char banderaLevel=0;



   if ( Chip_UART_ReadLineStatus(LPC_USART2) & UART_LSR_RDR ) {
        receivedByte = Chip_UART_ReadByte(LPC_USART2);

        switch (receivedByte){

        	case 'v':												// Solicitud de Datos Actuales para la App- nodo 1
        		for(unsigned char i=0; i<5 ; i++){
        			Chip_UART_SendByte(LPC_USART2,(int)Mediciones1[i]/10);
        		}
        		break;

        	case 'g':												// Solicitud de Datos Actuales para la App
                		for(unsigned char i=0; i<5 ; i++){
                			Chip_UART_SendByte(LPC_USART2,(int)Mediciones2[i]/10);
                		}
                		break;


        	case 'F':										//Solicitud de Ultimos 24 valores de HumSuelo para grafica en App
        		Return_Pointer(&HumAmbp, &TempAmbp, &HumSuelop, &TempSuelop, &Horap); //esta funcion solicita los punteros a los arreglos de ultimos 24 valores en el archivo WorkApp.c
        		for(unsigned char i=0; i<CANT ; i++){
        			DELAY();
        			Chip_UART_SendByte(LPC_USART2,*(HumSuelop+i));
        		}
        		break;


        	case 'G':					//Solicitud de Ultimos 24 valores de HumAmb para grafica en App
        	    Return_Pointer(&HumAmbp, &TempAmbp, &HumSuelop, &TempSuelop, &Horap);
        	    for(unsigned char i=0; i<CANT ; i++){
        	    	DELAY();
        	    	Chip_UART_SendByte(LPC_USART2, *(HumAmbp+i));
        	     }
        	     break;


        	case 'H':						//Solicitud de Ultimos 24 valores de TempSuelop para grafica en App
        	    Return_Pointer(&HumAmbp, &TempAmbp, &HumSuelop, &TempSuelop, &Horap);
        	    for(unsigned char i=0; i<CANT ; i++){
        	    	DELAY();
        	    	Chip_UART_SendByte(LPC_USART2,*(TempSuelop+i));

        	    }
        	    break;


        	case 'I':					//Solicitud de Ultimos 24 valores de TemAmb para grafica en App
               Return_Pointer(&HumAmbp, &TempAmbp, &HumSuelop, &TempSuelop, &Horap);
               for(unsigned char i=0; i<CANT ; i++){
            	   DELAY();
            	   Chip_UART_SendByte(LPC_USART2,*(TempAmbp+i));
               }
               break;


        	case 'J':					//Solicitud de Ultimos 24 valores de Horas para grafica en App- Se solicita siempre!
                Return_Pointer(&HumAmbp, &TempAmbp, &HumSuelop, &TempSuelop, &Horap);
                for(unsigned char i=0; i<CANT ; i++){
                	DELAY();
                	Chip_UART_SendByte(LPC_USART2,*(Horap+i));

                }
                break;

        	case 'T':
        		banderaTemp=1;


        	break;

        	case 'L':
        		banderaLevel=1;

             break;

			default:

				if (banderaTemp==1){
					int Ref_Temp=receivedByte;
					PI_Get_Ref(Ref_Temp);
					banderaTemp=0;	// Limpio bandera de recepcion

				}
				if (banderaLevel==1){
					int Ref_Level=receivedByte;
					Ref_Level_App(Ref_Level);
					banderaLevel=0;
				}
				   break;





          }

   	   }


   	NVIC_EnableIRQ(USART2_IRQn);	//Limpieza de bandera de interrupcion de UART3

   }


