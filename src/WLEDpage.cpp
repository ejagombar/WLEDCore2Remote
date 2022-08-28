#include "WLEDpage.h"
#include "WIFIsetup.h"


uint16_t deepGray = RGB16BIT(40,40,40);
uint16_t gray = RGB16BIT(68,68,68);


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


void WLEDpage::openScreen()
{
    initButtons();
    drawScreen();
    
}

void WLEDpage::importWLEDData(WLED getWLEDLights[])
{
    for (int i = 0; i < maxNumofWLED; i++)
    {
        WLEDLights[i] = getWLEDLights[i];
    }
}

void WLEDpage::closeScreen()
{
    deinitButtons();
}

void WLEDpage::initButtons()
{
    for (int i = 0; i < maxNumofWLED; i++)
    {
        String buttonName = String(i); 
        buttonList[i] = new Button(0, 69*(i+1)-4-65/2, 320, 65, false,buttonName.c_str());
        buttonList[i]->addHandler(WLEDPageButtonEvent, E_TOUCH);
    }
}

void WLEDpage::deinitButtons()
{
    for (int i = 0; i < maxNumofWLED; i++)
    {
        buttonList[i]->delHandlers(WLEDPageButtonEvent);
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

    for (int i = 0; i < maxNumofWLED; i++)
    {
        if (WLEDLights[i].hasData() == true)
        {
           drawFullCell(i, deepGray, BLACK);
        }
        else
        {
            drawEmptyCell(i, deepGray, gray);
        }
    }
}


void WLEDpage::drawFullCell(uint16_t position, uint16_t bgColour, uint16_t circleColour)
{
    drawRoundBox(M5.Lcd.width()/2,69*(position+1)-4,M5.Lcd.width()-6, 65, bgColour);
    M5.Lcd.setTextSize(1); M5.Lcd.drawString(WLEDLights[position].IP(),16,69*(position+1)+5,1);
    M5.Lcd.setTextSize(2); M5.Lcd.drawString(WLEDLights[position].name(),13,69*(position+1)-32,1);
    M5.Lcd.fillCircle(M5.Lcd.width() - 35 , 69*(position+1)-4, 24, circleColour);
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

    M5.Lcd.drawFastHLine(x-(size/2)-gap, y+2, size+gap*2, lineColour);     M5.Lcd.drawFastHLine(x-1-(size/2)-gap, y+1, 2+size+gap*2, lineColour);
    M5.Lcd.drawFastHLine(x-1-(size/2)-gap, y, 2+size+gap*2, lineColour);   M5.Lcd.drawFastHLine(x-1-(size/2)-gap, y-1, 2+size+gap*2, lineColour);
    M5.Lcd.drawFastHLine(x-(size/2)-gap, y-2, size+gap*2, lineColour);     M5.Lcd.drawFastVLine(x+2, y-(size/2)-gap, size+gap*2, lineColour);
    M5.Lcd.drawFastVLine(x+1, y-1-(size/2)-gap, 2+size+gap*2, lineColour); M5.Lcd.drawFastVLine(x, y-1-(size/2)-gap, 2+size+gap*2, lineColour);
    M5.Lcd.drawFastVLine(x-1, y-1-(size/2)-gap, 2+size+gap*2, lineColour); M5.Lcd.drawFastVLine(x-2, y-(size/2)-gap, size+gap*2, lineColour);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void WLEDPageButtonEvent(Event& e) {
    Button& button = *e.button;
    if ((e.button != &M5.BtnA) && (e.button != &M5.BtnB) && (e.button != &M5.BtnC)) {
        int i = std::stoi(button.label());
        WLED &b = WLEDtabPage.WLEDLights[i];
        if (b.hasData() == true) {
        
            if (b.on() == true) {
                WLEDtabPage.drawFullCell(i, deepGray, BLACK); 
            } else {
                WLEDtabPage.drawFullCell(i, deepGray, b.colour());
            }
            b.on() = !b.on();
        } else {
            WLEDtabPage.drawEmptyCell(i, deepGray, gray);
        }
    }
}



WLEDpage WLEDtabPage;
