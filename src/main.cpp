#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Wire.h>
#include <WiFi.h>

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
  display.begin(I2C_ADDRESS, true);
}



void status_display(int distance, int lower_bound, int upper_bound){
  delay(50);
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);
  
  display.setCursor(8, 48);
  display.print("Ideal:");
  
  display.setCursor(20, 48);
  display.print(lower_bound);

  display.setCursor(30, 48);
  display.print(upper_bound);

  display.setCursor(40, 48);
  display.print("cm");
}

void loop() {
  // put your main code here, to run repeatedly:
  status_display(65, 50, 66);
  display.display();
}

