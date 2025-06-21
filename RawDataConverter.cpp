#include "RawDataConverter.h"
#include <Arduino.h>

char divider1 = ':';
char divider2 = ';';

char numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};




namespace Converter {
    //finaldata enddata;
    
    int endDataSize = 1;
    int endDatafSize = 1;
    dict* endData = new dict[endDataSize];
    dictf* endDataf = new dictf[endDatafSize];
    
    void _assignToVal(const String& wrd, int val) {
       // for (unsigned int i=0;i<sizeof(endData) / sizeof(endData[0]);i++) {
       for (int i=0;i<endDataSize;i++) {
            dict& pair = endData[i];
            if (pair.key == wrd) {
                pair.value = val;
            }
        }
    }

    void _assignToValf(const String& wrd, float val) {
        for (int i=0;i<endDataSize;i++) {
            dictf& pair = endDataf[i];
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
        int8_t valueMultiplier = 1;
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
                valueMultiplier = 1;
                passedWord = 0;
                continue;
            }
            if (!passedWord) {
                //assign the char to currentWord
                currentWord.concat(rawdata[i]);
            } else {
                //assign to value
                if (rawdata[i]=='-') {
                    valueMultiplier=-1;
                } else {
                    currentValue.concat(rawdata[i]);
                }
                
            }
        }
        if (currentWord != ""&&currentValue != "") {
            _assignToVal(currentWord,currentValue.toInt()); 
                 
        }
        return endData;
    }

    const dictf* convertf(const char* rawdata) {
        //main function for conversion
        if (endDataf == nullptr) return nullptr;
        String currentWord;
        String currentValue;
        byte passedWord = 0;
        int8_t valueMultiplier = 1;
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
                    _assignToValf(currentWord,currentValue.toFloat()*valueMultiplier);
                }
                currentWord = "";
                currentValue = "";
                valueMultiplier = 1;
                passedWord = 0;
                continue;
            }
            if (!passedWord) {
                //assign the char to currentWord
                currentWord.concat(rawdata[i]);
            } else {
                //assign to value
                if (rawdata[i]=='-') {
                    valueMultiplier=-1;
                } else {
                    currentValue.concat(rawdata[i]);
                }
                
            }
        }
        if (currentWord != ""&&currentValue != "") {
            _assignToValf(currentWord,currentValue.toFloat()*valueMultiplier); 
                 
        }
        return endDataf;
    }

    int getPacketSize() {
        //returns the packet size for indexing, though not necessary
        return endDataSize;
    }

    int getPacketSizef() {
        //same as getPacketSize, but for float
        return endDatafSize;
    }

    void setDataTemplate(dict* newData, int size) {
        //sets the array template wiht size and variable names
        if (endData != nullptr) {
            delete[] endData;
        }
        
        endData = new dict[size];
        endDataSize = size;
        for (int i=0;i<size;i++) {
            endData[i] = newData[i];
        }
    }

    void setDataTemplatef(dictf* newDataf, int size) {
        //same as setDataTemplate, but for float
        if (endDataf != nullptr) {
            delete[] endDataf;
        }
        
        endDataf = new dictf[size];
        endDatafSize = size;
        for (int i=0;i<size;i++) {
            endDataf[i] = newDataf[i];
        }
    }


    /*int getValue(const dict* Data, int size, String Key) {
        for (int i=0;i<size;i++) {
            dict pair = Data[i];
            if (pair.key==Key) {return pair.value;}
        };
        return 0;
    }

    int getValue(dict* Data, int size, String Key) {
        for (int i=0;i<size;i++) {
            dict pair = Data[i];
            if (pair.key==Key) {return pair.value;}
        };
        return 0;
    }*/

    int getValue(String Key) {
        //parses through endData and returns the value corresponding to String Key
        if (endData==nullptr) return 0;
        for (int i=0;i<endDataSize;i++) {
            dict pair = endData[i];
            if (pair.key == Key) return pair.value;
        }
        return 0;
    }
    
    float getValuef(String Key) {
        //same as getValue, but for float
        if (endDataf==nullptr) return 0.0f;
        for (int i=0;i<endDatafSize;i++) {
            dictf pair = endDataf[i];
            if (pair.key == Key) return pair.value;
        }
        return 0.0f;
    }

}
