#include <Arduino.h>
#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // You will need to install this library in PlatformIO/Arduino IDE

// --- Pins and Settings ---
const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN = 17;
const float CALIBRATION_FACTOR = 13800.0;

HX711 scale;
// Initialize the LCD at I2C address 0x27 (standard), with 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// --- Function Declarations ---
void displayWeight(float weight);

void setup() {
  Serial.begin(115200);
  
  // 1. Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Scale");
  lcd.setCursor(0, 1);
  lcd.print("Starting up...");

  Serial.println("Initializing the scale...");

  // 2. Initialize the HX711
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  
  // 3. Apply your custom human-tested calibration factor
  scale.set_scale(CALIBRATION_FACTOR);  
  
  // 4. Tare to remove the weight of the wooden board
  scale.tare();               
  
  Serial.println("Scale is ready!");
  
  // Clear the startup message and prep the LCD UI
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weight:");
}

void loop() {
  // Get a single reading and a 10-sample average for Serial analysis
  float singleReading = scale.get_units(1);
  float averageReading = scale.get_units(10);
  
  // Zero-snapping: Hide microscopic drift for the LCD when empty
  float displayVal = averageReading;
  if (displayVal < 0.0 && displayVal > -0.2) {
    displayVal = 0.0;
  }

  // Print detailed data to Serial monitor (like before for analysis)
  Serial.println(averageReading, 5);

  // Update the LCD screen
  displayWeight(displayVal);

  // Short delay so the numbers don't blur past too fast to read
  delay(250); 
}

// --- Custom LCD Display Function ---
void displayWeight(float weight) {
  lcd.setCursor(0, 1); // Move to the second row
  
  // If weight is negative (someone lifted the board), show 0 to avoid UI glitches
  if (weight < 0) {
    lcd.print("0.0 kg          "); 
  } else {
    // Print the weight
    lcd.print(weight, 1);
    lcd.print(" kg          "); // The extra spaces overwrite leftover characters from previous larger numbers
  }
}