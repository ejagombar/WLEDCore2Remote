#ifndef UTILS_H
#define UTILS_H

#include <M5Core2.h>

struct RGB8BitColours;

RGB8BitColours HSVtoRGB(float h, float s,float v);
uint16_t RGB16BIT(uint8_t r, uint8_t g, uint8_t b);

#endif //UTILS_H