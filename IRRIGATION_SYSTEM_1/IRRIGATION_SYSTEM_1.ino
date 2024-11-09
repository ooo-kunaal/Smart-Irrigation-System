#include <Wire.h>                // I2C library
#include <LiquidCrystal_I2C.h>    // LCD library

LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 is the I2C address

int sensor_pin = A0;  // Use A0 for analog input
int relay_pin = 3;    // Relay control pin

void setup() {
  // Start Serial communication
  Serial.begin(9600);
  
  // Pin Modes
  pinMode(sensor_pin, INPUT);
  pinMode(relay_pin, OUTPUT);

  // Turn off relay initially
  digitalWrite(relay_pin, LOW);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.backlight();  // Turn on LCD backlight

  lcd.setCursor(0, 0);
  lcd.print("Setup Complete");
  delay(2000);      // Delay to see the message
  lcd.clear();
  
  Serial.println("Setup Complete");
}

void loop() {
  // Read analog data from the sensor
  int sensor_data = analogRead(sensor_pin);
  
  // Debugging the sensor value
  Serial.print("Sensor_data: ");
  Serial.println(sensor_data);

  // Clear the LCD to print new data
  lcd.clear();
  
  // Logic to control the relay based on sensor data
  if (sensor_data > 950) {
    // Dry soil condition, turn motor on
    Serial.println("Dry Soil, motor on");
    digitalWrite(relay_pin, HIGH);  // Turn the motor on
    lcd.setCursor(0, 0);
    lcd.print("Dry Soil");
    lcd.setCursor(0, 1);
    lcd.print("Motor ON");
    
  } else if (sensor_data >= 400 && sensor_data <= 950) {
    // Moist soil, turn motor off
    Serial.println("Moist Soil, motor off");
    digitalWrite(relay_pin, LOW);   // Turn the motor off
    lcd.setCursor(0, 0);
    lcd.print("Moist Soil");
    lcd.setCursor(0, 1);
    lcd.print("Motor OFF");

  } else if (sensor_data < 400) {
    // Wet soil, turn motor off
    Serial.println("Wet Soil, motor off");
    digitalWrite(relay_pin, LOW);   // Turn the motor off
    lcd.setCursor(0, 0);
    lcd.print("Wet Soil");
    lcd.setCursor(0, 1);
    lcd.print("Motor OFF");
  }
  
  // Small delay for stability
  delay(1000);
}
