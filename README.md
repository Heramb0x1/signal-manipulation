# 📡 NodeMCU Signal Generation using VL53L0X and WiFi

This project demonstrates **real-time signal generation** using the **VL53L0X Time-of-Flight distance sensor** connected to a **NodeMCU (ESP8266)**. The NodeMCU transmits measured distance data over **WiFi** to a Python server via TCP/IP sockets.

> 🔧 Ideal for gesture-based controls, proximity automation, and IoT sensor networks.

---

## 🚀 Features

- ⚡ Real-time distance detection using VL53L0X
- 🌐 WiFi-based communication with a Python server
- 🧠 Custom I2C configuration using defined SDA/SCL pins
- 🕐 Signal sent every 1ms (1kHz loop frequency)
- 🔄 Easy integration into larger IoT networks

---

## 🔌 Hardware Requirements

| Component                 | Description                                |
|--------------------------|--------------------------------------------|
| NodeMCU ESP8266          | WiFi-enabled microcontroller               |
| VL53L0X ToF Sensor       | Measures distance using laser pulses       |
| Breadboard & Jumper Wires| For clean prototyping connections          |
| Power Supply             | 5V via USB or external source              |

---

## 🔧 Pin Configuration

| VL53L0X Pin | NodeMCU Pin |
|-------------|-------------|
| VIN         | 3V3         |
| GND         | GND         |
| SDA         | D2 (GPIO4)  |
| SCL         | D1 (GPIO5)  |

---

## 📦 Arduino Libraries Required

Ensure you have these installed via **Arduino Library Manager**:

- `Adafruit VL53L0X`
- `Wire.h`
- `ESP8266WiFi.h`

---

## 📡 WiFi Setup

Edit the following lines in the `.ino` file with your **WiFi credentials**:

```cpp
const char* ssid = "your-SSID";
const char* password = "your-password";
```

Also, configure the IP and port of your Python server:
```cpp
const char* host = "192.168.ABC.XYZ";  // Replace with your server's IP
const int port = 23456;                // Match this with your Python server
```

🐍 Python Server (Example)
Here’s a simple Python TCP server to receive distance data:

```python
import socket

HOST = '192.168.ABC.XYZ'  # Same IP as in your .ino file
PORT = 23456

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"Listening on {HOST}:{PORT}")
    conn, addr = s.accept()
    with conn:
        print(f"Connected by {addr}")
        while True:
            data = conn.recv(1024)
            if not data:
                break
            print("Received:", data.decode())
```
Make sure the server runs before the NodeMCU boots.


---



## My Other projects : 
> ml0 > ML Notebook > **[ml0.betterworkai.org](https://ml0.bettterworkai.org)** <br>
> My Quick-ship > **[heramb.dino.icu](https://heramb.dino.icu)**

