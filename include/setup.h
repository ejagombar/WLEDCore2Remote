#ifndef SETUP_H
#define SETUP_H

#include <M5Core2.h>
#include "WiFi.h"
#include <Free_Fonts.h>
#include <tuple>
#include <ESP32Ping.h>
#include <Preferences.h>

struct RGB16BitColours;

void WifiSetupButtonEvent(Event& e);
void WifiConnectButtonEvent(Event& e);
uint16_t RGB16BIT(uint8_t r, uint8_t g, uint8_t b);

class WifiSetup;
class WifiConnect;

class SSIDButton: public Button
{
    using Button::Button;

    public:
        String SSIDString;
        ButtonColors SavedColours;
};
 
class WifiSetup
{
    public:

        WifiSetup();
        ~WifiSetup();

        std::tuple<String, uint16_t> run();

        friend void WifiSetupButtonEvent(Event& e);

    private:

        #define MAXSSID (5)

        RGB16BitColours WifiStrengthTo16BitColour(int strength);

        void WifiSelectionScreen();
        void PrintTitle();
        void initButtons();
        void deinitButtons();

        const GFXfont font = FreeMonoBold9pt7b;
        bool gotSSID = false;
        String WifiSSID = "";
        String testVar = "";
        int numOfNetworks = 0;
        uint16_t returnedColour = 0;
        ButtonColors defaultColours = {BLACK, DARKGREY, BLACK};
        SSIDButton *buttonList[MAXSSID];
};


class WifiConnect
{
    public:
        WifiConnect();
        ~WifiConnect();

        bool run(String getSSID, String getPassword);

        friend void WifiConnectButtonEvent(Event& e);

    private:

        bool checkConnection();
        void waitForTap();
        void storeWifiData();
        String SSID;
        String password;
        bool isPressed = false;
        const GFXfont font = FreeMonoBold9pt7b;
};



extern WifiSetup WifiSetupScreen;
extern WifiConnect WifiConnectScreen;
extern Preferences preferences;

#endif //SETUPWIFI_H

