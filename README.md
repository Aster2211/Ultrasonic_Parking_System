# 📏 Ultrasonic Distance Meter & Parking Assistant

A 2nd-year ECE embedded systems mini-project featuring an ultrasonic distance meter and reverse parking assistant built with an Arduino Uno, HC-SR04 sensor, 16x2 I2C LCD, and active-LOW buzzer.

## 📌 Key Features
- **Time-of-Flight Physics:** Emits 10µs ultrasonic sound bursts at 40 kHz and calculates distance based on echo duration ($d = \frac{t \times 0.0343}{2}$).
- **Real-Time Visual Feedback:** Displays exact distance in centimeters along with dynamic status indicators (`Safe`, `Warning!`, `STOP!`).
- **Dynamic Proximity Alarm:** Scales active-LOW buzzer beep intervals proportionally to object proximity to emulate a vehicle reverse parking radar.

## 🔌 Circuit Pinout

| Component | Pin | Arduino Uno Pin | Notes |
| :--- | :--- | :--- | :--- |
| **I2C LCD** | VCC / GND | **5V / GND** | Display Power |
| **I2C LCD** | SDA / SCL | **A4 / A5** | I2C Communication (`0x27`) |
| **Active-LOW Buzzer** | I/O | **Digital Pin 11** | Proximity warning alerts |
| **HC-SR04** | VCC / GND | **5V / GND** | Sensor Power |
| **HC-SR04** | **Trig** | **Digital Pin 9** | Emits 10µs sound pulse |
| **HC-SR04** | **Echo** | **Digital Pin 10** | Measures echo pulse return time |

## 🛠️ Software Requirements
- **Arduino IDE**
- **LiquidCrystal_I2C** Library
