#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include "RTClib.h"
#include <Wire.h>

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};

int pinCS = 05; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 8;
int numberOfVerticalDisplays = 2;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String hora = "";
String minuto = "";
String ponto = ":";
String segundo = "";
String semana = "";
int wait = 100; // In milliseconds
//int wait = 20; // In milliseconds

int spacer = 1;
int width = 5 + spacer; // The font width is 5 pixels

void setup() {
if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
   rtc.adjust(DateTime(2024, 4, 18, 16, 35, 30));
  }
  matrix.setIntensity(7); // Use a value between 0 and 15 for brightness

// Adjust to your own needs
//  matrix.setPosition(0, 0, 0); // The first display is at <0, 0>
//  matrix.setPosition(1, 1, 0); // The second display is at <1, 0>
//  matrix.setPosition(2, 2, 0); // The third display is at <2, 0>
//  matrix.setPosition(3, 3, 0); // And the last display is at <3, 0>
//  ...
 matrix.setRotation(0, 1); 
 matrix.setRotation(1, 1); 
 matrix.setRotation(2, 1); 
 matrix.setRotation(3, 1); 
 matrix.setRotation(4, 1);  
  matrix.setRotation(5, 1); 
 matrix.setRotation(6, 1); 
 matrix.setRotation(7, 1); 
 matrix.setRotation(8, 1); 
 matrix.setRotation(9, 1); 
 matrix.setRotation(10, 1); 
 matrix.setRotation(11, 1); 
 matrix.setRotation(12, 1);  
  matrix.setRotation(13, 1); 
 matrix.setRotation(14, 1); 
 matrix.setRotation(15, 1);
 
//  matrix.setRotation(8, 1); 
//  matrix.setRotation(4, 1);  
 //matrix.setRotation(3, 2);    // The same hold for the last display
}

void loop() {
   DateTime now = rtc.now();
   hora = now.hour(); 
  minuto = now.minute(); 
  segundo = now.second(); 
   semana = daysOfTheWeek[now.dayOfTheWeek()]; 

float rolagem = rtc.getTemperature();
String newstring ;
newstring.concat(rolagem);
String newstring2 = " GRAUS C";
newstring.concat(newstring2);
String tape = newstring;
//tape = newstring.concat(newstring2);
 if ( minuto.toInt() % 3 == 0) 
 { for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {

    //matrix.doubleBuffering(true); // Prevent screen flicker

    matrix.fillScreen(LOW);

  int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically
    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < tape.length() ) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }
      letter--;
      x -= width;
    }

    //matrix.doubleBuffering(false); // Send drawing to display
    matrix.write(); // Send bitmap to display

    delay(wait);
  }
  
 clearmatrix();
  }
  if (minuto.toInt()%3!= 0)
 { matrix.drawChar(15,0,hora[0],1,0,1);
      matrix.drawChar(20,0,hora[1],1,0,1);
      matrix.drawChar(25,0,ponto[0],1,0,1);
        matrix.drawChar(29,0,minuto[0],1,0,1);
          matrix.drawChar(35,0,minuto[1],1,0,1);
             matrix.drawChar(40,0,ponto[0],1,0,1);
               matrix.drawChar(45,0,segundo[0],1,0,1);
                 matrix.drawChar(51,0,segundo[1],1,0,1);
                    matrix.drawChar(15,8,semana[0],1,0,1);
                        matrix.drawChar(22,8,semana[1],1,0,1);
                        matrix.drawChar(28,8,semana[2],1,0,1);
                          matrix.drawChar(35,8,semana[3],1,0,1);
                            matrix.drawChar(42,8,semana[4],1,0,1);
                              matrix.drawChar(49,8,semana[5],1,0,1);
                                matrix.drawChar(56,8,semana[6],1,0,1);
     matrix.write();
     clearmatrix();
                                     }
}
void clearmatrix()
{
  for(int y=0;y<8;y++)
    for(int x=0;x<8;x++)
      matrix.drawPixel(x, y, LOW);
 
}