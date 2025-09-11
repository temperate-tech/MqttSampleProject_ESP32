# MqttSampleProject_ESP32
A sample project to publish data onto an mqtt host to get familiarised with the environment

# SHT4x ESP32 Multi-Sensor Dashboard & Data Logger

## Overview

This project enables you to monitor temperature and humidity from up to four SHT4x sensors using an ESP32 dev module. Sensor readings are published to MQTT topics and also sent to a local backend server, which stores data in a SQLite database and serves a web dashboard for live and historic visualization.

---

## Hardware Requirements

- **ESP32 Dev Module**
- **4 × SHT4x Sensors**
- **PCA9685/PCA9548A I2C Multiplexer** (for multiple SHT4x sensors)
- **WiFi Router** (for MQTT and backend communication)

---

## Software Requirements

- **Arduino IDE**
  - ESP32 board support (install via Boards Manager)
  - Required libraries:
    - [WiFi.h](https://github.com/espressif/arduino-esp32)
    - [PubSubClient](https://github.com/knolleary/pubsubclient)
    - [HTTPClient](https://github.com/espressif/arduino-esp32)
    - [ArduinoOTA](https://github.com/arduino-libraries/ArduinoOTA)
    - [Adafruit SHT4x](https://github.com/adafruit/Adafruit_SHT4x)
    - [Wire.h](https://github.com/espressif/arduino-esp32)
- **Node.js** (for backend server)
- **VSCode** or any code editor

---

## Setup Instructions

### 1. Arduino IDE & ESP32 Firmware

1. **Install Arduino IDE**  
   Download from [arduino.cc](https://www.arduino.cc/en/software).

2. **Install ESP32 Board Support**  
   - Open Arduino IDE → Preferences → Add URL:  
     `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
   - Tools → Board Manager → Install "esp32".

3. **Install Required Libraries**  
   - Arduino IDE → Tools → Manage Libraries → Search and install:
     - PubSubClient
     - Adafruit SHT4x
     - ArduinoOTA

4. **OTA Setup**  
   - Configure OTA updates in your code using `ArduinoOTA` library.
   - Set OTA hostname and password.

5. **Hardware Connections**
   - Connect SHT4x sensors to ESP32 via I2C multiplexer.
   - Double-check wiring and addresses.

6. **Configure WiFi & MQTT**
   - Set your WiFi SSID and password in the code.
   - Set MQTT broker (e.g., HiveMQ public broker).

7. **Data Publishing**
   - Sensor data is published to MQTT topics (e.g., `esp32/sensor1/temp`).
   - Data also sent via HTTP POST to local backend.

8. **Upload Code**
   - Select correct board and port in Arduino IDE.
   - Upload sketch to ESP32.

---

### 2. Backend Server (Node.js + SQLite)

1. **Clone Repository**
   ```sh
   mkdir server-backend
   cd server-backend
   mkdir SHT4x_ESP32
   cd SHT4x_ESP32
   git clone <this-repo-url> .
   ```

2. **Create Public Folder for Web Dashboard**
   ```sh
   mkdir public
   # Copy your index.html dashboard to 'public' folder
   cp path/to/index.html public/
   ```

3. **Setup Node.js Backend**
   - In `SHT4x_ESP32` folder:
     ```sh
     npm init -y
     npm install express sqlite3 cors
     ```
   - Save backend code as `server.js` in this folder.

4. **Run Backend**
   ```sh
   node server.js
   ```
   - Server will run on port 5000 (default).

---

### 3. Windows Network & Firewall Setup

1. **Assign Static IP**
   - Control Panel → Network and Internet → Network and Sharing Center
   - Change adapter settings → Wi-Fi Adapter → Properties → IPv4
   - Check "Use the following IP address"
     - Enter desired static IP, subnet mask, default gateway, DNS info.
     - Find subnet mask & gateway using `ipconfig` in CMD.
     - Get router IP for gateway by logging into router admin panel.
   - Click "OK" and reconnect WiFi.
   - Verify new IP using `ipconfig`.

2. **Update IP in Code**
   - Replace all occurrences of old IP address in Arduino code, `index.html`, and `server.js` with your new static IP.

3. **Configure Windows Firewall**
   - "Windows Defender Firewall with Advanced Security" → Inbound Rules → New Rule
   - Rule Type: Port → TCP, specific local port (e.g., 5000)
   - Allow connection → Check all profiles (Domain, Private, Public)
   - Name: "Node.js Server port 5000" (add description if needed)

---

### 4. Dashboard Usage

- **Access Dashboard:**  
  Open browser at:  
  `http://<Your-localhost-IP>:<Your-port>/`  
  Example: `http://192.168.1.25:5000/`

- **Features:**
  - Live temperature & humidity widgets for 4 sensors.
  - Interactive graphs (live & historic).
  - Date/time picker for historic data.
  - Download CSV of historic data by date/time range.
  - Responsive design for mobile/desktop.
  - Uses MQTT for real-time updates.

---

## How Data Flows

1. **ESP32 reads SHT4x sensors** (via I2C multiplexer, up to 4 sensors).
2. **Publishes data to MQTT broker** (`broker.hivemq.com`).
3. **Sends data via HTTP POST** to backend (`/api/sensor-data`).
4. **Backend saves data in SQLite database** (`sensor_data.db`).
5. **Dashboard fetches live data via MQTT** and historic data via HTTP GET from backend.
6. **Dashboard allows CSV download** for selected date/time ranges.

---

## Troubleshooting

- **ESP32 not connecting to WiFi:** Double-check SSID/password, router settings, and static IP configuration.
- **No dashboard data:** Check that Node.js server is running and firewall allows port 5000.
- **Historic data missing:** Ensure ESP32 is publishing HTTP POST data and SQLite database is writable.
- **OTA issues:** Make sure ESP32 and PC are on the same network; check OTA password.

---

## License

MIT License (or as specified in the repository).

## Author

[temperate-tech](https://github.com/temperate-tech)

---

## Quick Links

- [ESP32 documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/)
- [Adafruit SHT4x Library](https://github.com/adafruit/Adafruit_SHT4x)
- [Node.js Express](https://expressjs.com/)
- [Chart.js](https://www.chartjs.org/)
- [HiveMQ MQTT Broker](https://www.hivemq.com/public-mqtt-broker/)
