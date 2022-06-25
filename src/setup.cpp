#include "setup.h"


void _buttonEvent(Event& e);

WifiSetup::WifiSetup()
{

}

WifiSetup::~WifiSetup()
{

}

String WifiSetup::run()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(200);
  WifiSelectionScreen();

  while(gotSSID == false)
  {
    M5.update();
  }

  return SSID;
}

uint16_t WifiSetup::RGB16BIT(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint16_t)((r>>3)<<11)|((g>>2)<<5)|(b>>3));
}

uint16_t WifiSetup::WifiStrengthTo16BitColour(int strength)
{
  const int minVal = 50;
  const int maxVal = 100;
  float mappedStrength;

  strength = abs(strength);

  if (strength < minVal) {mappedStrength = 0;}
  else if (strength > maxVal) {mappedStrength = 1;}
  else {mappedStrength =((float)(strength - minVal))/((float)(maxVal - minVal));}

  uint8_t r1 = 255, g1 = 0, b1 = 0;
  uint8_t r2 = 0, g2 = 255, b2 = 0;

  uint8_t R =  (r1-r2) * mappedStrength + r2;
  uint8_t G =  (g1-g2) * mappedStrength + g2;
  uint8_t B =  (b1-b2) * mappedStrength + b2;

  return RGB16BIT(R,G,B);
}


void WifiSetup::PrintTitle()
{
  M5.Lcd.clear();
  M5.Lcd.setFreeFont(&font);
  M5.Lcd.setTextColor(WHITE);  
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(55, 20);
  M5.Lcd.println("Wifi Setup ");
}

void WifiSetup::WifiSelectionScreen()
{
  PrintTitle();
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(90, 45);
  M5.Lcd.println("Please wait...");

  int numOfNetworks = WiFi.scanNetworks();

  PrintTitle();

  if (numOfNetworks == 0)
  {
    M5.Lcd.println("No networks found");
  }
  else
  {
    if (numOfNetworks >= 5) {numOfNetworks = 5;}

    initButtons(numOfNetworks);



    M5.Buttons.draw();

    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setFreeFont(&font);
    M5.Lcd.setTextDatum(TC_DATUM);

    // Button B
    //M5.Lcd.drawString("Refresh", 160, 226,2);
    //M5.Buttons.addHandler
    

    

    
  }

}

void WifiSetup::initButtons(int SSIDCount)
{

  M5.Buttons.setFont(&font);
  M5.Buttons.setTextSize(2);

  for (int i = 0; i < SSIDCount; i++)
  {
    uint16_t StrengthColour = WifiStrengthTo16BitColour(WiFi.RSSI(i));
    ButtonColors on_clrs  = {BLACK, WHITE, BLACK};
    ButtonColors off_clrs = {BLACK, StrengthColour, BLACK}; 

    String SSID =  WiFi.SSID(i);

    buttonList[i] = new Button(0, (31+36*(uint16_t)i), 320, 35, false , SSID.c_str(), off_clrs, on_clrs, CC_DATUM);
  }

  M5.Buttons.addHandler(buttonEvent, E_TAP);

}

void WifiSetup::deinitButtons()
{
  M5.Buttons.delHandlers(buttonEvent, nullptr, nullptr);

  for(int i = 0; i < MAXSSID-1; i++)
  {
    delete(buttonList[i]);
    buttonList[i] = NULL;
  }
}

void buttonEvent(Event& e)
{

  Serial.println("\n\n\n\n--------------------------Touched!");

}


WifiSetup WifiSetupScreen;


    // Button** SSIDList = new Button*[numOfNetworks];
    // for (int i = 0; i < numOfNetworks; ++i)
    // {
    //   uint16_t StrengthColour = WifiStrengthTo16BitColour(WiFi.RSSI(i));
    //   on_clrs  = {BLACK, WHITE, BLACK};
    //   off_clrs = {BLACK, StrengthColour, BLACK}; 

    //   String SSID =  WiFi.SSID(i).substring(0,12);

    //   //SSIDList[i] = new Button(0, (30+36*i), 320, 35, false , "test", off_clrs, on_clrs, CC_DATUM);
    //   SSIDList[i] = new Button(0, (31+36*(uint16_t)i), 320, 35, false , SSID.c_str(), off_clrs, on_clrs, CC_DATUM);
    // }