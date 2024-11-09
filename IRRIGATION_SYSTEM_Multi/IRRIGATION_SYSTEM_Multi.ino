#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD with I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Relay and Soil Sensor Pins
int relay_pins[5] = {2, 3, 4, 5, 6};        // Relay pins
int soil_pins[5] = {9, 10, 11, 12, 13};      // Soil sensor pins
String motor_status[5];                      // Motor status storage

void setup() {
  // Initialize relay and soil sensor pins
  for (int i = 0; i < 5; i++) {
    pinMode(relay_pins[i], OUTPUT);  // Set relay pins as outputs
    pinMode(soil_pins[i], INPUT);    // Set soil sensor pins as inputs
    digitalWrite(relay_pins[i], HIGH);  // Turn off all relays initially
  }

  // Initialize Serial for debugging
  Serial.begin(9600);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Irrigation Sys");
  delay(2000);  // Initial message display delay
  lcd.clear();
}

void loop() {
  // Iterate through all 5 sensors and motors
  for (int i = 0; i < 5; i++) {
    int sensor_status = digitalRead(soil_pins[i]);  // Read soil sensor value
    if (sensor_status == HIGH) {  // If the soil is dry
      digitalWrite(relay_pins[i], LOW);  // Turn on the motor (active LOW)
      motor_status[i] = "ON";  // Update motor status
      Serial.print("Motor ");
      Serial.print(i + 1);
      Serial.println(": ON (Soil is dry)");
    } else {  // If the soil is wet
      digitalWrite(relay_pins[i], HIGH);  // Turn off the motor
      motor_status[i] = "OFF";  // Update motor status
      Serial.print("Motor ");
      Serial.print(i + 1);
      Serial.println(": OFF (Soil is wet)");
    }
  }

  // Display status of all 5 motors on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);  // First line
  lcd.print("M1:");
  lcd.print(motor_status[0]);
  lcd.print(" M2:");
  lcd.print(motor_status[1]);
  lcd.setCursor(0, 1);  // Second line
  lcd.print("M3:");
  lcd.print(motor_status[2]);
  lcd.print(" M4:");
  lcd.print(motor_status[3]);
  lcd.setCursor(9, 1);  // Second line continuation for M5
  lcd.print("M5:");
  lcd.print(motor_status[4]);

  // Print all statuses to Serial Monitor
  Serial.println("Motor Status Summary:");
  Serial.println("M1: " + motor_status[0] + " | M2: " + motor_status[1] +
                 " | M3: " + motor_status[2] + " | M4: " + motor_status[3] +
                 " | M5: " + motor_status[4]);
  Serial.println("-------------------------");

  delay(1000);  // Delay between updates
}
