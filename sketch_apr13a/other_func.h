#ifndef OTHER_FUNC_H
#define OTHER_FUNC_H

// include library to read and write from flash memory
#include "EEPROM.h"
// define the number of bytes you want to access
#define EEPROM_SIZE 10000
#define ACS_Pin 13
float token_balance;
float token_balance1;
float High_peak,Low_peak;         //Variables to measure or calculate
float Amps_Peak_Peak, Amps_RMS;
boolean conType1 = false;

//some function to sample the current and calculate power consumption
void eeprom_adjust(int y,float q)
{
    
    //for balance
    if (y==0)
    {
        EEPROM.write(0,q);
        EEPROM.commit();
    //for consumption data
    }
    else if(y==1)
    {
        EEPROM.write(50,q);
        EEPROM.commit();
    }
    delay(500);
}
float power_adjust(float tokens_left)            //read_Amps function calculate the difference between the high peak and low peak 
{                           //get peak to peak value
  // High_peak = 0;      //We first assume that our high peak is equal to 0 and low peak is 1024, yes inverted
  // Low_peak = 4095;
  
  // uint32_t start_time = millis();
  // while((millis()-start_time) < 1000) //sample for 1 Sec//everytime a sample (module value) is taken it will go through test
  //     {
  //       float ACS_Value = analogRead(ACS_Pin); //We read a single value from the module

        
  //       if(ACS_Value > High_peak)                //If that value is higher than the high peak (at first is 0)
  //           {
  //             High_peak = ACS_Value;            //The high peak will change from 0 to that value found
  //           }
        
  //       if(ACS_Value < Low_peak)                //If that value is lower than the low peak (at first is 1024)
  //           {
  //             Low_peak = ACS_Value;             //The low peak will change from 1024 to that value found
  //           }
  //     }                                        //We keep looping until we take all samples and at the end we will have the high/low peaks values
      
  // Amps_Peak_Peak = High_peak - Low_peak;      //Calculate the difference
  // Amps_RMS = ((Amps_Peak_Peak/4095)*0.3536*5)/0.066;
  // tokens_left-=(Amps_RMS*240/(60*60*1000));
//   tokens_left-=(0.1);
  return tokens_left;

} 



#endif
