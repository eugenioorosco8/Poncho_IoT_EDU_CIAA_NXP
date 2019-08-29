/*
 * TriAc.h
 *
 *  Created on: 6 ago. 2018
 *      Author: samu_
 */

#ifndef TRIAC_H_
#define TRIAC_H_

#include "chip.h"

void Triac_Init( unsigned char desfaseje_fn);//

void Triac_Disparo( unsigned char angulo);

void PI_Init (float KI, unsigned char KP,unsigned char Tolerancia,unsigned char Zona_Muerta,float Ts);//

void PI_Value(int Temp);

void PI_Get_Ref(char REF);






#endif /* TRIAC_H_ */
