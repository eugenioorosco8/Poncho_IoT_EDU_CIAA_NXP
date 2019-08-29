/*
 * WorkApp.c

 *
 *  Created on: 13 jul. 2018
 *      Author: usuario
 */
#include "WorkApp.h"
#include "rtc.h"
//--------------------------------Variables y Arreglos Globales a este archivo----------------------------
#define VALORES 24
int HumAmb[VALORES]={0},TempAmb[VALORES]={0},HumSuelo[VALORES]={0},TempSuelo[VALORES]={0},Hora[VALORES]={0};
 char j=0;

//---------Funcion donde se descompone el paquete recibido via RF y se almacenan los ultimo 24 valores---

void Last_Values_App(int* Mediciones){
	/*Mediciones=[humedadAmb Tamb Hsuelo Tsuelo]*/


	if(j<VALORES){						//se Cargan los valores en primera pasada...
		HumAmb[j]=Mediciones[0]/10;
		Repeat_Values(HumAmb,j,Mediciones[0]/10); //se repite el ultimo valor hasta el final del arreglo
		TempAmb[j]=Mediciones[1]/10;
		Repeat_Values(TempAmb,j,Mediciones[1]/10);
		HumSuelo[j]=Mediciones[2]/10;
		Repeat_Values(HumSuelo,j,Mediciones[2]/10);
		TempSuelo[j]=Mediciones[3]/10;// 	de 0 A 23 ya se tienen los 24 valores
		Repeat_Values(TempSuelo,j,Mediciones[3]/10);
		Hora[j]=rtc_get_parametro(RTC_TIMETYPE_HOUR);
		j++;
	}

	if(j==VALORES){ 						//Rotacion de valores a la izquierda
		for(int n=0;n<(VALORES-1);n++){
			HumAmb[n]=HumAmb[n+1];
			TempAmb[n]=TempAmb[n+1];
			HumSuelo[n]=HumSuelo[n+1];
			TempSuelo[n]=TempSuelo[n+1];
			Hora[n]=Hora[n+1];
		}

		HumAmb[VALORES-1]=Mediciones[0]/10; 	//Se cargan los ultimos valores
		TempAmb[VALORES-1]=Mediciones[1]/10;
		HumSuelo[VALORES-1]=Mediciones[2]/10;
		TempSuelo[VALORES-1]=Mediciones[3]/10;
		Hora[VALORES-1]=rtc_get_parametro(RTC_TIMETYPE_HOUR);
	}
}
//----------------------------Funcion para repetir el ultimo valor hasta el final del arreglo-------------

void Repeat_Values(int* Variable, char j, int value){ //Uncicamente se usa cuando  j<VALORES
char i=0;
	for(i=j;i<(VALORES-1);i++){
		Variable[i]=value;
	}
}

//--Esta Funcion envia los punteros de los arreglos antes creados a Work_Bluetooth.c para ser usados por la interrupcion UART---

void Return_Pointer(int* HumAmbp,int*TempAmbp,int*HumSuelop,int*TempSuelop,int*Horap){	//entrega de punteros para ser usado en Work_Bluetooth.c al enviar los datos

	*HumAmbp=&HumAmb[0];
	*TempAmbp=&TempAmb[0];
	*HumSuelop=&HumSuelo[0];
	*TempSuelop=&TempSuelo[0];
	*Horap=&Hora[0];

}




