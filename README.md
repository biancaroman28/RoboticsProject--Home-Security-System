# Robotics Project - Home Security System

## Introduction
A lot of security systems out there are expensive and can be difficult to set up or use. For this project, I decided to design a simpler, more budget-friendly version that still offers key features like motion detection, air quality monitoring, day/night detection, and gas leak detection. The goal was to prove that you don’t need to spend a lot of money to have a reliable security system that’s easy to use and works well.
## General Description
- **Secure Mode**: Activated when the user is away from home. If the PIR sensor detects movement, the alarm sounds for 10 seconds. The LED flashes rapidly to signal an intrusion. If the ENS160 sensor detects anomalies (toxic gas or poor air quality) a warning message is sent to the phone via WiFi or Bluetooth. The LCD is locked and navigation through menus is disabled. When the user returns home, they must scan a valid RFID card to deactivate Secure mode and activate Normal mode.
- **Normal Mode**: Activated when the user is home. If the ENS160 sensor detects anomalies, the alarm sounds until conditions return to normal, or is disabled. The LED flashes slowly to signal the issue. If the PIR sensor detects movement,the alarm sounds to signal unexpected presence. The LDR sensor monitors ambient light levels:as it gets darker, the LED gradually becomes brighter. The LCD is active and displays sensor data.

![image](https://github.com/user-attachments/assets/f2943e64-69d5-4247-880b-fb778025ef50)



## Hardware Design
## **2. Components and Their Roles**
Here is a list of the components used in the project along with their roles:

- **ESP32 Devkit**: The microcontroller acts as the central processing unit, handling all sensor data, processing inputs, and managing outputs.  
- **16x2 LCD**: Displays sensor readings and system status.  
- **PIR Sensor**: Detects motion for intrusion detection.  
- **ENS160 Sensor**: Monitors air quality and gas presence.  
- **AHT2x Sensor**: Measures temperature and humidity.  
- **LDR Sensor**: Monitors ambient light levels for day/night detection.  
- **RFID Module**: Activates or deactivates Secure Mode using valid RFID cards.  
- **Passive Buzzer**: Sounds an alarm for anomalies or intrusions.  
- **Red LED**: Indicates intrusions or system alerts.  
- **50k Potentiometer**: Used for LCD brightness control.  

---

## **3. Block Diagram**
Below is the block diagram of the project, showing all components and their connections to the ESP32 microcontroller:

![Block Diagram](path_to_your_image)  
*Figure 1: Block Diagram of the System.*

---

## **4. Circuit Schematic**
The electrical connections between components are represented in the circuit schematic:

![Circuit Schematic](path_to_your_circuit_image)  
*Figure 2: Electrical Schematic of the System.*

---

## **5. Bill of Materials (BOM)**
The table below lists all the components used in the project with relevant links and datasheets:

| **Component**       | **Description**              | **Quantity** | **Link/Datasheet**                   |
|----------------------|------------------------------|-------------|--------------------------------------|
| ESP32 Devkit         | Microcontroller             | 1           | [ESP32 Datasheet](link_here)         |
| 16x2 LCD             | Display for data            | 1           | [LCD Module](link_here)              |
| 50k Potentiometer    | Brightness control for LCD  | 1           | [Potentiometer Datasheet](link_here) |
| PIR Sensor           | Motion detection            | 1           | [PIR Sensor Datasheet](link_here)    |
| ENS160 Sensor        | Air quality sensor          | 1           | [ENS160 Datasheet](link_here)        |
| AHT2x Sensor         | Temperature & Humidity      | 1           | [AHT2x Datasheet](link_here)         |
| LDR Sensor           | Light detection             | 1           | [LDR Info](link_here)                |
| RFID Module          | Secure mode activation      | 1           | [RFID Datasheet](link_here)          |
| Passive Buzzer       | Alarm                       | 1           | [Buzzer Info](link_here)             |
| Red LED              | Alert indicator             | 1           | [Red LED Info](link_here)            |
| Jumper Wires         | Connections                 | -           | [Jumper Wires](link_here)            |

---

## **6. Detailed Hardware Description**
Below is a detailed explanation of the hardware setup and functionalities:

### **ESP32 Devkit**
- The ESP32 acts as the central microcontroller managing all inputs and outputs.
- Interfaces:  
  - **I2C**: ENS160, AHT2x Sensors, and LCD  
  - **SPI**: RFID Module  
  - **GPIO/PWM**: PIR sensor, buzzer, LED, and LDR  

---

### **LCD Display (16x2)**
- Connected to the ESP32 for displaying sensor readings and status.  
- **Pins Used**:  

| **LCD Pin** | **ESP32 Pin** | **Potentiometer Pin** | **Purpose**            |
|-------------|---------------|-----------------------|------------------------|
| 1 & 16      | GND           | Pin 1                | Ground connection      |
| 2 & 15      | 3.3V          | Pin 3                | Power (3.3V)           |
| 3           | Signal (Pin 2)| -                    | LCD contrast control   |
| 4           | GPIO 22       | -                    | RS Pin                 |
| 5           | GND           | -                    | R/W Pin (Grounded)     |
| 6           | GPIO 23       | -                    | Enable Pin             |
| 11          | GPIO 5        | -                    | Data Pin D4            |
| 12          | GPIO 18       | -                    | Data Pin D5            |
| 13          | GPIO 19       | -                    | Data Pin D6            |
| 14          | GPIO 21       | -                    | Data Pin D7            |

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

## **7. Pin Mapping**
Below is the complete pin mapping for the project:

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

## **8. Hardware Images and Proof of Functionality**
### **Image 1: Components Connected**
![Components Connected](path_to_your_image)  

### **Image 2: Working Component Example**
![Working Example](path_to_working_example_image)  
*Figure X: Demonstration of the RFID module successfully activating Normal Mode.*


## Software Design


## Results


## Conclusions


## Source Code


## Journal


## Bibliography

