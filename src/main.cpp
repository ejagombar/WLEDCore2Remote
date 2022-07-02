#include <M5Core2.h>
#include <GDTouchKeyboard.h>
#include "WIFIsetup.h"
#include "WLEDpage.h"

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

  M5.Buttons.addHandler(getTabSelection, E_TOUCH);
  WLEDtabPage.run();
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
  for (int i = 0; i < maxNumofWLED; i++)
  {
    String wledSavedName = "wled";
    wledSavedName += i;
    char charBuf[50];
    wledSavedName.toCharArray(charBuf, 50);
    preferences.begin(charBuf, false);

    String ip = preferences.getString("ip", ""); 
    String name = preferences.getString("name", "");
    if (!(ip == "" || name == ""))
    {
      WLEDLights[i].loadData(i, ip, name);
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
  if (e.button == &M5.BtnA)
  {
    WLEDtabPage.run();
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