/*
 * WorkSD.h

 *
 *  Created on: 2 jul. 2018
 *      Author: usuario
 */
#include "integer.h"

#ifndef WORKSD_H_
#define WORKSD_H_
#endif /* WORKSD_H_ */

//---------------Funciones de Inicializacion de Hardware del Modulo SD---------

void initHardwareSD(void);
void SysTick_Handler(void);



//-----------------Funciones de Manejo de Archivos en SD-----------------------

void Open_Write_SD( const void* Escribir, UINT Tam,const void* FILENAME);
void Open_Read_SD(const void* Leer, UINT Tam,const void* FILENAME);
void Write_MeasurementsSD(int *Mediciones,int N_Datos,unsigned char pipe);




