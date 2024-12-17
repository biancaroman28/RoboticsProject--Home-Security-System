# Robotics Project - Home Security System

## Introduction
A lot of security systems out there are expensive and can be difficult to set up or use. For this project, I decided to design a simpler, more budget-friendly version that still offers key features like motion detection, air quality monitoring, day/night detection, and gas leak detection. The goal was to prove that you don’t need to spend a lot of money to have a reliable security system that’s easy to use and works well.
## General Description
- **Secure Mode**: Activated when the user is away from home. If the PIR sensor detects movement, the alarm sounds for 10 seconds. The LED flashes rapidly to signal an intrusion. If the ENS160 sensor detects anomalies (toxic gas or poor air quality) a warning message is sent to the phone via WiFi or Bluetooth. The LCD is locked and navigation through menus is disabled. When the user returns home, they must scan a valid RFID card to deactivate Secure mode and activate Normal mode.
- **Normal Mode**: Activated when the user is home. If the ENS160 sensor detects anomalies, the alarm sounds until conditions return to normal, or is disabled. The LED flashes slowly to signal the issue. If the PIR sensor detects movement,the alarm sounds to signal unexpected presence. The LDR sensor monitors ambient light levels:as it gets darker, the LED gradually becomes brighter. The LCD is active and displays sensor data.
![image](https://github.com/user-attachments/assets/f2943e64-69d5-4247-880b-fb778025ef50)



## Hardware Design
### Components
- **LCD + Button**: Used for menu navigation to switch between *Secure* and *Normal* modes. The button allows the user to interact with the system, but the menu is locked in *Secure* mode.
- **RFID**: Deactivates *Secure* mode and activates *Normal* mode when the user scans a valid RFID card.
- **PIR**: Detects movement, used for detecting intrusions when the user is away.
- **ENS160**: Monitors air quality and detects gases or toxic fumes.
- **AHT2x**: Measures temperature and humidity in the environment.
- **LDR**: Monitors the surrounding light levels, used to detect day or night.
- **Arduino Uno**

## Software Design


## Results


## Conclusions


## Source Code


## Journal


## Bibliography

