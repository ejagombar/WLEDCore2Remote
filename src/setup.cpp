#include "setup.h"


void buttonEvent(Event& e);


WifiSetup::WifiSetup()
{

}

WifiSetup::~WifiSetup()
{

}

struct RGB16BitColours
{
    uint16_t defaultColour;
    uint16_t lighterColour;
    uint16_t darkerColour;
};

std::tuple<String, uint16_t> WifiSetup::run()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(200);
  WifiSelectionScreen();

  while(gotSSID == false)
  {
    M5.update();
  }
  deinitButtons();
  return {SSID,returnedColour};
}

uint16_t WifiSetup::RGB16BIT(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint16_t)((r>>3)<<11)|((g>>2)<<5)|(b>>3));
}

RGB16BitColours WifiSetup::WifiStrengthTo16BitColour(int strength)
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

  RGB16BitColours colours;

  colours.defaultColour = RGB16BIT(R,G,B);
  colours.lighterColour = RGB16BIT(R+25,G+25,B);
  colours.darkerColour = RGB16BIT(R-20,G-20,B);

  return colours;
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

  numOfNetworks = WiFi.scanNetworks();

  PrintTitle();

  if (numOfNetworks == 0)
  {
    M5.Lcd.println("No networks found");
  }
  else
  {
    if (numOfNetworks >= 5) {numOfNetworks = 5;}

    initButtons();



    M5.Buttons.draw();

    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setFreeFont(&font);
    M5.Lcd.setTextDatum(TC_DATUM);

    // Button A
    M5.Lcd.drawString("Refresh", 55, 226,2);
    // Button C
    M5.Lcd.drawString("Next", 265, 226,2);

    


  }

}

void WifiSetup::initButtons()
{

  M5.Buttons.setFont(&font);
  M5.Buttons.setTextSize(2);

  for (int i = 0; i < numOfNetworks; i++)
  {
    RGB16BitColours StrengthColour = WifiStrengthTo16BitColour(WiFi.RSSI(i));
    ButtonColors on_clrs  = {BLACK, StrengthColour.lighterColour, BLACK};
    ButtonColors off_clrs = {BLACK, StrengthColour.defaultColour, BLACK};
    ButtonColors deselcted_clrs = {BLACK, StrengthColour.darkerColour, BLACK};

    String SSIDLabel =  WiFi.SSID(i);

    buttonList[i] = new SSIDButton(0, (31+36*(uint16_t)i), 320, 35, false , (SSIDLabel.substring(0,12)).c_str(), off_clrs, on_clrs, CC_DATUM);

    buttonList[i]->SSIDString = SSIDLabel;
    buttonList[i]->SavedColours = deselcted_clrs;

  }

  M5.Buttons.addHandler(buttonEvent, E_TOUCH);

}

void WifiSetup::deinitButtons()
{
  M5.Buttons.delHandlers(buttonEvent, nullptr, nullptr);

  for(int i = 0; i < MAXSSID; i++)
  {
    delete(buttonList[i]);
    buttonList[i] = NULL;
  }
}

void buttonEvent(Event& e)
{
  if(e.button == &M5.BtnA)  //Refresh
  {
    WifiSetupScreen.deinitButtons();
    WifiSetupScreen.run();
    return;
  }

  else if(e.button == &M5.BtnC)  // Next
  {
    if (WifiSetupScreen.SSID != "")
    {
      
      WifiSetupScreen.gotSSID = true;
    }
    return;
  }
  else
  {
    
    for (int i = 0; i < WifiSetupScreen.numOfNetworks; i++)
    {
      if (WifiSetupScreen.buttonList[i]->isPressed() == true)
      {
        WifiSetupScreen.buttonList[i]->off = WifiSetupScreen.buttonList[i]->on;
        WifiSetupScreen.SSID = WifiSetupScreen.buttonList[i]->SSIDString;
        WifiSetupScreen.returnedColour = WifiSetupScreen.buttonList[i]->SavedColours.text;
      }
      else
      {
        WifiSetupScreen.buttonList[i]->off = WifiSetupScreen.buttonList[i]->SavedColours;
      }
    }
    M5.Buttons.draw();
  }
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