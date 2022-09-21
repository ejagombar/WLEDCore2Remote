#include "colourPicker.h"

struct RGB8BitColours
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};


colourPickerPage::colourPickerPage(){}


colourPickerPage::~colourPickerPage(){}


void colourPickerPage::openScreen(){

}

void colourPickerPage::closeScreen(){

}

void colourPickerPage::initButtons()
{
   // M5.Touch.addHandler(colourPickerButtonEvent, E_TOUCH + E_RELEASE);
    M5.Buttons.addHandler(colourPickerButtonEvent, E_TOUCH + E_MOVE);
    M5.Touch.begin();
    
}

void colourPickerPage::deinitButtons()
{

}

void colourPickerPage::generateColourPicker(){

    float invHeight = 1/static_cast<float>(colourHeight+1);
    float hueStep = 360.0/static_cast<float>(colourWidth);
    for (int i = 0; i < colourHeight; i++) {
        float value = invHeight*(i+1);
        for (int j = 0; j < colourWidth; j++) {
            float h = (180 + (int)(static_cast<float>(j) * hueStep)) % 360;
            float s = 0.5 + static_cast<float>((i)/(0.5*static_cast<float>(colourHeight)));
            RGB8BitColours pixelColour = HSVtoRGB(h,sqrt(value),1.0-(value*value));
            uint16_t convertedColour = M5.Lcd.color565(pixelColour.r,pixelColour.g,pixelColour.b);
            colourPoints[j][i] = convertedColour;
        }
    }

}


void colourPickerPage::drawColourPicker(){
    for (int i = 0; i < colourHeight; i++) {
        for (int j = 0; j < colourWidth; j++) {
            M5.Lcd.fillRect(20*j,20*i,20,20,colourPoints[j][i]);
        }
    }
    drawSelectedColour();
}

void colourPickerPage::drawSelectedColour(){
    M5.Lcd.fillRect(0,height-20,width,20,M5.Lcd.color565(255,255,255));
    M5.Lcd.fillRect(1,height-19,width-2,18,M5.Lcd.color565(0,0,0));
    M5.Lcd.fillRect(1,height-19,width-2,18,selectedColour_);
}

void colourPickerPage::selectColour(int16_t x, int16_t y){
    if ( (x <= width) && (y <= height-gridSize) ){
        selectedColour_ = colourPoints[x/gridSize][y/gridSize];
    }
}

void colourPickerButtonEvent(Event& e){
    TouchPoint_t coordinate;
    coordinate = M5.Touch.getPressPoint();
    Serial.printf("x:%d, y:%d \r\n", coordinate.x, coordinate.y);
}



colourPickerPage cpPage;