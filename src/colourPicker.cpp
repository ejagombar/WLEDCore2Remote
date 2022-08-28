#include "colourPicker.h"

struct RGB8BitColours
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};


colourPickerPage::colourPickerPage(){

}


colourPickerPage::~colourPickerPage(){

}



void colourPickerPage::openScreen(){


}

void colourPickerPage::closeScreen(){

}

void colourPickerPage::generateColourPicker(){

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float h = static_cast<float>(j) * 1.125;
            float s = 0.5 + static_cast<float>((i)/(0.5*static_cast<float>(height)));
            RGB8BitColours pixelColour = HSVtoRGB(h,1,0.5);
            M5.Lcd.drawPixel(j,i,M5.Lcd.color565(pixelColour.r,pixelColour.g,pixelColour.b));
        }
    }

}





colourPickerPage cpPage;