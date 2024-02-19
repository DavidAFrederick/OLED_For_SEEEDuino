#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels


#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


const int sensor_one_pin = 1;
const int sensor_two_pin = 2;
const int sensor_three_pin = 3;

int sensorOneState = 0;
const int ledPin =  13;
String  stringToDisplay = "Initializing";

void setup() {
  Serial.begin(9600);
  

 // initialize the pushbutton pin as an input:
  pinMode(sensor_one_pin, INPUT);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
  stringToDisplay = "Initializing";
  displayText(stringToDisplay);    // Draw 'stylized' characters

}

void loop() {

   sensorOneState = digitalRead(sensor_one_pin);

  if (sensorOneState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    stringToDisplay = "NOT Detected";
    displayText(stringToDisplay);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    stringToDisplay = "Detected";
    displayText(stringToDisplay);
  }
  delay(100);
}


void displayText(String stringToDisplay) {
  display.clearDisplay();

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(stringToDisplay);
//  display.println(F("Initializing......."));

  display.display();
}
