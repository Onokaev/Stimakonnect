#ifndef netSwitch_h
#define netSwitch_h

#include "myfunctions.h"
//#include "GSM.h"
//#include "core_functions.h"
//#include "other_func.h"

int mycounter=0;
float initial_balance;

void theLoop(PubSubClient &theClient)
{
      if(!theClient.connected())
        {
          lcd.setCursor(10, 0);
          lcd.print(token_balance1);
          reconnect(theClient);
        }     
        initial_balance=EEPROM.readFloat(50);
        Serial.println(initial_balance);
        static char tb[7];
        dtostrf(token_balance1, 6, 2, tb);
        theClient.publish("Jkuat-grid/house1/balance", tb);
        theClient.publish("Jkuat-grid/house1/status/now", relayer);
        lcd.setCursor(10, 0);
        lcd.print(token_balance1);
        theClient.loop();
        // ten second delay
        if (mycounter==10)
        {
          //publish consumtpion data and adjust the eeprom value
          float used_up = (initial_balance - token_balance1);
          if (used_up>0)
          {
            static char tb1[7];
            dtostrf(used_up , 6, 2, tb1);
            theClient.publish("Jkuat-grid/house1/consumed", tb1 );
          }
          
          eeprom_adjust(1,token_balance1);
           mycounter=0;
        } 
        mycounter+=1;
}

//this function switches connection between wifi and gsm based on the one that is available.
//the flag netSwitch = false, GSM is the gateway in use, else if the Switch= true WIFI is the default gateway

#endif
