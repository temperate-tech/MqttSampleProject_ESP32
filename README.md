# MqttSampleProject_ESP32
A sample project to publish data onto an mqtt host to get familiarised with the environment

# ESP32 Multi-SHT4x Sensor MQTT Dashboard

This project enables the ESP32 to read from up to four Adafruit SHT4x temperature/humidity sensors, push real-time data to MQTT and a local backend server, and visualize sensor readings on a web dashboard with historic data download support.

---

## Hardware Requirements

- **ESP32 Dev Module:** Any standard ESP32 development board.
- **Adafruit SHT4x Sensors:** Up to 4 SHT4x sensors (humidity/temperature).
- **I2C Bus Multiplexer:** Required for connecting multiple sensors to ESP32 (e.g. PCA9546).
- **Jumper wires, breadboard, 3.3V power** (as required for your setup).

---

## Software Requirements

### 1. **Arduino IDE Setup**

- **Install Arduino IDE:** Download from [arduino.cc](https://www.arduino.cc/en/software).
- **Install Board Support:**
  - Go to `Tools > Board > Boards Manager` and install "esp32" by Espressif.
- **Required Libraries:**
  - Open `Tools > Manage Libraries` and install:
    - **Adafruit SHT4x** (`Adafruit_SHT4x`)
    - **WiFi**
    - **PubSubClient**
    - **HTTPClient**
    - **ArduinoOTA**
- **OTA (Over-The-Air) Update:**
  - Configure ArduinoOTA for wireless firmware updates.
  - Set hostname and password in code for security.

### 2. **Node.js Backend Setup**

#### a. **Install Node.js (LTS)**
- Download and install from [nodejs.org](https://nodejs.org/).

#### b. **Clone This Repository**
- Create a directory (e.g., `C:\server-backend\SHT4x_ESP32`)
- Clone the repo inside this folder.

#### c. **Setup Project Structure**
- In `SHT4x_ESP32`, create a subfolder named `public`.
- Place your `index.html` dashboard file inside `public`.

#### d. **Install Dependencies**
- Open VSCode in `SHT4x_ESP32`.
- Open a terminal and run:
  ```sh
  npm init -y
  npm install express sqlite3 cors
  ```

#### e. **Create and Run the Server**
- Save the provided backend code (see below) as `server.js` in `SHT4x_ESP32`.
- Start the server:
  ```sh
  node server.js
  ```
- The dashboard will be available at:  
  `http://<Your-localhost-IP>:<PORT>/`  
  (Default: `http://192.168.1.25:5000/`)

---

## Network Configuration for Local Server

1. **Set Static IP for Host Machine:**
   - Open Control Panel → Network and Internet → Network and Sharing Center.
   - Click "Change adapter settings" (left panel).
   - Right-click your Wi-Fi adapter → Properties.
   - Select "Internet Protocol Version 4 (TCP/IPv4)" → Properties.
   - Check "Use the following IP address".
   - Enter desired static IP, subnet mask, and default gateway:
     - **How to find your router's IP and subnet mask:**
       - Open Command Prompt, type `ipconfig`, note "Default Gateway" and "Subnet Mask".
     - **How to get DNS info:**
       - Also in `ipconfig` output, note "DNS Servers".
   - Click OK, wait for reconnection.
   - Verify your IP has changed with `ipconfig`.

2. **Update IP Address in Code:**
   - Replace any instance of the local IP in your Arduino sketch, index.html, and server.js with your new static IP.

3. **Configure Windows Firewall:**
   - Open "Windows Defender Firewall with Advanced Security" from Start menu.
   - Go to "Inbound Rules" → "New Rule".
   - Select "Port" → TCP → Specific local port (e.g., 5000).
   - Allow the connection.
   - Check all profiles (Domain, Private, Public).
   - Name the rule (e.g., "Node.js Server port 5000"), add description if needed.
   - Finish.

---

## ESP32 Firmware Upload

- Connect your ESP32 to PC via USB.
- Select correct COM port and board in Arduino IDE.
- Upload the code.
- If using OTA, subsequent uploads can be done wirelessly.

---

## Commit Changes

- If you modified `index.html`, commit the changes via Git:
  ```sh
  git add public/index.html
  git commit -m "Update dashboard UI"
  git push
  ```

---

## API Usage & Testing

### 1. **Sensor Data Push**

- ESP32 firmware POSTs sensor data to your backend at:
  ```
  http://<your-static-IP>:5000/api/sensor-data
  ```
- Each record includes: `sensorId`, `temperature`, `humidity`, `timestamp`.

### 2. **API Testing with Postman**

- **Install Postman:** [Download here](https://www.postman.com/downloads/)
- **Test POST Endpoint:**
  - Set method to POST.
  - URL: `http://<your-static-IP>:5000/api/sensor-data`
  - Select "Body" → "raw" → "JSON".
  - Example payload:
    ```json
    {
      "sensorId": "sensor1",
      "temperature": 25.3,
      "humidity": 70.1
    }
    ```
  - Click "Send". You should receive `{ message: "Data saved successfully" }`.

- **Test GET Endpoint (Historic Data):**
  - Set method to GET.
  - URL:  
    `http://<your-static-IP>:5000/api/sensor-data?sensorId=sensor1&startDate=2024-09-10T00:00:00&endDate=2024-09-10T23:59:59`
  - Click "Send". You should see a list of records.

---

## Dashboard Features

- Displays live readings for 4 sensors (temp & humidity).
- Interactive graphs (live/historic) using Chart.js.
- Download historic data as CSV for custom date/time range.
- Responsive, modern UI.

---

## Troubleshooting

- Ensure all IP addresses in code and dashboard match your static local IP.
- Confirm Node.js server is running (`node server.js`).
- Check firewall rules for required ports.
- Use `ipconfig` to verify network settings.
- MQTT broker should be accessible from both ESP32 and dashboard.

---

## Useful Links

- [ESP32 Board Support](https://github.com/espressif/arduino-esp32)
- [Adafruit SHT4x Library](https://github.com/adafruit/Adafruit_SHT4x)
- [HiveMQ Public MQTT Broker](https://www.hivemq.com/public-mqtt-broker/)
- [Node.js](https://nodejs.org/)
- [Postman](https://www.postman.com/)

---

## License

MIT

---

## Credits

Developed by [temperate-tech](https://github.com/temperate-tech)

