/*

 * TriAc.c
 *
 *  Created on: 6 ago. 2018
 *      Author: samu_
 */
#include "TriAc.h"
#define TICKRATE_HZ 10000
unsigned char flag=0,cont_sinc=0,angulo=0, desfase=0;
unsigned char TOLERANCIA,ZONA_MUERTA,Kp;
float TS=0,Ki;
char ref=35;


void Triac_Disparo( unsigned char angulo_fn){
	angulo=(80-(angulo_fn*0.8));

}

void PI_Value( int Temp){
	static float e=0,e1=0,integral=0,u=0, integral_1=0;
	int U=0;
	Temp=(int)Temp/10;
	e= ref-Temp;
	integral= integral_1 + (TS*0.5*(e+e1));
	u= Kp*e + Ki* integral;

    if((e)<TOLERANCIA)
    {
     integral=0.0;
     u=0.0;
    }else{
    	U= (int) u + ZONA_MUERTA;
    	if(U>100){ U=100;}

    }
    Triac_Disparo(U);

    e1=e;
    integral_1 =integral;

}

void PI_Get_Ref(char REF){
	ref= REF;
}

void PI_Init (float KI, unsigned char KP,unsigned char Tolerancia,unsigned char Zona_Muerta,float Ts){
	Ki=KI;
	Kp=KP;
	TOLERANCIA=Tolerancia;
	ZONA_MUERTA=Zona_Muerta;
	TS=Ts;
}

void Triac_Init(unsigned char desfaseje_fn){
//***********************************************************************************
//********************************* TIMER 0  ****************************************
//***********************************************************************************

		desfase= desfaseje_fn;
		Chip_SCU_PinMux (6,5,MD_PUP,FUNC0); // pin salida
		Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT,3, 4);

		uint32_t timerFreq;



		/* Enable timer 1 clock and reset it */
		Chip_TIMER_Init(LPC_TIMER1);
		Chip_RGU_TriggerReset(RGU_TIMER1_RST);
		while (Chip_RGU_InReset(RGU_TIMER1_RST)) {}

		/* Get timer 1 peripheral clock rate */
		timerFreq = Chip_Clock_GetRate(CLK_MX_TIMER1);

		/* Timer setup for match and interrupt at TICKRATE_HZ */
		Chip_TIMER_Reset(LPC_TIMER1);
		Chip_TIMER_MatchEnableInt(LPC_TIMER1, 1);
		Chip_TIMER_SetMatch(LPC_TIMER1, 1, (timerFreq / TICKRATE_HZ));
		Chip_TIMER_ResetOnMatchEnable(LPC_TIMER1, 1);
		Chip_TIMER_Enable(LPC_TIMER1);

		/* Enable timer interrupt */
		NVIC_EnableIRQ(TIMER1_IRQn);
		NVIC_ClearPendingIRQ(TIMER1_IRQn);

//**************************************************************************************
//*******************  INTERRUPCION ****************************************************
//**************************************************************************************
			Chip_SCU_PinMux(6,8,MD_PUP|MD_EZI|MD_ZI,FUNC4);
			Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 5, 16);

			//CONFIGURACION DE PINES GPIO COMO PINES DE INTERRUPCION.
			Chip_SCU_GPIOIntPinSel(1, 5, 16); // Configura un pin GPIO como un pin de interrupciÃƒÂ³

			//CONFIGURACION DE MODO DE INTERRUPCION
			Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT,PININTCH1);
			Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT,PININTCH1);

			//CONFIGURA EL NVIC limpieza flag de interrupcion NVIC
			Chip_PININT_ClearRiseStates(LPC_GPIO_PIN_INT,1);

			//LIMPIEZA Y HABILITACION DE FLAG IRQ
			NVIC_ClearPendingIRQ(PIN_INT1_IRQn);
			NVIC_EnableIRQ(PIN_INT1_IRQn);
}

//************************************************************************************************************
//******************************* Funcion de Interrupcion ****************************************************
//************************************************************************************************************
void GPIO1_IRQHandler(void){
	    //LIMPIA BANDERA DE INTERRUPCION

		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT,PININTCH1);
		NVIC_ClearPendingIRQ(PIN_INT1_IRQn);
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,5,16);


		flag=1;
		cont_sinc=0;
}
//*************************************************************************************************************
//**************************** Funcion del Timer ****************************************************************
//**************************************************************************************************************

void TIMER1_IRQHandler(void)
{
					static char contador=0,flag_sinc=0,f=1;

					if (Chip_TIMER_MatchPending(LPC_TIMER1, 1)) {
						Chip_TIMER_ClearMatch(LPC_TIMER1, 1);

					}
//*************************************************************


					  if(flag){ cont_sinc ++; }

					  if(flag && (cont_sinc >= 12)) {
					    flag=0;
					    flag_sinc= 1;
					    contador=0;
					  }
					  if( flag_sinc ){
						  contador++;
						  if( (contador >= angulo) && (contador <=  angulo+2 ) ){
						  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,3,4);
						  }
						  else {Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,3,4); }

					  if(contador >=  78 ){ flag_sinc = 0; Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,3,4); }
					  }
}




