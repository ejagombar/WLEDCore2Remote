#ifndef SETUP_H
#define SETUP_H

#include <M5Core2.h>
#include "WiFi.h"
#include <Free_Fonts.h>


void buttonEvent(Event& e);

class WifiSetup;

class WifiSetup
{
    public:
        WifiSetup();
        ~WifiSetup();

        String run();

        friend void _buttonEvent(Event& e);

    private:

        #define MAXSSID (5)

        

        uint16_t WifiStrengthTo16BitColour(int strength);
        uint16_t RGB16BIT(uint8_t r, uint8_t g, uint8_t b);
        void WifiSelectionScreen();
        void PrintTitle();

        
        void initButtons(int SSIDCount);
        void deinitButtons();

        const GFXfont font = FreeMonoBold9pt7b;
        bool gotSSID = false;
        String SSID = "";
        
        ButtonColors defaultColours = {BLACK, WHITE, WHITE};


        Button *buttonList[MAXSSID];
};


extern WifiSetup WifiSetupScreen;

#endif //SETUPWIFI_H

