#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>  
#include <PulseSensorPlayground.h>     

#define USE_ARDUINO_INTERRUPTS true
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

const int PulseWire = 2; // We used A0, A1 for OLED SCREEN A2 is for sensor
PulseSensorPlayground pulseSensor;  

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  pulseSensor.analogInput(PulseWire); 
  pulseSensor.setThreshold(550);   
  delay(2000);

}

void loop() {
  int myBPM = pulseSensor.getBeatsPerMinute(); // Getting heart beats here  

  if (pulseSensor.sawStartOfBeat()) {
    // If we get some pulse then do this. DO what? Print on OLED screen
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println(myBPM); // Put here myBPM
    display.display(); 
  }


  
}