#include <M5Core2.h>
#include <GDTouchKeyboard.h>
#include "WIFIsetup.h"
#include "WLEDpage.h"
#include "WLED.h"

#define maxNumofWLED 3

String SSID = "";
String password = "";
uint16_t colour = 0;
uint8_t screenVal = 1;  //0 = WLED page    1 = colour page      2 = settings
WLED WLEDLights[maxNumofWLED];


void checkForWifiData();
void setupProcess();
void checkForSavedWLED();

void getTabSelection(Event& e);

void setup() {
  M5.begin(); 
  checkForWifiData();
  checkForSavedWLED();
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
}



void getTabSelection(Event& e)
{
  Serial.println("A B or C pressed");
  WLEDtabPage.closeScreen();
  if (e.button == &M5.BtnA)
  {
    WLEDtabPage.openScreen();
  }
  else if (e.button == &M5.BtnB)
  {
    //colourPage.run();
  }
  else if (e.button == &M5.BtnC)
  {
    //settingsPage.run();
  }

}