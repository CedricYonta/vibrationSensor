/*
  Titre      : Titre du programme
  Auteur     :https://wiki.dfrobot.com/Analog_Piezo_Disk_Vibration_Sensor__SKU_DFR0052_#target_4
  Date       : 27/11/2021
  Description: Une description du programme
  Version    : 0.0.1
*/



#include <Arduino.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"


int GreenLED = 3;
int RedLED = 2;

bool  StatusFerme = true ;
bool StatusOuvert = false ;



const int analogPin = A1;



void setup()
{
  Serial.begin(9600); //

 wifiConnect();                  //Branchement au réseau WIFI
  MQTTConnect();                  //Branchement au broker MQTT


  pinMode(analogPin,INPUT); 
   pinMode(GreenLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
}
void loop()
{
      int val;
      val=analogRead(analogPin);//Connect the sensor to analog pin 0

if(val < 20){
    digitalWrite(RedLED, HIGH);
    digitalWrite(GreenLED, LOW);
     StatusFerme = true ;
     StatusOuvert =  false ;

    
  }else if(val >=20){  
    digitalWrite(GreenLED, HIGH);
    digitalWrite(RedLED, LOW);
    StatusFerme =  false ;
    StatusOuvert =  true ;

    
  }


      Serial.print("La valeur de vibration obtenue ");
      Serial.println(val,DEC);//

      appendPayload("Vibration",val );  //Ajout de la donnée température au message MQTT
  sendPayload();                                   //Envoie du message via le protocole MQTT

  appendPayload("Statutferme", StatusFerme);
 appendPayload("Statutouvert", StatusOuvert);

      delay(1000);
}
