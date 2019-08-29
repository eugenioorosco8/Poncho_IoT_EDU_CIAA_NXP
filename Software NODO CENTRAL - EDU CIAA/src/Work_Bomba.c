/*
 * Work_Bomba.c
 *
 *  Created on: 1 ago. 2018
 *      Author: usuario
 */
#include "chip.h"
#include "Work_Bomba.h"

#define	LEVEL_CRITICAL	20
#define HUMEDAD_CRITICAL	20

int LevelMin=0; 	//Variable Global de este archivo para control de bomba


//--------------------------Funcion de evaluacion de condiciones de accionamiento de bomba-----------------

void Bomba_Riego(int Hum_Suelo, int Nivel_Tanque){
	 Chip_SCU_PinMux(6,12,MD_PUP,0);
	 Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT,2,8);

	 if ((Hum_Suelo/10 < HUMEDAD_CRITICAL) && (Nivel_Tanque > LevelMin )) {


		 Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, 2, 8);	//Bomba On
	}

	 if ((Hum_Suelo/10 > HUMEDAD_CRITICAL*2) || (Nivel_Tanque< LEVEL_CRITICAL )){

		 Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 2, 8);	//Bomba Off

	 }

}







void Ref_Level_App (int Level){
	LevelMin=Level;				//copia a variable local del archivo
}



