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

---

# **HTTPS Guide — Secure Your Local Dashboard**

To run the backend server and dashboard over HTTPS (recommended for modern browsers and security):

## 1. **Install Chocolatey & mkcert**

- Open Command Prompt as Administrator.
- Run:
  ```sh
  @"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"
  ```
- After Chocolatey installs, run:
  ```sh
  choco install mkcert
  mkcert -install
  ```
- Go to your server folder:
  ```sh
  cd C:\server-backend\SHT4x_ESP32
  ```
- Create certificates for localhost and your static IP:
  ```sh
  mkcert localhost 192.168.1.25
  ```
  *(Replace `192.168.1.25` with your static IP if different.)*

## 2. **Update `server.js` for HTTPS**

- Replace existing code with HTTPS setup:
  ```js
  const express = require('express');
  const https = require('https');
  const fs = require('fs');
  const sqlite3 = require('sqlite3').verbose();
  const cors = require('cors');
  const path = require('path');
  const app = express();
  const PORT = 5000;
  // Middleware
  app.use(cors());
  app.use(express.json());
  app.use(express.static(path.join(__dirname, 'public')));
  // SSL/TLS Configuration
  const sslOptions = {
    key: fs.readFileSync('localhost+1-key.pem'),
    cert: fs.readFileSync('localhost+1.pem')
  };
  // ...rest of the code...
  // Start HTTPS Server
  https.createServer(sslOptions, app).listen(PORT, '192.168.1.25', () => {
    console.log(`Server running on https://192.168.1.25:${PORT}`);
  });
  ```
- Make sure you use the correct certificate/key file names as generated by `mkcert`.

## 3. **Update Firewall & Port Scope**

- Open Windows Firewall → Inbound Rules.
- Find "Node.js Server port 5000" → Properties → Scope.
- Set "Remote IP address" range: `192.168.1.1` to `192.168.1.254` (or your LAN range).

## 4. **Kill Previous Server & Restart**

- Open Command Prompt as admin.
- Check for processes using port 5000:
  ```sh
  netstat -ano | findstr :5000
  ```
- Kill conflicting process:
  ```sh
  taskkill /PID <PID> /F
  ```
  *(Replace `<PID>` with the actual Process ID.)*

## 5. **Update URLs in Client Code**

- **index.html**:  
  Update historic data fetch URLs to use HTTPS and port 5001 (if changed).
  ```js
  const url = `https://192.168.1.25:5001/api/sensor-data?sensorId=sensor${sensorId}&startDate=${startDate}&endDate=${endDate}`;
  ```
- **ESP32 firmware**:  
  Update backend data POST URL.
  ```cpp
  String url = "http://192.168.1.25:5001/api/sensor-data";
  ```
  *(Note: ESP32 Arduino core only supports HTTP by default. For HTTPS, you may need to install additional libraries for secure client connections.)*

## 6. **Run Secure Server**

- In VSCode terminal (in your project folder):
  ```sh
  node server.js
  ```

- Your dashboard will now be available at:  
  `https://<Your-localhost-IP>:<your-port>/`  
  (e.g. `https://192.168.1.25:5000/`)

- You can download historic data via the web dashboard.

---

*Enjoy your secure, multi-sensor ESP32 dashboard!*
