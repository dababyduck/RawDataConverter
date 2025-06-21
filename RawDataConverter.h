#ifndef RAWDATACONVERTER_H
#define RAWDATACONVERTER_H

#include <Arduino.h>
/*
This library converts raw data formed in one string into an easy-to-use array with
keys and values.
I originally developed it to convert esp-now's data for my projects.

Version 1.1 
Added float variant of the functions

*/

namespace Converter {
    struct dict 
    {
        String key;
        int value;
    };

    struct dictf
    {
      String key;
      float value;
    };
    
    const dict* convert(const char* rawdata);
    const dictf* convertf(const char* rawdata);
    int getPacketSize();
    int getPacketSizef();
    void setDataTemplate(dict* newData,int size);
    void setDataTemplatef(dictf* newData,int size);
    //int getValue(dict* Data,String Key);
    int getValue(String Key);
    float getValuef(String Key);
}


#endif
