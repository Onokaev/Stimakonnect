#ifndef CORE_FUNCTIONS_H
#define CORE_FUNCTIONS_H

#include "other_func.h"
#include "myfunctions.h" 
#include "GSM.h"
#include "netSwitcher.h"


TaskHandle_t Task1;
TaskHandle_t Task2;
static uint8_t taskCoreZero = 0;
static uint8_t taskCoreOne  = 1;


void Task1code( void * pvParameters )
{
  // Serial.print("Task1 running on core ");
  // Serial.println(xPortGetCoreID());
  //theSwitch will choose between wifi or GSM

    //initial connection is by GSM. This is default. Though it takes time to set up a connection, it has to run first. Takes less than 3mins if there's totally
    // no connection.
    
    setup_GSM();           //function defined in GSM.h. This will initialize GSM and connect it to internet through gprs tech
    if(GprsConnected)      //this is a flag set if gprsConnected() returns true. it is set within the GSM function
    {
      use_gsm = true;
      use_wifi = false;
      mqtt.setServer(online_server, 1883);
      mqtt.setCallback(callback);  
      mqtt.subscribe("Jkuat-grid/house1/status/change");
      mqtt.subscribe("Jkuat-grid/house1/load_data_meter",1);     
    }  
    
    else   //if GprsConnected evaluates to false, then wifi connection is attempted. 
    {
      use_wifi = true;
      use_gsm = false;
      Serial.println("Setting up wifi");
      GprsConnected = false;
      setup_wifi();
    }
    
    while(true)
    {
      if(!netSwitch)  //if netswitch is false, use gsm
      {
        theLoop(mqtt);
      }
      else
      {
        theLoop(client_wifi);
      }     

      lcd.setCursor(0, 0);
      lcd.print("Balance : ");
      lcd.setCursor(10, 0);
      lcd.print(token_balance1);
      lcd.setCursor(0, 1);
      lcd.print("CONNECTED    ");
      /* code */
        delay(1000);
    } 
}



void Task2code( void * pvParameters ){
  // Serial.print("Task2 running on core ");
  // Serial.println(xPortGetCoreID());

  while(true){
    token_checker(token_balance1);
    token_balance1=power_adjust(token_balance1);
    token_balance=EEPROM.readFloat(0);
    if ((token_balance-token_balance1)>=0.1)
    {
      eeprom_adjust(0,token_balance1);
    }
    delay(1000);
  }
} 


void task_create()
{
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */                  
   delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    2,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */
     delay(500); 
}  

#endif
