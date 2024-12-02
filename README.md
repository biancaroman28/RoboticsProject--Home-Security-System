# Robotics Project - Home Security System

## Introduction
This project aims to create a home security system that is both cost-effective and easy to use, focusing on providing essential security features in a simplified manner. The system incorporates sensors to detect motion, monitor air quality, and check light levels. It also uses an RFID card to switch between modes, providing an accessible and affordable solution for home security.

## General Description
- **Secure Mode**: Activated when the user is away from home.If the PIR sensor detects movement:
The alarm (buzzer) sounds for 10 seconds.
The LED flashes rapidly to signal an intrusion.If the ENS160 sensor detects hazardous conditions (toxic gas or poor air quality):
A warning message is sent to the phone via WiFi or Bluetooth.
The LED signals the issue with a specific flashing pattern (e.g., double-flash).
A notification is sent to the phone via WiFi or Bluetooth.The LCD is locked and navigation through menus is disabled.When the user returns home, they must scan a valid RFID card to deactivate Secure mode and activate Normal mode.
- **Normal Mode**: Activated when the user is home. If the ENS160 sensor detects anomalies (toxic gas or poor air quality):
The alarm (buzzer) sounds until conditions return to normal.
The LED flashes slowly to signal the issue. If the PIR sensor detects movement:
The alarm (buzzer) sounds to signal unexpected presence. The LDR sensor monitors ambient light levels:
As it gets darker, the LED gradually becomes brighter (using PWM for smooth transitions). The LCD is active and displays sensor data.




## Hardware Design
### Components
- **LCD + Button**: Used for menu navigation to switch between *Secure* and *Normal* modes. The button allows the user to interact with the system, but the menu is locked in *Secure* mode.
- **RFID**: Deactivates *Secure* mode and activates *Normal* mode when the user scans a valid RFID card.
- **PIR**: Detects movement, used for detecting intrusions when the user is away.
- **ENS160**: Monitors air quality and detects gases or toxic fumes.
- **AHT2x**: Measures temperature and humidity in the environment.
- **LDR (Light Dependent Resistor)**: Monitors the surrounding light levels, used to detect day or night.
- **Arduino Uno**

## Software Design


## Results


## Conclusions


## Source Code


## Journal


## Bibliography

