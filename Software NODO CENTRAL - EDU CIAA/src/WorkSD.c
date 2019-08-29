/*
/ * WorkSD.c
 *
 *  Created on: 2 jul. 2018
 *      Author: usuario
 */


#include "WorkSD.h"
#include <chip.h>
#include "ff.h"
#include <diskio.h>
#include <string.h>
#include "rtc.h"
#include "lcd.h"
//----------------------------Constantes globales de este archivo--------------------

#define SD_ON()		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,5,15);
#define SD_OFF() 	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,5,15);
#define DELAY()		for(uint32_t i=0;i<10000000;i++);
#define LED_ON() 	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,0,14);
#define LED_OFF()	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,0,14);

//------------Variables necesarias para crear archivos y funciones Fatfs -----------

static uint32_t ms_ticks;  /**< 1ms timeticks counter */
static FATFS fs;           /**< FatFs work area needed for each volume */
static FIL fp;             /**< File object needed for each open file */
UINT nbytesW,nbytesR;


//-----------------------------Funciones de Inicializacion de Hardware del Modulo SD-----------
 void initHardwareSD(void){
	//Board_Init();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);


	/* SPI configuration- CONFIGURACION DE PINES GPIO SD */
	Chip_GPIO_Init(LPC_GPIO_PORT); //Inicializo GPIO
	Chip_SCU_PinMuxSet(0xf, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC0)); /* CLK0 */
	Chip_SCU_PinMuxSet(0x1, 3, (SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC5)); /* MISO1 */
	Chip_SCU_PinMuxSet(0x1, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC5)); /* MOSI1 */

	Chip_SCU_PinMuxSet(0x6, 7, (SCU_MODE_PULLUP | SCU_MODE_FUNC4)); /* CS1 configured as GPIO0 */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 5, 15); //Chip Select en GPIO0
	SD_OFF(); // Asegura apagado de modulo SD.

// Leds indicadores de acceso a SD
	 Chip_SCU_PinMux(2,10,MD_PUP,0);
	 Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,0,14);
	 LED_OFF();

	Chip_SSP_Init(LPC_SSP1);
	Chip_SSP_Enable(LPC_SSP1);





}

 void SysTick_Handler(void){
 	ms_ticks++; //Interrumpe el Timer cada 1ms

 	if (ms_ticks >= 10) {
 		ms_ticks = 0;
 		disk_timerproc();   /* Disk timer process - Se llega a los 10ms*/
 	}
 }



 /*:::::::::::::::::::::::Funciones de Manejo de Archivos en SD :::::::::::::::::::::*/

 //-------------------------Funcion para escritura de archivo en SD-----------------

 void Open_Write_SD(const void* Escribir, UINT Tam,const void* FILENAME){

	 	 SD_ON();	//Enciendo el modulo CS

	 /* Give a work area to the default drive */

	 	if (f_mount(&fs, "", 0)!=FR_OK) {
	 		/* If this fails, it means that the function could
	 		 * not register a file system object.
	 		 * Check whether the SD card is correctly connected */
	 		/* La tarjeta no esta montada en el modulo SD*/


	 	}

	 	/* Create/open a file, then write a string and close it */
	 	FRESULT a;
	 	a=f_open(&fp, FILENAME, FA_WRITE | FA_OPEN_APPEND);

	 		if (f_open(&fp, FILENAME, FA_WRITE | FA_OPEN_APPEND) == FR_OK) {
	 			f_write(&fp,Escribir,Tam,&nbytesW);
	 			f_close(&fp);

	 			if (nbytesW == Tam) { //verificacion escritura efectiva con la esperada
	 				LED_ON()
	 				 DELAY()
	 				 LED_OFF()
	 				}
	 		}


	 		SD_OFF();	//Apago el modulo CS


 }

//------------------------Funcion de Lectura de archivo en SD-------------------------------------

 void Open_Read_SD (const void* Leer, UINT Tam,const void* FILENAME){

	 SD_ON();
		 /* Give a work area to the default drive */
		 	if (f_mount(&fs, "", 0) != FR_OK) {
		 		/* If this fails, it means that the function could
		 		 * not register a file system object.
		 		 * Check whether the SD card is correctly connected */
		 		/* La tarjeta no esta montada en el modulo SD*/

		 	}

		 	if (f_open(&fp, FILENAME, FA_OPEN_EXISTING| FA_READ) == FR_OK) {
	 			f_read(&fp,Leer,Tam,&nbytesR);
	 			f_close(&fp);

	 			if (nbytesR == Tam) { //verificacion de cantidad efectiva leida con la esperada

	 			}


	 }
		 	//SD_OFF();

}

 //-----------------Funcion Para armado de paquete de datos a escribir sobre archivo SD--------------

 void Write_MeasurementsSD(int *Mediciones,int N_Datos, unsigned char pipe){



	 static unsigned int cont=0;
	 int hora,minutos,segundos;
	 char glue[10], Escritos[30];

	 /*Mediciones=[humedadAmb Tempamb Humsuelo Tempsuelo]*/


	 	cont++;//conteo de mediciones

	 	hora=rtc_get_parametro(RTC_TIMETYPE_HOUR);
	 	minutos=rtc_get_parametro(RTC_TIMETYPE_MINUTE);
	 	segundos=rtc_get_parametro(RTC_TIMETYPE_SECOND);

	 	itoa(hora,glue,10);
	 		if(hora<10){
	 			glue[1]=glue[0];
	 			glue[0]='0';
	 			glue[2]='\0';
	 		}
	 		strcpy(Escritos,glue);//Hora
	 		strcat(Escritos,":");

	 		itoa(minutos,glue,10);
	 		if(minutos<10){
	 			glue[1]=glue[0];
	 			glue[0]='0';
	 			glue[2]='\0';

	 			}
	 		strcat(Escritos,glue); //Minutos
	 		strcat(Escritos,":");

	 		itoa(segundos,glue,10);
	 		if(segundos<10){
	 			glue[1]=glue[0];
	 			glue[0]='0';
	 			glue[2]='\0';
	 			}
	 		strcat(Escritos,glue);	//Segundos
	 		strcat(Escritos,"\t");


	 		for(int i=0;i<N_Datos;i++){
	 			itoa(Mediciones[i],glue,10);
	 			strcat(Escritos,glue);
	 			strcat(Escritos,"\t"); //Mediciones

	 		}

	 		itoa(cont,glue,10);
	 		strcat(Escritos,glue);		//Contador de Mediciones
	 		strcat(Escritos,"\r\n"); 	//retorno de carro

	 		if (pipe==0){
	 			lcd_gotoxy(1, 1);
	 		    printf_lcd("Save in SD N1   ");
	 		    Open_Write_SD(Escritos,strlen(Escritos), "nodo1.txt"); //Paquete listo se envia a escribir sobre SD



	 		}
	 		if (pipe==1){
	 			 lcd_gotoxy(1, 1);
	 			 printf_lcd("Save in SD N2   ");
	 		    Open_Write_SD(Escritos,strlen(Escritos), "nodo2.txt");



	 		}

 }









