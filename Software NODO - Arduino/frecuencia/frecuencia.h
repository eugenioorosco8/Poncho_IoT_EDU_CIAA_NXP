#ifndef frecuencia_h
#define frecuencia_h
#include "Arduino.h"

class frecuencia{
 
public:
 
 frecuencia(int pin);
 void begin();
 void Calibracion (int maximo,int minimo);
 int get();
 

private:
  int _pin, _f, _max, _min;


};

#endif