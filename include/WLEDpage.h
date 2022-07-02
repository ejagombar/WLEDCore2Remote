#ifndef WLEDSETUP_H
#define WLEDSETUP_H

#define maxNumofWLED 3

#include <M5Core2.h>
#include <Free_Fonts.h>
#include <Preferences.h>

class WLEDpage;
class WLED;


class WLED
{
    public:

        WLED();
        ~WLED();

        void loadData(uint16_t num, String IP, String name );
        String getIP();
        String getName();
        bool getHasData();

    private:

       
        String IP = "";
        String name = "";
        bool hasData = false;
        uint16_t num;


};


class WLEDpage
{
    public:

        WLEDpage();
        ~WLEDpage();

        void run();
        void importWLEDData(WLED WLEDLights[]);


    private:

        String getIp();
        String getName();
        void drawPlusButton(uint16_t x, uint16_t y, uint16_t size, uint16_t circleColour, uint16_t lineColour);
        void drawRoundBox(uint16_t x, uint16_t y,uint16_t xsize, uint16_t ysize, uint16_t colour);
        void drawEmptyCell(uint16_t position, uint16_t colour1, uint16_t colour2);
        void drawScreen();
        void drawFullCell(uint16_t position, uint16_t colour1, uint16_t colour2);
        void drawOnOffButton(uint16_t position, uint16_t colour1, uint16_t colour2,bool isOn);

        bool gotIP = false;
        String WLEDIP;
        String WLEDname;
        const GFXfont font = FreeMonoBold9pt7b;
        WLED WLEDLights[3];
};

extern WLEDpage WLEDtabPage;
extern WLED WLEDLight;

#endif //WLEDSETUP_H