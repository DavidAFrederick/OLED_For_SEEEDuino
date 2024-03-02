// March 1, 2024
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int sensorPin = A1; 
int sensorValue = 0;

//========================================================================
void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  display.clearDisplay();
  displayText("Initializing");  // Draw 'stylized' characters
  delay(1000);

// analogReference(AR_DEFAULT);    // 3.3 V
// analogReference(AR_INTERNAL1V0);
// analogReference(AR_INTERNAL2V23);
// analogReference(AR_INTERNAL1V65);

}
//========================================================================
void loop() {

  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  displayVoltage(sensorValue);

  // displayLengthPosition();

  delay(10);
}
//========================================================================

void displayText(String stringToDisplay) {
  display.clearDisplay();

  display.setTextSize(2);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 0);              // Start at top-left corner
  display.println(stringToDisplay);
  display.display();
}

void displayPosition(int position) {
  display.clearDisplay();
  displayText("Position: ");

  display.setTextSize(2);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  // display.setCursor(0, 16);             // Start at top-left corner
  display.setCursor(position * 10, 16);             // Start at top-left corner
  display.println(position);
  display.display();
}

void displayVoltage(int voltageToDisplay) {
  display.clearDisplay();

  display.setTextSize(2);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 16);              // Start at top-left corner
  display.println( voltageToDisplay);
  display.display();
}



// void displayDetectionStatus() {
//   if (sensorOneState == 1) {
//     digitalWrite(ledPin, HIGH);  // Turn LED On
//     displayText("NOT Detected");
//   } else {
//     digitalWrite(ledPin, LOW);  // Yurn LED Off
//     displayText("Detected");
//   }
// }

void displayLengthPosition(int numberToDisplay) {
  // int distance_position = 10;
  // sensorFourState * 8 + sensorThreeState * 4 + sensorTwoState * 2 + sensorOneState;

  // displayText("Position: ");
  displayPosition(numberToDisplay);
}

// void readSensors() {
//   sensorOneState = ! digitalRead(sensor_one_pin);
//   sensorTwoState = ! digitalRead(sensor_two_pin);
//   sensorThreeState = ! digitalRead(sensor_three_pin);
//   sensorFourState = ! digitalRead(sensor_four_pin);
// }
//========================================================================
