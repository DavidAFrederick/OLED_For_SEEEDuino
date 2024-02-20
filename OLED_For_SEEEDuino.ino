// Feb 19, 2024
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int sensor_one_pin = 1;
const int sensor_two_pin = 2;
const int sensor_three_pin = 3;
// Pin 4 is used for I2C. SDA. (DATA)
// Pin 6 is used for I2C. SCL. (CLOCK)
const int sensor_four_pin = 6;
const int ledPin = 13;


int sensorOneState = 0;
int sensorTwoState = 0;
int sensorThreeState = 0;
int sensorFourState = 0;

//========================================================================
void setup() {
  Serial.begin(9600);

  // initialize the pushbutton pin as an input:
  pinMode(sensor_one_pin, INPUT);
  pinMode(sensor_two_pin, INPUT);
  pinMode(sensor_three_pin, INPUT);
  pinMode(sensor_four_pin, INPUT);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  display.clearDisplay();
  displayText("Initializing");  // Draw 'stylized' characters
  delay(1000);
}
//========================================================================
void loop() {

  readSensors();

  // - TEMP Setting
  sensorTwoState = 1;  // 1 = not present
  sensorThreeState = 0;
  sensorFourState = 0;
  //

  displayLengthPosition();

  // displayDetectionStatus();

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

void displayDetectionStatus() {
  if (sensorOneState == 1) {
    digitalWrite(ledPin, HIGH);  // Turn LED On
    displayText("NOT Detected");
  } else {
    digitalWrite(ledPin, LOW);  // Yurn LED Off
    displayText("Detected");
  }
}

void displayLengthPosition() {
  int distance_position = sensorFourState * 8 + sensorThreeState * 4 + sensorTwoState * 2 + sensorOneState;

  // displayText("Position: ");
  displayPosition(distance_position);
}

void readSensors() {
  sensorOneState = ! digitalRead(sensor_one_pin);
  sensorTwoState = ! digitalRead(sensor_two_pin);
  sensorThreeState = ! digitalRead(sensor_three_pin);
  sensorFourState = ! digitalRead(sensor_four_pin);
}
//========================================================================