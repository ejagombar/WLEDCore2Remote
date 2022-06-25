#ifndef SETUP_H
#define SETUP_H

#include <M5Core2.h>
#include "WiFi.h"
#include <Free_Fonts.h>
#include <tuple>


struct RGB16BitColours;


void buttonEvent(Event& e);

class WifiSetup;

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

        friend void buttonEvent(Event& e);

    private:

        #define MAXSSID (5)

        RGB16BitColours WifiStrengthTo16BitColour(int strength);
        uint16_t RGB16BIT(uint8_t r, uint8_t g, uint8_t b);
        void WifiSelectionScreen();
        void PrintTitle();
        void initButtons();
        void deinitButtons();

        const GFXfont font = FreeMonoBold9pt7b;
        bool gotSSID = false;
        String SSID = "";
        int numOfNetworks = 0;
        uint16_t returnedColour = 0;
        ButtonColors defaultColours = {BLACK, DARKGREY, BLACK};
        SSIDButton *buttonList[MAXSSID];
};


extern WifiSetup WifiSetupScreen;

#endif //SETUPWIFI_H

