#include "WLEDpage.h"
#include "WIFIsetup.h"




WLEDpage::WLEDpage()
{
    gotIP = false;
    WLEDIP = "";
    WLEDname = "";
    //run();
}

WLEDpage::~WLEDpage()
{

}

void WLEDpage::importWLEDData(WLED getWLEDLights[])
{
    for (int i = 0; i < maxNumofWLED; i++)
    {
        WLEDLights[i] = getWLEDLights[i];
    }
}


void WLEDpage::run()
{


    drawScreen();
}

void WLEDpage::drawScreen()
{
    M5.Lcd.clear();
    M5.Lcd.setFreeFont(&font);
    M5.Lcd.setTextColor(WHITE);  
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(55, 20);
    M5.Lcd.println("WLED Setup");

    uint16_t deepGray = RGB16BIT(40,40,40);
    uint16_t deepGray2 = RGB16BIT(68,68,68);

    for (int i = 0; i < maxNumofWLED; i++)
    {
        if (WLEDLights[i].getHasData() == true)
        {
            drawRoundBox(i*100, 100, 100, 100, deepGray);
            M5.Lcd.setTextColor(WHITE);  
            M5.Lcd.setTextSize(1);
            M5.Lcd.setCursor(i*100+10, 110);
            M5.Lcd.println(WLEDLights[i].getName());
            M5.Lcd.setCursor(i*100+10, 130);
            M5.Lcd.println(WLEDLights[i].getIP());
        }
        else
        {
            //drawEmptyCell(i, deepGray, deepGray2);
            drawFullCell(i, deepGray, deepGray2);
        }
    }
}


void WLEDpage::drawFullCell(uint16_t position, uint16_t colour1, uint16_t colour2)
{
    drawRoundBox(M5.Lcd.width()/2,69*(position+1)-4,M5.Lcd.width()-6, 65, colour1);
    M5.Lcd.setTextSize(1);
    M5.Lcd.drawString("192.168.1.174",16,69*(position+1)+5,1);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("Bed Lights",13,69*(position+1)-32,1);

    M5.Lcd.fillCircle(M5.Lcd.width() - 35 , 69*(position+1)-4, 24, BLACK);
}

void WLEDpage::drawOnOffButton(uint16_t position, uint16_t colour1, uint16_t colour2,bool isOn)
{
    
}

void WLEDpage::drawEmptyCell(uint16_t position, uint16_t colour1, uint16_t colour2)
 {
    drawRoundBox(M5.Lcd.width()/2,69*(position+1)-4,M5.Lcd.width()-6, 65, colour1);
    drawPlusButton(M5.Lcd.width()/2, 69*(position+1)-4, 25, colour2, colour1);
 }

void WLEDpage::drawRoundBox(uint16_t x, uint16_t y,uint16_t xsize, uint16_t ysize, uint16_t colour)
{
    M5.Lcd.fillRoundRect(x-xsize/2, y-ysize/2, xsize, ysize, ysize/3, colour);
}

void WLEDpage::drawPlusButton(uint16_t x, uint16_t y,uint16_t size, uint16_t circleColour, uint16_t lineColour)
{
    uint16_t gap = size/4; 
    M5.Lcd.drawPixel(x,y,RED);
    M5.Lcd.fillCircle(x, y, size, circleColour);   //Draw a red circle with a radius of 50 at (x,y)

    M5.Lcd.drawFastHLine(x-(size/2)-gap, y+2, size+gap*2, lineColour);
    M5.Lcd.drawFastHLine(x-1-(size/2)-gap, y+1, 2+size+gap*2, lineColour);
    M5.Lcd.drawFastHLine(x-1-(size/2)-gap, y, 2+size+gap*2, lineColour);
    M5.Lcd.drawFastHLine(x-1-(size/2)-gap, y-1, 2+size+gap*2, lineColour);
    M5.Lcd.drawFastHLine(x-(size/2)-gap, y-2, size+gap*2, lineColour);

    M5.Lcd.drawFastVLine(x+2, y-(size/2)-gap, size+gap*2, lineColour);
    M5.Lcd.drawFastVLine(x+1, y-1-(size/2)-gap, 2+size+gap*2, lineColour);
    M5.Lcd.drawFastVLine(x, y-1-(size/2)-gap, 2+size+gap*2, lineColour);
    M5.Lcd.drawFastVLine(x-1, y-1-(size/2)-gap, 2+size+gap*2, lineColour);
    M5.Lcd.drawFastVLine(x-2, y-(size/2)-gap, size+gap*2, lineColour);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WLED::WLED()
{

}

WLED::~WLED()
{

}

void WLED::loadData(uint16_t getNum, String getIP, String getName)
{
    name = getName;
    IP = getIP;
    hasData = true;
    num = getNum;
}


String WLED::getIP()
{
    return IP;
}

String WLED::getName()
{
    return name;
}

bool WLED::getHasData()
{
    return hasData;
}





WLEDpage WLEDtabPage;
