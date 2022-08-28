#include "utils.h"

struct RGB8BitColours
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

uint16_t RGB16BIT(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint16_t)((r>>3)<<11)|((g>>2)<<5)|(b>>3));
}

RGB8BitColours HSVtoRGB(float h, float s,float v){
    if(h>360 || h<0 || s>1.0 || s<0.0 || v>1.0 || v<0.0){
        Serial.println("Error: vals out of range");
    }

    float C = s*v;
    float X = C*(1-std::abs(std::fmod(h/60.0, 2)-1));
    float m = v-C;
    float r,g,b;

    if(h >= 0 && h < 60){
        r = C,g = X,b = 0;
    }
    else if(h >= 60 && h < 120){
        r = X,g = C,b = 0;
    }
    else if(h >= 120 && h < 180){
        r = 0,g = C,b = X;
    }
    else if(h >= 180 && h < 240){
        r = 0,g = X,b = C;
    }
    else if(h >= 240 && h < 300){
        r = X,g = 0,b = C;
    }
    else{
        r = C,g = 0,b = X;
    }
    uint8_t R = static_cast<uint8_t>((r+m)*255.0);
    uint8_t G = static_cast<uint8_t>((g+m)*255.0);
    uint8_t B = static_cast<uint8_t>((b+m)*255.0);

    return RGB8BitColours{R,G,B};
}