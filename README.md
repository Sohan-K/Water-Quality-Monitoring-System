# Water Quality Monitoring System

This project is a water quality monitoring system that measures water temperature and Total Dissolved Solids (TDS) using an ESP32 microcontroller. The data is sent to a ThingSpeak server, where real-time graphs visualize the collected information.

## Features
- Measures water temperature and TDS levels.
- Uses ESP32 and sensors to collect data.
- Sends real-time data to ThingSpeak.
- Provides graphical visualization of water quality trends.

## Technologies Used
- **Hardware:** ESP32, Temperature Sensor, TDS Sensor.
- **Software:** Arduino IDE, ThingSpeak API.
- **Communication:** Wi-Fi (ESP32 to ThingSpeak).

## Installation & Setup
1. **Hardware Setup:**
   - Connect the TDS sensor and temperature sensor to the ESP32.
   - Ensure proper wiring and power connections.

2. **Software Setup:**
   - Install the **Arduino IDE** and required ESP32 board libraries.
   - Install additional libraries: `WiFi.h`, `HTTPClient.h`, and `ThingSpeak.h`.

3. **ThingSpeak Configuration:**
   - Create a ThingSpeak account.
   - Set up a new channel and obtain the API Key.

4. **Upload Code:**
   - Modify the `WIFI_SSID` and `WIFI_PASSWORD` in the code.
   - Add your ThingSpeak **API Key**.
   - Upload the sketch to ESP32 via Arduino IDE.

## Usage
- Once powered on, the ESP32 collects water quality data.
- Data is sent to ThingSpeak at regular intervals.
- View real-time updates on your ThingSpeak channel.

## Live Data
View real-time water quality data here: [ThingSpeak Channel](https://thingspeak.mathworks.com/channels/2479318)

## Future Enhancements
- Add pH sensor support.
- Implement alerts for poor water quality.
- Improve data analysis with machine learning.

## License
This project is licensed under the MIT License.

