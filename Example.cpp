#include <Arduino.h>
#include <RawDataConverter.h>

Converter::dict DataTemplate[] = {
  {"Angle1",45},     //{String name, int value}
  {"Angle2",135},
  {"Button1",1}
};
int DataTemplateSize = sizeof(DataTemplate)/sizeof(DataTemplate[0]);
const char* example_rawstring = "Angle1:45;Angle2:135;Button1:1";


void setup() {
  Serial.begin(9600);
  Converter::setDataTemplate(DataTemplate,DataTemplateSize);
  const Converter::dict *endData = Converter::convert(example_rawstring);
  int packetSize = Converter::getPacketSize();
  

  //print each one of the elements:
  for (int i=0;i<packetSize;i++) {
        Converter::dict pair = endData[i];
        Serial.print("Key: ");
        Serial.print(pair.key);
        Serial.print(", Value: ");
        Serial.println(pair.value);
    }

  //or address each element as needed
  
  Serial.println("Printing Angle1 manualy:");
  int angle1 = Converter::getValue("Angle1");
  Serial.print("Angle1=");
  Serial.println(angle1);
}

void loop() {}
