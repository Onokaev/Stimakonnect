#ifndef GSMFunctions_H
#define GSMFunctions_H

#define pass(void)
#define TX_Pin 25
#define RX_Pin 26

#include <SoftwareSerial.h>
SoftwareSerial SerialAT(RX_Pin, TX_Pin);
const int BAUD_RATE = 115200;   //serial speed of sim800l and monitor

#define TINY_GSM_MODEM_SIM800
//define how you intend to connect to internet
#define TINY_GSM_USE_GPRS true
#include <TinyGsmClient.h>
TinyGsm modem(SerialAT);
TinyGsmClient gsmClient(modem);
PubSubClient mqtt(gsmClient);

// Your GPRS credentials, if any
const char apn[] = "";
const char gprsUser[] = "";
const char gprsPass[] = "";
boolean GprsConnected = false;

void setup_GSM()
{
  //modem.restart();
  modem.init();
  String modemInfo = modem.getModemInfo();
  Serial.print("Modem Info: ");
  Serial.println(modemInfo);
  Serial.print("Waiting for network...");
    if(!modem.waitForNetwork()) 
    {
      Serial.println(" fail");
      delay(1000);
    }
    else
    {
      Serial.println(" success");
    } 
    if(modem.isNetworkConnected()) 
    {
      Serial.println("Network connected");
    }   
    
//#if TINY_GSM_USE_GPRS
//  // GPRS connection parameters are usually set after network registration
//    Serial.print(F("Connecting to "));
//    Serial.print(apn);
//    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) 
//    {
//      Serial.println(" fail");
//      delay(2000);
//    }
//    else
//    {
//      Serial.println(" success");
//    }
//    //Serial.println(" success");
//
//  if (modem.isGprsConnected()) 
//  {
//    GprsConnected = true;
//    Serial.println("GPRS connected");
//  }
//#endif
}


#endif
