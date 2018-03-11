#include <TVout.h>
#include "fontALL.h"

TVout TV;
unsigned char x,y;
bool alarm = 1;

void setup()  {
  x=0;
  y=0;
  TV.begin(_NTSC,128,56);  //for devices with only 1k sram(m168) use TV.begin(_NTSC,128,56)
  TV.select_font(font8x8);
}

void loop() {

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
    TV.clear_screen();
    TV.println("SECURETEK ALARM\n)v2.1.15(\n\nTemp: 25.0C\n\nHumi: N/A%");
    TV.delay(1000);
  }
  
}
