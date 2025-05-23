# 🧺 Automatic Clothesline System

Drying clothes outdoors is energy-efficient and eco-friendly, but it comes with the risk of sudden weather changes that can dampen your freshly washed laundry. The Automatic Clothesline System is a smart Arduino-based solution designed to safeguard your clothes from unexpected rain or high humidity levels.

At the heart of this project lies an intelligent control system that continuously monitors environmental conditions using two key sensors:
- DHT11: A digital temperature and humidity sensor that helps determine ambient humidity levels. High humidity often indicates impending rain or unsuitable drying conditions.
- YL-83 Rain Sensor Module: Detects raindrops and provides real-time feedback to the microcontroller, enabling immediate action when precipitation is detected.

The system responds to these conditions by driving a 28BYJ-48 stepper motor, controlled through a ULN2003 driver board. This motor is mechanically linked to the clothesline mechanism, allowing the Arduino to automatically retract the clothesline when it rains or when humidity surpasses a user-defined threshold, protecting your laundry from moisture. Conversely, when the weather clears and humidity levels drop below the threshold, the system automatically extends the clothesline, allowing natural drying to resume.

This autonomous system offers hands-free operation, reduces the need for constant weather-checking, and provides peace of mind by ensuring your clothes stay dry even when you're away. Designed to be simple yet robust, the project is ideal for home automation enthusiasts, eco-conscious individuals, and anyone looking to enhance convenience through smart technology.

---

## 🌟 Features

* 🚿 **Automatic retraction during rainfall**
* 💧 **Humidity-based operation** (retracts clothesline when humidity exceeds a defined threshold)
* 🌞 **Automatically extends clothesline when dry**
* ⚙️ **Reliable stepper motor control**
* 🛠️ **Modular and extendable design**

---

## 🔧 Components Used

| Component              | Quantity | Description                               |
| ---------------------- | -------- | ----------------------------------------- |
| Arduino Uno / Nano     | 1        | Microcontroller                           |
| DHT11                  | 1        | Temperature and Humidity Sensor           |
| YL-83 Rain Sensor      | 1        | Analog rain detection module              |
| 28BYJ-48 Stepper Motor | 1        | Controls clothesline extension/retraction |
| ULN2003 Driver Module  | 1        | Drives the stepper motor                  |
| Jumper Wires           | -        | For circuit connections                   |
| Power Supply (5V)      | 1        | External power for stepper motor          |

---

## 🔌 Circuit Diagram



* DHT11:

  * VCC → 5V
  * GND → GND
  * Data → D2

* YL-83 Rain Sensor:

  * VCC → 5V
  * GND → GND
  * AO → A0

* 28BYJ-48 Stepper Motor via ULN2003:

  * IN1 → D8
  * IN2 → D9
  * IN3 → D10
  * IN4 → D11
  * VCC → External 5V
  * GND → GND

---

## 💡 Arduino Sketch Explanation

The sketch performs the following:

1. Reads temperature and humidity from the DHT11 sensor.
2. Monitors analog signal from the YL-83 rain sensor.
3. Decides whether to **retract** or **extend** the clothesline:

   * If it’s **raining** or **humidity > threshold** → retract.
   * If it’s **not raining** and **humidity < threshold** → extend.
4. Controls the 28BYJ-48 stepper motor using the ULN2003 driver.

> Thresholds can be customized in the code for different climates.

---

## 📥 Installation Instructions

1. Clone this repository:

   ```bash
   git clone https://github.com/yourusername/automatic-clothesline.git
   ```
2. Open the `.ino` file in the Arduino IDE.
3. Install required libraries (via Library Manager):

   * `DHT sensor library` by Adafruit
   * `Adafruit Unified Sensor`
4. Connect components as per the circuit diagram.
5. Upload the code to your Arduino board.

---

## 🔄 How It Works

| Condition                         | Action Taken         |
| --------------------------------- | -------------------- |
| Rain detected                     | Retracts clothesline |
| Humidity > threshold (e.g. 85%)   | Retracts clothesline |
| Dry weather, humidity < threshold | Extends clothesline  |

The system continuously monitors the environment. When adverse conditions are detected, it ensures that your clothes are protected without requiring any manual intervention.

---

## 🧪 Simulation 

![Chart Data](https://github.com/user-attachments/assets/d74c27e1-97af-4e1d-a64a-d756e883b37e)

---

## 🚀 Future Improvements

* 🌐 Add IoT capabilities (e.g. ESP8266) for remote monitoring
* 🔋 Include a solar power option for sustainability
* 📲 Mobile notification support for status alerts
* 🌬️ Add wind speed sensor for comprehensive weather detection
* 🧠 Integrate machine learning for adaptive decision-making
