#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Wire.h>
#include <WiFi.h>
#include <distance_detect.h>
#include <music.h>

#define I2C_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define BUZZER 32

int LowerBoundSafeDistance = 1;
int UpperBoundSafeDistance = 22;

bool SafeStatus;

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//                                                                                                                                       
TaskHandle_t GraphicsDisplay;
TaskHandle_t MusicHandle;

void printText(int x, int y, String text, int s = 1){
  display.setTextSize(s);
  display.setCursor(x, y);
  display.print(text);
}

void printText(int x, int y, int value, int s =1){
  display.setTextSize(s);
  display.setCursor(x, y);
  display.print(value);
}

void status_display(float distance, int lower_bound, int upper_bound){
  delay(10);
  
  /*
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  
  display.drawFastHLine(1, 12, 128, SH110X_WHITE);
  display.drawFastHLine(1, 52, 128, SH110X_WHITE);

  printText(10, 0, "Distance: ");
  printText(70, 0, static_cast<int>(round(distance)) );

  printText(10, 18, "Status:");
  if (distance < lower_bound){
    printText(10, 30, "TOO CLOSE", 2);
  }
  else if (distance > upper_bound){
    display.setTextSize(2);
    printText(10, 30, "TOO FAR", 2);
  }
  else{
    display.setTextSize(2);
    printText(10, 30, "SAFE", 2);
  }

  printText(8, 56, "Ideal:");
  
  printText(50, 56, lower_bound);

  printText(63, 56, "-");
  printText(70, 56, upper_bound);

  printText(90, 56, "cm");

  */
  display.drawFastHLine(1, 12, 128, SH110X_WHITE);
  

  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  
 

  if (distance < lower_bound || distance > upper_bound){
    printText(16, 24, "WORK NOW", 2);
  }
  else{
    printText(24,4 , "Turkish March");
    display.drawFastHLine(1, 16, 128, SH110X_WHITE);
    printText(8, 24, "W GRINDSET", 2);
    display.drawFastHLine(1, 52, 128, SH110X_WHITE);
    printText(16,56, "Enjoy the music!");
  }
}

void DisplayGraphicCode( void * pvParameters ){
  for(;;){
    status_display(DetectDistance(SafeStatus, LowerBoundSafeDistance, UpperBoundSafeDistance), LowerBoundSafeDistance, UpperBoundSafeDistance);
    display.display();
  }
}



int i = 0;

void MusicHandleCode( void * pvParameters ) {
  for(;;){
    while(i < 338 && SafeStatus){
      tone(BUZZER, Notes[i], 50);
      delay(80 *1.3);
      noTone(BUZZER);
      i++;
    };
    
    if(i>=337){
      i = 0;
    }

  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  display.begin(I2C_ADDRESS, true);
  display.display();
  display.clearDisplay();

  xTaskCreatePinnedToCore(DisplayGraphicCode,
                      "DisplayGraphics",
                      10000,
                      NULL,
                      1, 
                      &GraphicsDisplay,
                      0);
  delay(200);
  xTaskCreatePinnedToCore(MusicHandleCode,
                      "MusicHandle",
                      10000,
                      NULL,
                      1, 
                      &GraphicsDisplay,
                      1);
  delay(200);
}


void loop(){

}

