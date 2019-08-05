#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  16

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

int high = 0;
int prevHigh = 0;
int counter = 0;
int counter_x = 0;
int counter_y = 0;
bool reset_x = false;
bool reset_y = false;
int duty_x = 0;
int duty_y = 0;
int timer = 0;
bool counting = false;

int pos_x = 0;
int pos_y = 0;

float r, g, b = 0;
float target_r = 0;
float target_b = 0;
float target_g = 0;
float x = 0;
float y = 0;

byte rb;
byte gb;
byte bb;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  Serial.println("tracker");
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(25); // Set BRIGHTNESS to about 1/5 (max = 255)
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, 10, 10, 10);
  }
  strip.show();
  bool sync = false;
  // =================================================================  syncing
  while (!sync) {
    delay(1);
    prevHigh = high;
    int sensorValue0 = analogRead(A0);
    int sensorValue1 = analogRead(A1);
    if (sensorValue0 > sensorValue1) high = sensorValue0;
    else high = sensorValue1;
    if (high - prevHigh >= 10) {
      // rising edge
      counter = 0;
    } else if (prevHigh - high >= 10) {
      // falling edge

      counter = 0;
    } else if (high < 10 && prevHigh < 10) {
      // stay 0
      counter++;
    } else {
      // stay 1
      counter = 0;
    }
    if (counter > 100) {
      counter = 2000;
      duty_x = 0;
      duty_y = 0;
      sync = true;
    }
  }
}

// the loop routine runs over and over again forever:
void loop() {
  // =================================================================  reading
  prevHigh = high;
  int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  if (sensorValue0 > sensorValue1) high = sensorValue0;
  else high = sensorValue1;
  //  Serial.println(high);
  //                Serial.print("    ");
  if (prevHigh - high >= 10 && !counting) {
    //      Serial.println("start counting!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    timer = millis();
    counting = true;
    duty_x = 0;
    duty_y = 0;
  }
  // =================================================================  position
  if (counting) {
    if (millis() - timer < 100) {
      //      Serial.println("counting   X");
      if (prevHigh > 10 && high > 10) duty_x++;
    } else if (millis() - timer < 250) {
      //      Serial.println("counting   Y");
      if (prevHigh > 10 && high > 10) duty_y++;
    } else {
      counting = false; // -------------------------------------------  coordinating done
      Serial.print(duty_x);
      Serial.print(" ");
      Serial.println(duty_y);
    }
  }
  // =================================================================  RGB LED
  if (Serial.available() > 0) { // -----------------------------------  receive led infor
    // read the incoming byte:
    rb = Serial.read();
    gb = Serial.read();
    bb = Serial.read();
  }
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, rb, gb, bb);
  }
  strip.show();
}
