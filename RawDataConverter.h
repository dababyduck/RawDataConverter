#ifndef RAWDATACONVERTER_H
#define RAWDATACONVERTER_H

#include <Arduino.h>
/*
This library converts raw data formed in one string into an easy-to-use array with
keys and values.
I originally developed it to convert esp-now's data for my projects
To change the final array's 

Version 1.0
*/

namespace Converter {
    struct dict 
    {
        String key;
        int value;
    };
    
    const dict* convert(const char* rawdata);
    int getPacketSize();
    void setDataTemplate(dict* newData,int size);
    //int getValue(dict* Data,String Key);
    int getValue(String Key);
}


#endif
