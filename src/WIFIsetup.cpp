#include "WIFIsetup.h"

void WifiSetupButtonEvent(Event& e);

struct RGB16BitColours
{
    uint16_t defaultColour;
    uint16_t lighterColour;
    uint16_t darkerColour;
};


WifiSetup::WifiSetup()
{

}

WifiSetup::~WifiSetup()
{

}

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

  return std::make_tuple(WifiSSID,returnedColour);
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
  M5.Lcd.println("Wifi Setup");
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

  M5.Buttons.addHandler(WifiSetupButtonEvent, E_TOUCH);
}

void WifiSetup::deinitButtons()
{
  M5.Buttons.delHandlers(WifiSetupButtonEvent, nullptr, nullptr);
  Serial.println("Deinit buttons");
  for(int i = 0; i < MAXSSID; i++)
  {
    delete(buttonList[i]);
    buttonList[i] = NULL;
  }
}

void WifiSetupButtonEvent(Event& e)
{
  if(e.button == &M5.BtnA)  //Refresh
  {
    WifiSetupScreen.deinitButtons();
    WifiSetupScreen.gotSSID = false;
    WifiSetupScreen.WifiSSID = "";
    WifiSetupScreen.run();
    return;
  }

  else if(e.button == &M5.BtnC)  // Next
  {
    if (WifiSetupScreen.WifiSSID != "")
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
        WifiSetupScreen.WifiSSID = WifiSetupScreen.buttonList[i]->SSIDString;
        WifiSetupScreen.returnedColour = WifiSetupScreen.buttonList[i]->SavedColours.text;
        Serial.println("Got SSID: "+WifiSetupScreen.WifiSSID);
      }
      else
      {
        WifiSetupScreen.buttonList[i]->off = WifiSetupScreen.buttonList[i]->SavedColours;
      }
    }
    M5.Buttons.draw();
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


WifiConnect::WifiConnect()
{

}

WifiConnect::~WifiConnect()
{

}

bool WifiConnect::run(String getSSID, String getPassword)
{
  SSID = getSSID;
  password = getPassword;
  isPressed = false;

  return checkConnection();
}

void WifiConnect::waitForTap()
{
  M5.Lcd.println("Tap anywhere to continue");

  M5.Buttons.addHandler(WifiConnectButtonEvent, E_TOUCH);
  while (!isPressed)
  {
     M5.update();
  }
  M5.Buttons.delHandlers(WifiConnectButtonEvent, nullptr, nullptr);
}


bool WifiConnect::checkConnection()
{

  M5.Lcd.clear();
  M5.Lcd.setFreeFont(&font);
  M5.Lcd.setTextColor(WHITE);  
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.print("Connecting to " + SSID);

  WiFi.begin(SSID.c_str(), password.c_str());
  int timeOut = 0;
  while ((WiFi.status() != WL_CONNECTED) && (timeOut < 25))
  {
    delay(500);
    M5.Lcd.print(".");
    timeOut++;
    if (timeOut >= 25)
    {
      M5.Lcd.fillScreen(RED);  
      M5.Lcd.setCursor(0, 20);
      M5.Lcd.print("Connecting to " + SSID);
      M5.Lcd.setTextSize(1);
      M5.Lcd.println("\n\nConnection failed");
      waitForTap();
      return false;
    }
  }

  M5.Lcd.fillScreen(RGB16BIT(0, 189, 31));
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.print("Connecting to " + SSID);
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("\n\nConnected!");
  M5.Lcd.println("IP address: " + WiFi.localIP().toString());

  M5.Lcd.println("Pinging google...");
  bool success = Ping.ping("www.google.com");
 
  if(!success){
    M5.Lcd.println("Ping failed");
    return false;
  }
 
  M5.Lcd.println("Ping succesful");

  storeWifiData();

  M5.Lcd.println("Saved Wifi Data to flash");

  delay(200);
  waitForTap();

  return true;

}

void WifiConnectButtonEvent(Event& e)
{
 WifiConnectScreen.isPressed = true;
}

void WifiConnect::storeWifiData()
{
  preferences.begin("wifiData", false);
  preferences.putString("ssid", SSID); 
  preferences.putString("password", password);
  preferences.end();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WifiSetup WifiSetupScreen;
WifiConnect WifiConnectScreen;
Preferences preferences;