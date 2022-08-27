#include "WLEDpage.h"
#include "WIFIsetup.h"


WLED::WLED()
{

}

WLED::~WLED()
{

}

void WLED::loadData(uint16_t getNum, String getIP, String getName, uint16_t getColour)
{
    name = getName;
    IP = getIP;
    hasData = true;
    num = getNum;
    colour = getColour;
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

uint16_t WLED::getColour()
{
    return colour;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


WLEDpage::WLEDpage()
{
    gotIP = false;
    WLEDIP = "";
    WLEDname = "";
    //openScreen();
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


void WLEDpage::openScreen()
{
    
    initButtons();
    drawScreen();
}

void WLEDpage::closeScreen()
{
    deinitButtons();
}

void WLEDpage::initButtons()
{
    ButtonColors off_clrs = {BLACK, BLACK, BLACK};
    for (int i = 0; i < maxNumofWLED; i++)
    {
        String buttonName = String(i);
        buttonList[i] = new Button(0, 69*(i+1)-4-65/2, 320, 65, false , buttonName.c_str(), off_clrs, off_clrs, CC_DATUM);
    }

    M5.Buttons.addHandler(WLEDPageButtonEvent, E_TOUCH);
}

void WLEDpage::deinitButtons()
{
    M5.Buttons.delHandlers(WLEDPageButtonEvent, nullptr, nullptr);

    for(int i = 0; i < maxNumofWLED; i++)
    {
        delete(buttonList[i]);
        buttonList[i] = NULL;
    }
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
            drawFullCell(i, deepGray, deepGray2);
        }
        else
        {
            drawEmptyCell(i, deepGray, deepGray2);
            //drawFullCell(i, deepGray, deepGray2);
        }
    }
}


void WLEDpage::drawFullCell(uint16_t position, uint16_t colour1, uint16_t colour2)
{
    drawRoundBox(M5.Lcd.width()/2,69*(position+1)-4,M5.Lcd.width()-6, 65, colour1);
    M5.Lcd.setTextSize(1);
    M5.Lcd.drawString(WLEDLights[position].getIP(),16,69*(position+1)+5,1);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString(WLEDLights[position].getName(),13,69*(position+1)-32,1);

    M5.Lcd.fillCircle(M5.Lcd.width() - 35 , 69*(position+1)-4, 24, BLACK);
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



void WLEDPageButtonEvent(Event& e)
{
    Button& b = *e.button;
    int i = 1;
    Serial.println(b.label());
    uint16_t deepGray = RGB16BIT(140,140,140);
    uint16_t deepGray2 = RGB16BIT(168,168,168);

    if (WLEDtabPage.WLEDLights[i].getHasData() == true)
    {
        WLEDtabPage.drawFullCell(i, deepGray, deepGray2);
    }
    else
    {
        WLEDtabPage.drawEmptyCell(i, deepGray, deepGray2);
        //drawFullCell(i, deepGray, deepGray2);
    }
}



WLEDpage WLEDtabPage;
