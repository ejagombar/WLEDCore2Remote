#include "main.h"

void setup() {
  M5.begin(); 
  checkForWifiData();
  checkForSavedWLED();
  cpPage.generateColourPicker();
  M5.BtnA.addHandler(getTabSelection, E_TOUCH);
  M5.BtnB.addHandler(getTabSelection, E_TOUCH);
  M5.BtnC.addHandler(getTabSelection, E_TOUCH);
  WLEDtabPage.importWLEDData(WLEDLights);
  WLEDtabPage.openScreen();
}



void checkForWifiData() //-----------------------------------checkForWifiData-------------------------------------
{
  preferences.begin("wifiData", false);

  SSID = preferences.getString("ssid", ""); 
  password = preferences.getString("password", "");

  preferences.end();

  Serial.println("SSID: " + SSID);
  Serial.println("Password: " + password);

  if (SSID == "" || password == "")
  {
    Serial.println("No values saved for ssid or password");
    setupProcess();
  }
  else
  {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(SSID.c_str(), password.c_str());
    int timeOut = 0;
    while ((WiFi.status() != WL_CONNECTED) && (timeOut < 25)) 
    {
      delay(1000);
      timeOut++;
      if (timeOut >= 25)
      {
        setupProcess();
      }
    }
    
  }  
}

void setupProcess() //-------------------------------------setupProcess---------------------------------------
{
  bool connected = false;
    while (connected == false)
    {
      std::tie(SSID , colour)= WifiSetupScreen.run();
      String password = GDTK.run(SSID+" Pass: ",colour,false);
      password = password.substring(SSID.length()+7,password.length());
      connected = WifiConnectScreen.run(SSID,password);
    }
}



void checkForSavedWLED() //-------------------------------------checkForSavedWLED---------------------------------------
{
    preferences.begin("wled1", false);
    preferences.putString("ip", "192.168.1.172"); 
    preferences.putString("name", "Eds Room");
    preferences.putUShort("colour", RED);
    preferences.end();
    preferences.begin("wled0", false);
    preferences.putString("ip", "192.168.1.165"); 
    preferences.putString("name", "Bed");
    preferences.putUShort("colour", RED);
    preferences.end();

  for (int i = 0; i < maxNumofWLED; i++)
  {
    String wledSavedName = "wled";
    wledSavedName += i;
    char charBuf[50];
    wledSavedName.toCharArray(charBuf, 50);
    Serial.print(wledSavedName);
    preferences.begin(charBuf, false);

    String ip = preferences.getString("ip", ""); 
    String name = preferences.getString("name", "");
    uint16_t colour = preferences.getUShort("colour", 0);
    if (!(ip == "" || name == ""))
    {
      WLEDLights[i].loadData(i, ip, name,colour);
      Serial.print(WLEDLights[i].name());
    }

    preferences.end();
  }
}

void loop() //-------------------------------------loop---------------------------------------
{
  M5.update();
  if (M5.Touch.ispressed()) {
    screenPressed();
  }
}

void screenPressed(){
  if (screenState == colourPickerTab) {
    TouchPoint_t coordinate = M5.Touch.getPressPoint();
    if ((coordinate.x >= 0) && (coordinate.y >= 0)){
      cpPage.selectColour(coordinate.x,coordinate.y);
      colour = cpPage.selectedColour();
      Serial.printf("coord: %d %d",coordinate.x,coordinate.y);
      cpPage.drawSelectedColour();
    }
  }

}



void getTabSelection(Event& e)
{
  WLEDtabPage.closeScreen();
  if (e.button == &M5.BtnA)
  {
    screenState = wledTab;
    WLEDtabPage.openScreen();
  }
  else if (e.button == &M5.BtnB)
  {
    screenState = colourPickerTab;
    cpPage.drawColourPicker();
  }
  else if (e.button == &M5.BtnC)
  {
     screenState = settingsTab;
    //settingsPage.run();
  }

}