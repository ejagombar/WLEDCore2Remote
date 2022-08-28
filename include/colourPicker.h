#ifndef COLOURPICKER_H
#define COLOURPICKER_H

#include <M5Core2.h>
#include "utils.h"


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
        
        friend void colourPickerButtonEvent(Event& e);

    private:

        const int width = 320;
        const int height = 240;
    

};

extern colourPickerPage cpPage;

#endif //COLOURPICKER_H