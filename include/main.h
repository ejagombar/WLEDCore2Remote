#ifndef MAIN_H
#define MAIN_H

#include <M5Core2.h>
#include <GDTouchKeyboard.h>
#include "WIFIsetup.h"
#include "WLEDpage.h"
#include "WLED.h"
#include "utils.h"
#include "colourPicker.h"

#define maxNumofWLED 3

#define wledTab 0
#define colourPickerTab 1
#define settingsTab 3

String SSID = "";
String password = "";
uint16_t colour = 0;
uint8_t screenVal = 1;  //0 = WLED page    1 = colour page      2 = settings
WLED WLEDLights[maxNumofWLED];
int screenState = wledTab;


void checkForWifiData();
void setupProcess();
void checkForSavedWLED();
void screenPressed();

void getTabSelection(Event& e);



#endif //MAIN_H