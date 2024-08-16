#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Wire.h>
#include <WiFi.h>
#include <distance_detect.h>

#define I2C_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

int LowerBoundSafeDistance = 50;
int UpperBoundSafeDistance = 66;

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  display.begin(I2C_ADDRESS, true);
  display.display();
  display.clearDisplay();
  

}

void printText(int x, int y, String text){
  display.setCursor(x, y);
  display.print(text);
}

void printText(int x, int y, int value){
  display.setCursor(x, y);
  display.print(value);
}

void status_display(float distance, int lower_bound, int upper_bound){
  delay(10);
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);
  
  display.drawFastHLine(1, 12, 128, SH110X_WHITE);
  display.drawFastHLine(1, 52, 128, SH110X_WHITE);

  printText(8, 56, "Ideal:");
  
  printText(50, 56, lower_bound);

  printText(63, 56, "-");
  printText(70, 56, upper_bound);

  printText(90, 56, "cm");

  printText(10, 0, "Distance: ");

  printText(70, 0, static_cast<int>(round(distance)) );
}


void loop() {
  // put your main code here, to run repeatedly:
  status_display(DetectDistance(), 50, 66);
  display.display();
}

