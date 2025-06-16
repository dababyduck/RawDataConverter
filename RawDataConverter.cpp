#include "RawDataConverter.h"
#include <Arduino.h>

char divider1 = ':';
char divider2 = ';';


namespace Converter {
    //finaldata enddata;
    int endDataSize = 1;
    dict* endData = new dict[1];
    
    void _assignToVal(const String& wrd, int val) {
       for (int i=0;i<endDataSize;i++) {
            dict& pair = endData[i];
            if (pair.key == wrd) {
                pair.value = val;
            }
        }
    }


    const dict* convert(const char* rawdata) {
        //main function for conversion
        if (endData == nullptr) return nullptr;
        String currentWord;
        String currentValue;
        byte passedWord = 0;
        for (unsigned int i=0;i<strlen(rawdata);i++) {
            //parsing through each char of raw data
            if (rawdata[i]==divider1) {
                //passed word name, going to the value
                passedWord = 1;
                continue;
            }
            if (rawdata[i]==divider2) {
                //assign the word
                if (currentWord != ""&&currentValue != "") {
                    _assignToVal(currentWord,currentValue.toInt());
                }
                currentWord = "";
                currentValue = "";
                passedWord = 0;
                continue;
            }
            if (!passedWord) {
                //assign the char to currentWord
                currentWord.concat(rawdata[i]);
            } else {
                //assign to value
                currentValue.concat(rawdata[i]);
            }
        }
        if (currentWord != ""&&currentValue != "") {
            _assignToVal(currentWord,currentValue.toInt());      
        }
        return endData;
    }
    int getPacketSize() {
        //returns the packet size for indexing, though not necessary
        return endDataSize;
    }
    void setDataTemplate(dict* newData, int size) {
        if (endData != nullptr) {
            delete[] endData;
        }
        
        endData = new dict[size];
        endDataSize = size;
        for (int i=0;i<size;i++) {
            endData[i] = newData[i];
        }
    }

    int getValue(String Key) {
        if (endData==nullptr) return 0;
        for (int i=0;i<endDataSize;i++) {
            dict pair = endData[i];
            if (pair.key == Key) return pair.value;
        }
        return 0;
    }

}
