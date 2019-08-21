#include "Arduino.h"
#include "frecuencia.h"

frecuencia::frecuencia(int pin)
{
    _pin=pin;
    
}

void frecuencia::begin()
{
     pinMode(_pin,INPUT);
}

void frecuencia::Calibracion(int maximo,int minimo)
{
   _max=maximo; 
   _min=minimo;
}

int frecuencia::get()
{
   long timeH=0;//tiempo pulso HIGH
   long timeL=0;//tiempo pulso LOW
   float Periodo=0;// suma de time LOW+HIGH , 1s = 1000000 us
   
   int Suma=0;
   int Cont=0;

  for (int i=0; i<10; i++){
    
    timeH=pulseIn(_pin,HIGH,90000);//90000 es el tiempo que espera al pulso, es aprox 10Hz como minimo. Si es menor entrega un cero la fn pulseIn
    timeL=pulseIn(_pin,LOW,90000);
    
  
     if ((timeH !=0)&& (timeL !=0))
     {  
        Periodo=((timeH+timeL)*0.000001); 
        _f= 1/Periodo; 
     }
     else { _f=0; }


    
       if ((_f <= _max)&&(_f >= _min))  { Suma=(Suma + _f); Cont++; }
      
  }
     if( Cont > 0 ){ _f=(Suma/Cont); return(_f); }
     else{ return(-1); }
  

}

  