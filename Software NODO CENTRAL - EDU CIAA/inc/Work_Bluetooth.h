#ifndef WORK_BLUETOOTH_H_
#define WORK_BLUETOOTH_H_
#endif /* WORK_BLUETOOTH_H_ */

#include "chip.h"
#include "TriAc.h"

void Bluetooth_Init(void);

void Bluetooth_GetData1(int *Datos_Nodo1, unsigned char n_datos); //para obtener datos para la app nodo 1
void Bluetooth_GetData2(int *Datos_Nodo2, unsigned char n_datos);// pra obtener datos para la app nodo 2

