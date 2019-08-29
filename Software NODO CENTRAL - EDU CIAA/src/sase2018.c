/*
===============================================================================
 /*
===============================================================================
 Name        : test.c
 Author      :JULIAN BY MATEO
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
//---------------------- INCLUDES PROJECT SD-----------------------------

#include <chip.h>
#include "ff.h"
#include <diskio.h>
#include "WorkSD.h"
#include "rtc.h"
#include <string.h>
#include <stdlib.h>
#include "WorkApp.h"
// LCD
#include "puertos.h"
#include "lcd.h"
// ESP8266
#include "Serial.h"
#include "ESP8266.h"


//--------------------- ESP8266 ------------------------------------------
#define Intentos 2
#define Tiempo_Espera 7 // equivale a 14 seg
#define ssid "wifi-2"
#define password "tplinkmateo15"
unsigned char flag_WiFi=0, flag_GPRS=0, time_out=0, busy=0,pipe;

//**********************************************************************************************************
//                     Interrupcion del RIT Timer
//**********************************************************************************************************

 void RIT_IRQHandler(void){
	 uint16_t static contador=0;
	 if(contador < 15){ contador ++;}
	 else{ contador=0;  }

     time_out++;
     Chip_RIT_ClearInt(LPC_RITIMER);
     NVIC_ClearPendingIRQ(RITIMER_IRQn);
}



//---------------------INCLUDES PROJECT RF--------------------------------

	#include "UPC_nRF24L01.h"

	uint8_t pipe_00[5] = {"PIPE0"};
	uint8_t pipe_01[5] = {"PIPE1"};
    unsigned char mensaje[8] = {1,2,4,8,16,32,64,128};
    #define  nameWidth 3
	#define FCH 90
	#define dataRate 0 // 0-> 1Mbps  ,   1-> 2Mbps
	#define PowerOut 3 //0=> -18dBm, 1 => -12dBm, 2 => -6dBm, 3 => 0dBm
	#define EnableChecksum 0 // 0->Disable , 1 -> Enable
	#define PAYLOAD 8  // NUMEROS DE BYTES A ENVIAR
    #define LNA_Gain 1 //  0 => Disabled, 1 => Enabled
	#define CRC_Setup 2 //0 => 1byte, 1 => 2byte
    #define Mascara_Pipe 0b00001110


//-------------------------INCLUDE PROJECT BLUETOOTH--------------------------

#include  "Work_Bluetooth.h"

 //------------------------INCLUDE ADC TANQUE---------------------------------

#include "Work_ADC.h"

//------------------------------INCLUDE BOMBA--------------------------------

#include <Work_Bomba.h>

//---------------------------------INCLUDE CALENTADOR PID---------------------
#include "TriAc.h"
#define KI 0.03
#define KP 2
#define Tolerancia 2
#define Zona_Muerta 5
#define Ts 5

//-----------------------------VARIABLES GLOBALES------------------------------
    // Datos Pipe 0
    int Datos_SD[5]={0};	//Datos provenientes del Nodo 0
    char RX_Payload[8]={0};
    //Datos Pipe 1
    int Datos_SD_01 [5]={0};	//Datos provenientes del Nodo 1
    char RX_Payload_01[8]={0};

    int Ref_Temp_App=25;	//Dato de referencia primera pasada temperatura




//-------------------------INTERRUPT RIT----------------------------------------

  /*  void RIT_IRQHandler(void){
    static int Mediciones[4]={173,128,589,123}; //mediciones x10 (a una cifra decimal) samuel

    		/*Write_MeasurementsSD(Mediciones);
    		Last_Values_App(Mediciones);

    		Chip_RIT_ClearInt(LPC_RITIMER);
    		NVIC_ClearPendingIRQ(RITIMER_IRQn);


    }*/


//--------------------------------------MAIN------------------------------------

    //*************************************** lcd *********************************
    /*

*/

int main(void) {


#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable

	SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
#if defined (__MULTICORE_MASTER) || defined (__MULTICORE_NONE)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
#endif
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif
// Force the counter to be placed into memory
volatile static int i = 0 ;
// Enter an infinite loop, just incrementing a counter

//******************************************* LCD  *********************************************************
    lcd_init_port();
    lcd_init();

    lcd_gotoxy(1, 1);
    printf_lcd("   TESIS 2019 ");
    lcd_gotoxy(1, 2);
    printf_lcd(" JULIAN - MATEO ");

//**************************************************************************
//**************** RITIMER**************************************************
//**************************************************************************
    /*
     Chip_RIT_Init(LPC_RITIMER);
     Chip_RIT_SetTimerInterval(LPC_RITIMER,2000);
     Chip_RIT_Enable(LPC_RITIMER);
     NVIC_EnableIRQ(RITIMER_IRQn);
*/
     uint8_t static caso=0,estado=0,cont_fail=0;

//***************************************************************************
//                  PIN POWER A6
//***************************************************************************
     Chip_SCU_PinMux (6,12,MD_PUP,FUNC3); // CS
     Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT,2, 8);
     Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,2,8);

//----------------------------------------REGITRO HORARIO PARA SD ARCHIVOS--------------------------

  // int sec=0,min=34,hour=18,dayofmonth=11,dayofweek=16,dayofyear=190,month=12,year=2018 ;
   //rtc_set(sec,min,hour,dayofmonth,dayofweek,dayofyear,month,year); 	//Seteo valores iniciales del reloj
   rtc_init();

//----------------------------------------HABILITACION Y CONFIGURACION RIT-----------------------------

 /*  Chip_RIT_Init(LPC_RITIMER);
   Chip_RIT_SetTimerInterval(LPC_RITIMER,5000);
  Chip_RIT_Enable(LPC_RITIMER);
  NVIC_EnableIRQ(RITIMER_IRQn);*/


//---------------------------------------INIT HARDWARE SD------------------------------------------------

     initHardwareSD();

//------------------------------> INICIALIZA HARDWARE nRF24L01 RF RX<--------------------------------------
    Chip_SCU_PinMuxSet(0x6, 7, (SCU_MODE_PULLUP | SCU_MODE_FUNC4)); /* CS1 configured as GPIO0 */
   	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 5, 15); //Chip Select en GPIO0
   	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,5,15);
    //MIRF_IRQinit();
    SPI_Start();
    nRF24L01_Ports_Start();
    Reset_nRF24L01_Status_and_nRF24L01_Payloads ();
    Start_RX_Mode_nRF24L01(nameWidth, FCH,dataRate, PowerOut,LNA_Gain, CRC_Setup,pipe_00,0x00,0x00, 0x00, 0x00, 0x00, EnableChecksum, 8, 8, 0, 0, 0, 0);

//-----------------------------------------INIT HARDWARE BLUETOOTH---------------------------------------


    Bluetooth_Init();

//-------------------------------------------INIT HARDWARE ADC----------------------------------------
  uint8_t channel_ADC_Tank=2;  	//Canal 2 para el ADC potenciometro tanque
  InicializarAdc(channel_ADC_Tank);

//---------------------------------------------INIT HARDWARE CALENTADOR-TRIAC---------------------------

  	////Triac_Init(3);
  	//PI_Init (KI,KP,Tolerancia,Zona_Muerta,Ts);







//*********************************************************************************************************
//             loop               loop               loop                  loop

//**********************************************************************************************************
    while(1) {


   if(dataReady() & busy==0){ //Si se recibe un dato via RF...


       lcd_gotoxy(1, 1);// limpia LCD
       printf_lcd("                ");
       lcd_gotoxy(1, 2);
       printf_lcd("                ");


      pipe= Read_nRF24L01_Status ();
      pipe= pipe & Mascara_Pipe;

     // si esta enviando un dato espera....

      if(pipe== 0b00000000){
    	   pipe=0;// Informacion Proveniente del Nodo 0
    	   busy=1; // Indica que el Nrf24l01, debe esperar hasta que el dato se envie al servidor
    	   flag_WiFi=1;// El dato sera enviado por Wifi

           lcd_gotoxy(1, 1); printf_lcd("Data Station 0  ");
           Receive_Data_RX_Mode_nRF24L01( 0,0, PAYLOAD,RX_Payload,Datos_SD);  //Dato recibido via RF desde Nodo en Datos_SD
           Reset_nRF24L01_Status_and_nRF24L01_Payloads ();// Limpia los Registros de Payload y Status
           Start_RX_Mode_nRF24L01(nameWidth, FCH,dataRate, PowerOut,LNA_Gain, CRC_Setup,0x00,pipe_01, 0x00, 0x00, 0x00, 0x00, EnableChecksum, 8, 8, 0, 0, 0, 0);
           Write_MeasurementsSD(Datos_SD,5, 0);// escribe Datos en La memoria SD, en el Archivo Correspondiente

      }
      if(pipe== 0b00000010){ // Verifica si el datos proviene del NODO 1
    	  pipe=1;// Informacion Proveniente del Nodo 1
    	  busy=1;// Indica que el Nrf24l01, debe esperar hasta que el dato se envie al servidor
    	  flag_WiFi=1;// El dato sera enviado por Wifi
          lcd_gotoxy(1, 1); printf_lcd("Data Station 1  ");
    	  Receive_Data_RX_Mode_nRF24L01( 0,0, PAYLOAD,RX_Payload_01,Datos_SD_01);  //Dato recibido via RF desde Nodo en Datos_SD
    	  Reset_nRF24L01_Status_and_nRF24L01_Payloads ();
    	  Start_RX_Mode_nRF24L01(nameWidth, FCH,dataRate, PowerOut,LNA_Gain, CRC_Setup,pipe_00,0x00, 0x00, 0x00, 0x00, 0x00, EnableChecksum, 8, 8, 0, 0, 0, 0);
    	  Write_MeasurementsSD(Datos_SD_01,5, 1);// Escribe Datos en La memoria SD, en el Archivo Correspondiente

      }


//--------------------------------Lectura de Nivel de tanque y asignacion-----------------------------------

      Datos_SD[4]=(int)((-0.1095)*AdcPolling())+100;	// Agrega litros de tanque
      Datos_SD[4]= 800;
      Datos_SD_01[4]= 800;

//--------------------------------Bucle de escritura en SD--------------------------------------------------

      //Write_MeasurementsSD(Datos_SD,5); 	//almacena paquete recibido via RF en archivo de SD
      Last_Values_App(Datos_SD);		//Almacena en arreglos historicos para graficar en  App

//-------------------------------Bucle de envio por Bluetooth-----------------------------------------------

      Bluetooth_GetData1(Datos_SD, 5);
      Bluetooth_GetData2(Datos_SD_01, 5);

 }// fin DATA Ready NRF24L01

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                          ENVIAR DATOS SERVIDOR                                                            //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   	  if(flag_WiFi){

   	        switch(caso){
   	        	case 0:  // SE CONECTA RED WIFI
   	        		   Serial_Begin(115200);

   	        		   estado=ESP8266_begin(ssid,password);

   	        		   if(estado){
   	        			   caso=1; cont_fail =0;
   	        		   	   lcd_gotoxy(1, 1); printf_lcd("WiFi Conect     ");
   	        		   	   lcd_gotoxy(1, 2); printf_lcd("Connecting Cloud");
   	        		   }

   	        		   else {
   	        			   caso=0; cont_fail ++;
   	        			   lcd_gotoxy(1, 1);printf_lcd("WiFi Fail       ");
   	        		       lcd_gotoxy(1, 2);printf_lcd("Netword no found");
   	        		   }

   	        		   if(cont_fail > Intentos){
   	        			   flag_GPRS=1;   flag_WiFi=0; cont_fail =0; caso=0; busy=0;
   	        			   lcd_gotoxy(1, 1);printf_lcd("Connect A6 / GPRS");
   	        		       lcd_gotoxy(1, 2);printf_lcd("Company Claro AR");
   	        		   }

   	        	       break;

   	        	case 1: // SE CONECTA AL SERVIDOR THING SPEAK

   	        		 	estado=ESP266_ConnectThingSpeak();

   	        		 	if(estado){// CONEXION CON EXITO
   	        		 	 caso=2;cont_fail =0;flag_GPRS=0;
   	        		 	 lcd_gotoxy(1, 1); printf_lcd("Thing Speak     ");
   	        		 	 lcd_gotoxy(1, 2); printf_lcd("Connect......   ");
   	        		 	}

   	        		 	else{ caso=1; cont_fail++; }// FALLA EN CONEXION SERVIDOR

   	        		 	if(cont_fail > Intentos){
   	        		 		flag_GPRS=1;  flag_WiFi=0; cont_fail =0; caso=0; busy=0;
   	        		 	}

   	        	        break;

   	        	case 2:
   	        		 if(pipe==0){ estado=ESP8266_WriteChannel("CFDZGKH7ME80Z4FA",Datos_SD[0]/10,Datos_SD[1]/10,Datos_SD[2]/10,Datos_SD[3]/10,Datos_SD[4]/10);}

   	        		 if(pipe==1){estado=ESP8266_WriteChannel("EXNLVJJTBY17SM8V",Datos_SD_01[0]/10,Datos_SD_01[1]/10,Datos_SD_01[2]/10,Datos_SD_01[3]/10,Datos_SD_01[4]/10);}



   	        		    lcd_gotoxy(1, 1); printf_lcd("               ");
   	        		   	lcd_gotoxy(1, 2); printf_lcd("               ");
   	        		 	if(estado){
   	        		 		flag_WiFi=1;
   	        		 		caso=0;
   	        		 		busy=0;
   	        		 	    lcd_gotoxy(1, 1); printf_lcd("Uploadind Data  ");
   	        		 	    lcd_gotoxy(1, 2); printf_lcd("                ");
   	        		 	    delay();
   	        		 	} else{
   	       		 	        lcd_gotoxy(1, 1); printf_lcd("Fail Server     ");
   	    	        	    lcd_gotoxy(1, 2); printf_lcd("                ");
   	        		 		caso=0;
   	        		 		cont_fail++;
   	        		 		delay();
   	        		 	}

   	        		    if(cont_fail > Intentos){
   	        		    	flag_GPRS=1; flag_WiFi=0; cont_fail =0; caso=0; busy=0;
   	        		    }

   	        		    break;


   	        }

   	  }// fin flag_WIFi








}
  return 0;
}





