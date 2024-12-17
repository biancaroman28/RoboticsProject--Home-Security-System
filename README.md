# Robotics Project - Home Security System

## Introduction
A lot of security systems out there are expensive and can be difficult to set up or use. For this project, I decided to design a simpler, more budget-friendly version that still offers key features like motion detection, air quality monitoring, day/night detection, and gas leak detection. The goal was to prove that you don’t need to spend a lot of money to have a reliable security system that’s easy to use and works well.
## General Description
- **Secure Mode**: Activated when the user is away from home. If the PIR sensor detects movement, the alarm sounds for 10 seconds. The LED flashes rapidly to signal an intrusion. If the ENS160 sensor detects anomalies (toxic gas or poor air quality) a warning message is sent to the phone via WiFi or Bluetooth. The LCD is locked and navigation through menus is disabled. When the user returns home, they must scan a valid RFID card to deactivate Secure mode and activate Normal mode.
- **Normal Mode**: Activated when the user is home. If the ENS160 sensor detects anomalies, the alarm sounds until conditions return to normal, or is disabled. The LED flashes slowly to signal the issue. If the PIR sensor detects movement,the alarm sounds to signal unexpected presence. The LDR sensor monitors ambient light levels:as it gets darker, the LED gradually becomes brighter. The LCD is active and displays sensor data.




## Hardware Design
## **1. Components and Their Roles**
- **ESP32**: The microcontroller acts as the central processing unit, handling all sensor data, processing inputs, and managing outputs.  
- **16x2 LCD**: Displays sensor readings and system status.  
- **PIR Sensor**: Detects motion for intrusion detection.  
- **ENS160 Sensor**: Monitors air quality and gas presence.  
- **AHT2x Sensor**: Measures temperature and humidity.  
- **LDR Sensor**: Monitors ambient light levels for day/night detection.  
- **RFID Module**: Activates or deactivates Secure Mode using valid RFID cards.  
- **Passive Buzzer**: Sounds an alarm for anomalies or intrusions.  
- **LED**: Indicates intrusions or system alerts.  
- **50k Potentiometer**: Used for LCD brightness control.  

---

## **2.Diagrams**
![image](https://github.com/user-attachments/assets/cdc49d3e-e275-4b51-b4ec-edb934304796)
![image](https://github.com/user-attachments/assets/14c6337c-a5f5-4bc3-aa8e-5e9ce893afe6)



## **3. Bill of Materials (BOM)**


| **Component**       | **Description**              | **Datasheet**                        | **Source/Purchase Link**             |
|----------------------|------------------------------|--------------------------------------|--------------------------------------|
| ESP32          | Microcontroller             | [ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf) | [Purchase Link](https://www.robofun.ro/platforme-de-dezvoltare/esp-wroom-32-wifi-module-ch340-type-c.html)       |
| 16x2 LCD             | Display for data            |                                       | Kit       |
| 50k Potentiometer    | Brightness control for LCD  |                                       | Kit      |
| PIR Sensor           | Motion detection            |                                           | [Purchase Link](https://www.robofun.ro/senzori/modul-senzor-de-miscare-pir.html)       |
| ENS160 Sensor        | Air quality sensor          | [ENS160 Datasheet](https://www.mouser.com/datasheet/2/1081/SC_001224_DS_1_ENS160_Datasheet_Rev_0_95-2258311.pdf?srsltid=AfmBOopD5iQ_zGEQW9MNsx139wTIkgXACXXDjR8WssaWiWnYD_jbje7h)|       |
| AHT2x Sensor         | Temperature & Humidity      | [AHT2x Datasheet](link_to_datasheet) |        |
| LDR Sensor           | Light detection             |    | Kit       |
| RFID Module          | Secure mode activation      |  |        |
| Passive Buzzer       | Alarm                       | | Kit       |
| Red LED              | Alert indicator             | | Kit       |
| Jumper Wires         | Connections                 | | Kit     |

---

## **5. Detailed Hardware Description**

### **ESP32**
- The ESP32 acts as the central microcontroller managing all inputs and outputs.
- Interfaces:  
  - **I2C**: ENS160, AHT2x Sensors  
  - **SPI**: RFID Module  
  - **GPIO/PWM**: PIR sensor, buzzer, LED, LCD
  - **ADC**: LDR Sensor

---

### **LCD Display (16x2)**
- Connected to the ESP32 for displaying sensor readings and status.  
- **Pins Used**:  

| **LCD Pin** | **ESP32 Pin** | **Potentiometer Pin** | **Purpose**            |
|-------------|---------------|-----------------------|------------------------|
| 1 & 16      | GND           | Pin 1                | Ground connection      |
| 2 & 15      | 3.3V          | Pin 3                | Power (3.3V)           |
| 3           | -             | Pin 2                | LCD contrast control   |
| 4           | GPIO 12       | -                    | RS Pin                 |
| 5           | GND           | -                    | R/W Pin (Grounded)     |
| 6           | GPIO 14       | -                    | Enable Pin             |
| 11          | GPIO 27        | -                    | Data Pin D4            |
| 12          | GPIO 2       | -                    | Data Pin D5            |
| 13          | GPIO 15       | -                    | Data Pin D6            |
| 14          | GPIO 13       | -                    | Data Pin D7            |

**Potentiometer**: 50k potentiometer adjusts the LCD brightness.

---

### **ENS160 & AHT2x Sensors**
- **I2C Interface**:  
  - SDA → GPIO **21**  
  - SCL → GPIO **22**  
- **Power**:  
  - VCC → **3.3V**  
  - GND → **GND**  
- **Function**: Monitors air quality, gas presence, temperature, and humidity.  

---

### **RFID Module**
- **SPI Interface**:  
  - SDA → GPIO **5**  
  - SCK → GPIO **18**  
  - MISO → GPIO **19**  
  - MOSI → GPIO **23**  
  - RST → GPIO **17**  
- **Power**:  
  - VCC → **3.3V**  
  - GND → **GND**  
- **Function**: Scans valid RFID cards to toggle between Secure and Normal Modes.

---

### **PIR Sensor**
- **Pins**:  
  - Signal → GPIO **32**  
  - VCC → **3.3V**  
  - GND → **GND**  
- **Function**: Detects motion for intrusion detection.

---

### **Passive Buzzer**
- **Pin**: PWM GPIO **16**  
- **Function**: Sounds alarms for anomalies or intrusions.

---

### **Red LED**
- **Pin**: GPIO **26**  
- **Function**: Indicates system alerts (e.g., intrusion detection).

---

### **LDR Sensor**
- **Pin**: Analog GPIO **33**  
- **Function**: Monitors ambient light for day/night detection.

---

## **6. Pin Mapping**

| **Component**        | **ESP32 Pin**      | **Purpose**                |
|-----------------------|--------------------|----------------------------|
| ENS160 Sensor         | GPIO 21, 22       | I2C (SDA, SCL)             |
| AHT2x Sensor          | GPIO 21, 22       | I2C (SDA, SCL)             |
| RFID Module           | GPIO 5, 18, 19, 23| SPI (SDA, CLK, MISO, MOSI) |
| RFID Reset Pin        | GPIO 17           | RST                        |
| PIR Sensor            | GPIO 32           | Motion detection input     |
| Passive Buzzer        | GPIO 16 (PWM)     | Alarm                      |
| Red LED               | GPIO 26           | Alert indicator            |
| LDR Sensor            | GPIO 33 (ADC)     | Light level detection      |
| LCD Pins              | GPIO 5, 18, 19, 21, 22, 23 | LCD Display              |

---

## **7. Hardware Images and Proof of Functionality**
### **Image 1: Components Connected**
![image](https://github.com/user-attachments/assets/062940bd-4cc3-4656-a09b-3dfddd561aad)
  

### **Image 2: Working Component Example**
![image](https://github.com/user-attachments/assets/6fd86ac7-9a33-471c-be5f-e420d2aaae4b)


https://github.com/user-attachments/assets/bcbf2db4-0fdf-4d63-8e8c-8716478da93b



https://github.com/user-attachments/assets/9d53ba2b-810f-4c06-86e0-a586a8709767




## Software Design


## Results


## Conclusions


## Source Code


## Journal


## Bibliography

