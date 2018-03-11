#include <stdio.h>
#include <TVout.h>
#include "fontALL.h"

TVout TV;
unsigned char x,y;
bool alarm = 0;
float temp = 0.0;

void setup()  {
  Serial.begin(9600); // open the serial port at 9600 bps
  x=0;
  y=0;
  TV.begin(_NTSC,128,56);  //for devices with only 1k sram(m168) use TV.begin(_NTSC,128,56)
  TV.select_font(font8x8);
}

void loop() {

  temp = analogRead(A6);
  if (temp > 550) {
    alarm = 1;
  }
  else {
    alarm = 0;
  }
  
  if (alarm) {    
    TV.delay(1000);
    TV.clear_screen();
    TV.println("SECURETEK ALARM\n)v2.1.15(\n\nINTRUDER ALERT!\n\nINTRUDER ALERT!");
    TV.delay(1000);
    for(x=0;x<TV.hres();x++){
      for(y=0;y<TV.vres();y++){
        TV.set_pixel(x,y,1);
      }
    }
  }
  else {
    temp = analogRead(A6);
    Serial.print(temp);
    Serial.print("\n\r");
    
    TV.clear_screen();
    TV.println("SECURETEK ALARM\n)v2.1.15(\n\nTemp:     C\n\nHumi: N/A%");
    TV.set_cursor(42, 24);
    TV.print(temp/36+11,1);
    TV.delay(1000);
  }
  
}
