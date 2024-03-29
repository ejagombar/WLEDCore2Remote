#ifndef WLEDSETUP_H
#define WLEDSETUP_H

#define maxNumofWLED 3

#include <M5Core2.h>
#include <Free_Fonts.h>
#include <Preferences.h>
#include "WIFIsetup.h"
#include "WLED.h"

void WLEDPageButtonEvent(Event& e);


class WLEDpage;


class WLEDpage
{
    public:

        WLEDpage();
        ~WLEDpage();

        void openScreen();
        void closeScreen();
        void importWLEDData(WLED WLEDLights[]);
        
        friend void WLEDPageButtonEvent(Event& e);

    private:

        String getIp();
        String getName();
        void drawPlusButton(uint16_t x, uint16_t y, uint16_t size, uint16_t circleColour, uint16_t lineColour);
        void drawRoundBox(uint16_t x, uint16_t y,uint16_t xsize, uint16_t ysize, uint16_t colour);
        void drawEmptyCell(uint16_t position, uint16_t colour1, uint16_t colour2);
        void drawScreen();
        void drawFullCell(uint16_t position, uint16_t colour1, uint16_t colour2);
        void initButtons();
        void deinitButtons();
        void drawButtons(int i, WLED &b);

        bool gotIP = false;
        String WLEDIP;
        String WLEDname;
        const GFXfont font = FreeMonoBold9pt7b;
        WLED WLEDLights[maxNumofWLED];
        Button *buttonList[maxNumofWLED];
};

extern WLEDpage WLEDtabPage;
extern WLED WLEDLight;

#endif //WLEDSETUP_H