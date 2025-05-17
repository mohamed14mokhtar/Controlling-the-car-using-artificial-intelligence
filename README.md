# 🚗 Control the Car Using Artificial Intelligence

A smart car control system built using STM32, Arduino, ESP32, and AI. The car can be remotely controlled through a mobile app or intelligently stopped using a traffic sign detection AI model. The system also supports FOTA (Firmware Over-the-Air) updates via MQTT and Firebase.

---
## 📑 Table of Contents
1. [System Overview](#system-overview)
2. [Control Methods](#control-methods)
3. [FOTA (Firmware Over-The-Air)](#fota-firmware-over-the-air)
4. [Software Architecture](#software-architecture)
5. [Technologies & Tools Used](#technologies--tools-used)
6. [Software Tools](#software-tools)
7. [Features](#features)
8. [Future Enhancements](#future-enhancements)
9. [Team Members](#team-members)

---
## 🔧 System Overview

### 🧠 Main Controller: STM32F401RCT6
- Central brain of the system.
- Communicates with:
  - **ESP32** via **SPI** (receives app commands via MQTT).
  - **Arduino Uno** via **Bluetooth (HC-05)**.
  - **ESP8266** via **UART** (for FOTA updates).
  - **PC-based AI model** via **USB (UART-over-USB)**.
<p align="center">
  <img src="https://github.com/user-attachments/assets/0b0172f3-c7bc-4a31-b131-0acf431061b5" alt="Project Overview 1" width="45%" style="margin-right: 10px;" />
  <img src="https://github.com/user-attachments/assets/7aba6b28-6d8b-4bf1-ab34-adf24c880c92" alt="Project Overview 2" width="45%" />
</p>


### 🚗 Car Unit
- **Arduino Uno** + **Motor Driver**
- 4x **DC Motors** for movement
- **Ultrasonic Sensor** for obstacle detection
- **HC-05 Bluetooth Module** receives commands from STM32

> 🔁 Bluetooth Communication:
> - 1x HC-05 connected to STM32  
> - 1x HC-05 connected to Arduino Uno (car)

---

## 📱 Control Methods

### 1. **Manual Mode (via Mobile App)**
- Mobile app publishes MQTT messages to a **local broker**.
- ESP32 subscribes to the topic and forwards data via **SPI** to STM32.
- STM32 sends commands to the car via Bluetooth.
- <p align="center">
  <img src="https://github.com/user-attachments/assets/a40b5028-f00f-4b67-bb2b-8d2f9a78251d" width="60%" hight="50%" />
</p>

### 2. **Autonomous Stop (via AI Model)**
- AI model (runs on PC) detects **traffic light color**.
- Communicates with STM32 via **USB**.
- If RED is detected:
  - STM32 halts the car via Bluetooth.
- If NOT red:
  - STM32 continues relaying control signals from the mobile app.

---

## 🔁 FOTA (Firmware Over-The-Air)

Implemented on **STM32F401** with a custom **bootloader**:

- New firmware uploaded using:
  - Web App → MQTT → ESP8266 → STM32 (UART)
- Firmware files stored on **Firebase**
- STM32 bootloader supports:
  - ✅ Sector Erase
  - ✅ Mass Erase
  - ✅ Flash Download from Firebase
  - ✅ Jump to Application/Bootloader
  - - <p align="center">
  <img src="https://github.com/user-attachments/assets/bbcdc9dc-1cb7-4a7b-b847-e64f47bec031" width="60%" />
</p>

---

## ⚙️ Software Architecture

- **STM32** runs on **FreeRTOS**:
  - Tasks, queues, semaphores for real-time operations.
- **ESP32/ESP8266** written in **Arduino IDE**
- **Mobile App** uses MQTT to communicate with ESP32
- **Local MQTT Broker** built using **Mosquitto**
- **Node-RED** used for visual server control and OTA triggers

---

## 🧰 Technologies & Tools Used

| Category           | Tools/Hardware                                              |
|--------------------|-------------------------------------------------------------|
| Microcontrollers   | STM32F401RCT6, Arduino Uno                                  |
| Communication      | ESP32, ESP8266, 2x HC-05 Bluetooth Modules                  |
| Sensors & Motors   | 4 DC Motors, Motor Driver, Ultrasonic Sensor                |
| AI Model           | PC-based model (Traffic Light Detection) via USB            |
| OTA Tools          | Firebase, Node-RED, MQTT                                    |
| Protocols          | SPI, UART, USB (UART-over-USB), MQTT                        |
| Mobile App         | MQTT-based mobile app, connected to local broker            |
| Broker             | Local MQTT Broker using Mosquitto                           |

### 👨‍💻 Development Tools
- **STM32CubeIDE**
- **STM32CubeMX**
- **Keil MDK**
- **Arduino IDE**
- **Visual Studio Code**
- **Node-RED**
- **MQTTX**
- **Mosquitto MQTT Broker**

---

## 🔐 Features

- Real-time car control via mobile app  
- Local MQTT server for secure communication  
- AI-powered red light detection and emergency stop  
- Wireless bug fixes via FOTA  
- Real-time task management using FreeRTOS  

---

## 🚀 Future Enhancements

- Deploy AI model to an onboard system (e.g. Raspberry Pi)
- Add live video streaming in app
- GPS integration for location tracking
- Advanced traffic sign recognition (stop, yield, turn)

---

## 👥 Team Members

| Name              | Email                       |
|-------------------|-----------------------------|
| Mohamed Mokhtar   | mohamedmokhrat1@gmail.com   |
| Mohamed Haney     | hemdanmohamedhany@gmail.com |  
| Mohamed Galal     | mohamed.gallall12@gmail.com |       
| Omar Waled        | mohamed.gallall12@gmail.com |       
| Alaa Ahmed        | o2003wo@gmail.com           |
| Verena Ashraf     | alaa.ahmed.abbass@gmail.com |

---
