#include <M5Core2.h>
#include <GDTouchKeyboard.h>
#include "setup.h"


void setup() {
  M5.begin(); 

  


}




void loop() {


  auto [SSID , colour] = WifiSetupScreen.run();
  String t  = GDTK.run(SSID+" Pass: ",colour,false);
  Serial.println(t);
  delay(1000);
  



}

