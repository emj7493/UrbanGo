// Versión para dos relés //

// Arduino 0 - Prueba //

#include <SoftwareSerial.h>
#include <stdlib.h>

int     pinRele1              = 2     ;
int     pinRele2              = 3     ;
int     pinBT                 = 12    ;
int     longCodigo            = 0     ;
int     longCodigo_max        = 36    ;
float   t_inic                        ;
float   t_fin                         ;
String  inputString_Serial    = ""    ;
String  inputString_BT        = ""    ;
String  codigoRele1          = "5c34a1d8-1a50-4caf-a382-b49af63ae4b1-0\n";
String  codigoRele2          = "5c34a1d8-1a50-4caf-a382-b49af63ae4b1-0\n";
boolean BTstring_Complete     = 0     ;
boolean Serialstring_Complete = 0     ;

SoftwareSerial BT(9, 10); // RX, TX


void setup()
{
// Definición de los pins usados para los relés
  pinMode(pinRele1, OUTPUT);
  pinMode(pinRele2, OUTPUT);
  pinMode(pinBT, OUTPUT);
  
  digitalWrite(pinRele1, HIGH);
  digitalWrite(pinRele2, HIGH);
  digitalWrite(pinBT, HIGH);
  
  // Comienzo de comunicaciones serie
  Serial.begin(9600);
  BT.begin(9600);
  
}

void loop()
{  
  // Funciones para detectar y recibir string por comunicaciones serie
  
  BTEvent();
  t_fin = millis();
  //longCodigo = 0;    
  
  if (t_fin - t_inic ==  1000)
    {   
        digitalWrite(pinBT, LOW);
        delay(500);
        digitalWrite(pinBT, HIGH);
    }
    
  // Funciones al recibir un string
  if (BTstring_Complete == 1)
  { 
    BTstring_Complete = 0;
    Serial.print(inputString_BT);
    RLcode1();
    RLcode2();
    
    inputString_BT = "";
    }
  
}

//Función que captura el string entrante por el puerto bluetooth y pone BTString_complete a 1 cuando se detecta un salto de linea

void BTEvent()
{ 
  while (BT.available())
  { 
    char inChar = (char)BT.read();
    inputString_BT += inChar;
    longCodigo++;

    Serial.print(longCodigo);
    
    if ( inChar == '\n' )
    { 
      BTstring_Complete = 1;
      Serial.print("String cogida");
      Serial.print(inputString_BT);
    }
    inputString_BT = "";
   }
}

// Funciones que comprueba si el codigo recibido es el correcto y actúa

void RLcode1()
{
 if (inputString_BT == 'x' + codigoRele1)
    { 
      Serial.print("String reconocido");
        t_inic = millis();
        digitalWrite(pinRele1, LOW);
        delay(750);
        digitalWrite(pinRele1, HIGH);
    }
    
    if (inputString_BT == codigoRele1)
    {   
        Serial.print("String reconocido");
        t_inic = millis();
        digitalWrite(pinRele1, LOW);
        delay(750);
        digitalWrite(pinRele1, HIGH);
    }
}

void RLcode2()
{
    if (inputString_BT == 'x' + codigoRele2)
    {   
      Serial.print("String reconocido");
        t_inic = millis();
        digitalWrite(pinRele2, LOW);
        delay(750);
        digitalWrite(pinRele2, HIGH);
    }
    
    if (inputString_BT == codigoRele2)
    {   
      Serial.print("String reconocido");
        t_inic = millis();
        digitalWrite(pinRele2, LOW);
        delay(750);
        digitalWrite(pinRele2, HIGH);
    }
}


