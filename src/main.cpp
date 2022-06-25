#include <M5Core2.h>
#include <GDTouchKeyboard.h>
#include "setup.h"


void setup() {
  M5.begin(); 

  


}




void loop() {

  WifiSetupScreen.run();
  
  String t = GDTK.run("test:",0xefe1);
  Serial.println(t);
  delay(1000);
  



}

