


//**********************************************************
//              PANTALLA LCD 16x02
//**********************************************************
#define RS_PIN   A1    
#define EN_PIN   A2   //A2 EN NODO 01 // A0 en nodo 2
#define D4_PIN   4   
#define D5_PIN   5    
#define D6_PIN   6  
#define D7_PIN   7  
#include "LiquidCrystal.h"
LiquidCrystal lcd(RS_PIN,EN_PIN,D4_PIN,D5_PIN,D6_PIN,D7_PIN); //( RS, EN, d4, d5, d6, d7)

//**********************************************************
//                MODULO RF24L01 RF
//**********************************************************
#include "SPI.h"
#include "Mirf.h"
#include "MirfHardwareSpiDriver.h"
#include "nRF24L01.h"
signed char TS_int,TA_int,HA_int,TS_coma,TA_coma,HA_coma,HS_coma,HS_int; //Variables de sensores a trasmitir--> Parte entera y decimal
signed char Datos[8]={0};
unsigned char msj[8]={0};

//***********************************************************
//           HUMEDAD Y TEMPERATURA AMBIENTE DHT22
//***********************************************************
#include "DHT.h" //cargamos la librería DHT
#define DHTPIN 2 //Seleccionamos el pin en el que se //conectará el sensor
#define DHTTYPE DHT22 //Se selecciona el DHT22 (hay //otros DHT)
DHT dht(DHTPIN, DHTTYPE); //Se inicia una variable que será usada por Arduino para comunicarse con el sensor


//************************************************************
//                Frecuencia del NE555
//************************************************************
#include "frecuencia.h"
#define MaxFrecuencia 100000
#define MinFrecuencia 100
#define Valor_Critico 9000    // valor critico para empezar el riego
#define TiempoEsperaLectura 120 //tiempo de riego mas el tiempo qUE espera la lectura del sensor
#define Pin_rele_hz     3   //pin D3 para accionamiento del rele
#define FrecuenciaPin   A2   //A0 NODO 1   //A2 NODO 2
frecuencia frecuencia(FrecuenciaPin);
int frec=1;

//************************************************************
//              TEMPERATURA DEL SUELO 
//************************************************************
#include <OneWire.h>
#include <DallasTemperature.h>
#define Pin_temp_suelo 8 //D8 pin de lectura temperatura del suelo
OneWire ourWire(Pin_temp_suelo);
DallasTemperature sensors(&ourWire);


//************************************************************
//                        Timer 
//************************************************************
#include <MsTimer2.h>
char flag=1, caso=1, flag_actualizar=0;
int suelo,temp_suelo;  //variables del suelo
int h,t;  //variables ambientales

//************************************************************
//                    Modulo GSM 
//************************************************************
char phone_no[]="5492644440962";              
void enviarSMS(int t,int h, int suelo, int temp_suelo,int reservorio);
char Flag_SMS=0;



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//         SETUP                            SETUP                         SETUP
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void setup() {
//**************** Display LCD ************************************
   lcd.begin(16,2);// Segun el LCD empleado   
   lcd.setCursor(0, 0); 
   lcd.print(" TESIS 2019 ");
   delay(3000);
   lcd.clear();
   lcd.setCursor(0, 0); 
   lcd.print("Julian,Juan M.");
   delay(3000);
   lcd.clear();
   lcd.setCursor(0, 0); 
   lcd.print("Mateo,Samuel");
   delay(3000);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(" Inicializando... ");
   delay(3000);
 
//***********************  Modulo GSM A6 ********************************
  Serial.begin(115200);                       //Iniciamos una instancia de la librería SoftwareSerial
  Serial.print("AT+CMGF=1\r");               //Configuramos el módulo para trabajar con los SMS en modo texto
  delay(1000);                               //Pausa de 1 segundo
  Serial.print("AT+CNMI=2,2,0,0,0\r");      //Configuramos el módulo para que nos muestre los SMS recibidos por comunicacion serie
  delay(1000);   
//******************* Modulo RF *********************************************

 Mirf.cePin =9;
 Mirf.csnPin = 10;
 Mirf.spi= &MirfHardwareSpi;
 Mirf.init();
 Mirf.payload = 8;
 Mirf.channel = 90;
 Mirf.setRADDR((byte *)"TX_01");
 Mirf.config();
 Mirf.configRegister(RF_SETUP,0x06);

//*******     INICIALIZACION DE SENSORES ***************************
  dht.begin(); //Se inicia el sensor de humedad y temperatura ambiente
  sensors.begin();// inicia sensor temp del suelo     
  
//************** FRECUENCIA HZ *************************************
  frecuencia.begin();
  frecuencia.Calibracion(MaxFrecuencia, MinFrecuencia);
  
//*************** Rele leer frecuencia ****************************
  pinMode(Pin_rele_hz, OUTPUT);

 //**************** Timer ******************************************
   MsTimer2::set(5000, timerIsr);
   MsTimer2::start();
   //pinMode(13,OUTPUT);
  
   

}

void loop() {

  //   Verifica si llego un mensaje de Texto
  
  if (Serial.available() ){   
   
    String Comando = Serial.readString(); //Los almacenamos en la variable Comando
     if(Comando.indexOf("get")>=0){                  //Si la variable Comando contiene la palabra ON
        enviarSMS(t,h,suelo,temp_suelo,56);
     }
  }
 
  

if(flag){// flag de interrupcion que se activa cada 10 seg

     flag=0;
     h = dht.readHumidity(); //Se lee la humedad ambiente
     t = dht.readTemperature(); //Se lee la temperatura ambiente

//      TEMPERATURA DEL SUELO DS18B20

    sensors.requestTemperatures();
    temp_suelo = sensors.getTempCByIndex(0); //se lee temperatura del suelo
    
//    HUMEDAD DEL SUELO 
    digitalWrite(Pin_rele_hz, HIGH); //Acciono el rele de sensado
    delay(100);
    //frec =abs ( frecuencia.get() );

  
    frec=pulseIn(A2,HIGH);// Mide ele tiempo en alto //A0 NODO 1   //A2 NODO 2
    
    suelo=  -0.4*frec + 140; // CALIBRACION DEL SENSOR
    if(suelo > 99) suelo=99;
    if(suelo < 0) suelo=0;
    digitalWrite(Pin_rele_hz, LOW); //Apago el rele de sensado
    delay(100);
// ----------------------- ENVIAR DATOS POR RF-------------------------------
      Datos[0]= (char)temp_suelo;
      Datos[2]= (char)t;
      Datos[4]= (char)h;
      Datos[6]= (char)suelo;

      if(temp_suelo < 0){
      Datos[1]=((int)(temp_suelo*-10))%10;
      }else Datos[1]=((int)(temp_suelo*10))%10;

      if(t < 0){
      Datos[3]=((int)(t*-10))%10;
      }else Datos[3]=((int)(t*10))%10;
      
      Datos[5]=((int)(h*10))%10;
      Datos[7]=((int)(h*10))%10;

      Mirf.setTADDR((byte *)"TX_01");// CONFIGURA EL MODULO COMO TRASMISOR
      //ahora vamos a emitir
      Mirf.send(Datos);// ENVIA LOS DATOS

      //esperamos a que termine de emitir
       while( Mirf.isSending() ) ;
       
       if((Flag_SMS==0)&& ( (temp_suelo < 0)||(suelo < 30) ) ){
        Flag_SMS=1;   
        enviarSMS(t,h,suelo,temp_suelo,56);
       }
        if ((temp_suelo > 0)&&(suelo > 30)){Flag_SMS =0;}
       
}
//-----------------------------------------------
  if(flag_actualizar){// ACTUALIZA DATOS LCD
    switch(caso){
      case(1):
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("TEMP_AMBIENT="); lcd.print(t); lcd.print('C');
        lcd.setCursor(0, 1);
        lcd.print("HUM_AMBIENT= ");  lcd.print(h);  lcd.print('%');
        
        break;

    case(0):
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("TEMP_SUELO ="); lcd.print(temp_suelo); lcd.print('C');
        lcd.setCursor(0, 1);
        lcd.print("HUM_SUELO ="); lcd.print(suelo); lcd.print('%');
       
        break;
    }
    flag_actualizar=0;
    
  }
  
}
//************************************************************************
//                  Funcion del Timer
//************************************************************************
void timerIsr() { 
  static char cont=0,cont2=0;
     cont++;
     //flag_actualizar=1;
     cont2++;
     
     if(cont >= 2){
     flag=1; //bandera de lectura de sensores
     cont=0; //resetea contador de 10 segundo
     
     
     if(caso){    //Actualiza datos del suelo
      caso=0;
      flag_actualizar=1;
      }
     else {     //Actualiza datos de ambiente
      caso=1;
     flag_actualizar=1;
     }
     }
     
      if (cont2>10){ //Envio de SMS cada 50 segundos
        cont2=0;
         enviarSMS(t,h,suelo,temp_suelo,56);
      }
     
}
//*************************************************************************
//                         Enviar SMS
//*************************************************************************
void enviarSMS(int t,int h,int suelo,int temp_suelo,int reservorio){
   char Hum_Amb[3],Temp_Amb[3],Temp_Suelo[3],Hum_Suelo[3],Reservorio[3];
   reservorio=56;
   /*
   Serial.print("AT+CMGF=1\r");
   delay(1000);
   
   Serial.print("AT+CNMI=1,2,0,0,0\r"); 
   delay(1000);
*/
   Hum_Suelo[0]= (int)48 + (suelo/10); 
   Hum_Suelo[1]= (int)48+(suelo%10);
       
   Hum_Amb[0]= (int)48 + (h/10); 
   Hum_Amb[1]= (int)48+(h%10);

   Temp_Amb[0]= (int)48+(t/10); 
   Temp_Amb[1]= (int)48+(t%10); 

   Temp_Suelo[0]= (int)48+(temp_suelo/10); 
   Temp_Suelo[1]= (int)48+(temp_suelo%10); 

   Reservorio[0]= (int)48+(reservorio/10); 
   Reservorio[1]= (int)48+(reservorio%10); 

   
   Serial.println("AT+CMGF=1");
   delay(2000);
   Serial.print("AT+CMGS=\"");
   Serial.print(phone_no);
   Serial.write(0x22);
   Serial.write(0x0D); 
   Serial.write(0x0A); 
   delay(2000);
   Serial.print(Hum_Amb[0]);
   Serial.print(Hum_Amb[1]);
   Serial.print(';');

   Serial.print(Temp_Amb[0]);
   Serial.print(Temp_Amb[1]);
   Serial.print(';');

   Serial.print(Hum_Suelo[0]);
   Serial.print(Hum_Suelo[1]);
   Serial.print(';');

   Serial.print(Temp_Suelo[0]);
   Serial.print(Temp_Suelo[1]);
   Serial.print(';');

   Serial.print(Reservorio[0]);
   Serial.print(Reservorio[1]);
   Serial.print(';');

   Serial.print("sensores");
   Serial.println (char(26));
   delay(1000);
   Serial.println (char(26));
}
