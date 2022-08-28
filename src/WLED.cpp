#include "WLED.h"

WLED::WLED()
{

}

WLED::~WLED()
{

}

void WLED::loadData(uint16_t num, String IP, String name, uint16_t colour)
{
    hasData_ = true;
    name_ = name;
    IP_ = IP;
    num_ = num;
    colour_ = colour;
}
