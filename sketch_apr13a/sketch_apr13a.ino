#include "core_functions.h"

void setup()
{
//  EEPROM.begin(EEPROM_SIZE);
//  Serial.begin(115200);
  general_setup();
  task_create();
  token_checker(token_balance);
////  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
//eeprom_adjust(0,234.542);
//eeprom_adjust(1,240.32);
}
void loop() {
//  Serial.println(EEPROM.readFloat(50));
//  Serial.println(EEPROM.readFloat(0));
//  delay(2000);

}
