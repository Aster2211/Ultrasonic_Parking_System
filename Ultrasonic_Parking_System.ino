#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin Definitions
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int BUZZER_PIN = 11;

// Variables
long duration;
int distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Keep Active-LOW buzzer silent initially
  digitalWrite(BUZZER_PIN, HIGH);

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Distance Meter");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1500);
  lcd.clear();
}

void loop() {
  // 1. Send a 10-microsecond HIGH pulse to trigger sound wave
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // 2. Read travel duration in microseconds (time-of-flight)
  duration = pulseIn(ECHO_PIN, HIGH);

  // 3. Calculate distance in centimeters
  // Speed of sound = 0.0343 cm/us -> Divide by 2 for round-trip distance
  distance = duration * 0.0343 / 2;

  // 4. Update LCD Display
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm   "); // Extra spaces clear residual numbers

  lcd.setCursor(0, 1);
  if (distance > 30 || distance <= 0) {
    lcd.print("Status: Safe     ");
  } else if (distance <= 30 && distance > 10) {
    lcd.print("Status: Warning! ");
  } else {
    lcd.print("Status: STOP!    ");
  }

  // 5. Proximity Alarm Logic (Dynamic Beep Rate)
  if (distance > 0 && distance <= 10) {
    // Solid warning beep when extremely close
    digitalWrite(BUZZER_PIN, LOW); 
  } else if (distance > 10 && distance <= 30) {
    // Pulse beep speed scales with proximity
    digitalWrite(BUZZER_PIN, LOW);
    delay(50);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(distance * 15); // Closer distance = shorter pause = faster beeping
  } else {
    // Silent when out of danger zone
    digitalWrite(BUZZER_PIN, HIGH);
  }

  delay(100); // Sensor stability sampling delay
}