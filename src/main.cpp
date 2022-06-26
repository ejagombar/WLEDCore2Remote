#include <M5Core2.h>
#include <GDTouchKeyboard.h>
#include "setup.h"


void setup() {
  M5.begin(); 

  


}




void loop() {


  // preferences.begin("wifiData", false);

  // String ssid = preferences.getString("ssid", ""); 
  // String password = preferences.getString("password", "");

  // if (ssid == "" || password == ""){
  //   Serial.println("No values saved for ssid or password");
  // }

  // Serial.println("SSID: "+ssid);
  // Serial.println("Password: "+password);

  auto [SSID , colour] = WifiSetupScreen.run();
  Serial.println("About to open keyboard");
  String password = GDTK.run(SSID+" Pass: ",colour,false);
  password = password.substring(SSID.length()+7,password.length());
  //String SSID = "D19A5F";
  //String password = "EFF2632173##";
  WifiConnectScreen.run(SSID,password);
  //delay(20000);
  
}

