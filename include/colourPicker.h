#ifndef COLOURPICKER_H
#define COLOURPICKER_H

#include <M5Core2.h>
#include "utils.h"
#include <math.h>


void colourPickerButtonEvent(Event& e);


class colourPickerPage;


class colourPickerPage
{
    public:

        colourPickerPage();
        ~colourPickerPage();

        void openScreen();
        void closeScreen();
        void generateColourPicker();
        void drawColourPicker();
        void selectColour(int16_t x, int16_t y);
        void drawSelectedColour();


        uint16_t       &selectedColour()         { return selectedColour_; }
        const uint16_t &selectedColour()  const  { return selectedColour_; }
        
        friend void colourPickerButtonEvent(Event& e);

    private:

        void initButtons();
        void deinitButtons();
        

        const static int width = 320;
        const static int height = 240;

        const static int colourWidth = 16;
        const static int colourHeight = 11;

        const static int gridSize = 20;
        
        uint16_t colourPoints[colourWidth][colourHeight];
        uint16_t selectedColour_;

    




};

extern colourPickerPage cpPage;

#endif //COLOURPICKER_H