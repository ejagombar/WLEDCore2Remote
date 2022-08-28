#ifndef WLED_H
#define WLED_H

#include <M5Core2.h>


class WLED;


class WLED
{

    private:

        bool hasData_ = false;
        String IP_ = "";
        String name_ = "";
        uint16_t num_ = 0;
        uint16_t colour_ = 0;
        bool on_ = false;
        

    public:

        WLED();
        ~WLED();

        
        void loadData(uint16_t num, String IP, String name, uint16_t colour);

        bool       &hasData()        { return hasData_; }
        const bool &hasData() const  { return hasData_; }

        String       &IP()        { return IP_; }
        const String &IP() const  { return IP_; }

        String       &name()        { return name_; }
        const String &name() const  { return name_; }

        uint16_t       &num()        { return num_; }
        const uint16_t &num() const  { return num_; }

        uint16_t       &colour()        { return colour_; }
        const uint16_t &colour() const  { return colour_; }

        bool       &on()        { return on_;  }
        const bool &on() const  { return on_; }

};


#endif //WLED_H