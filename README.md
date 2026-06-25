# Digital Scale (Cân Điện Tử) using ESP32

A smart, high-precision electronic scale built using an ESP32 microcontroller, an HX711 24-bit ADC, and four 50kg load cells configured in a complete Wheatstone bridge. 

This project was developed as part of an academic study in Measurement Engineering (**Cơ sở Kỹ thuật Đo lường**) at Hanoi University of Science and Technology (HUST). It not only functions as a practical human scale but is also designed to facilitate the collection of raw data for statistical error, linearity, and hysteresis analysis.

## ✨ Features
* **Full Wheatstone Bridge:** Combines four 3-wire (half-bridge) load cells to sum dynamic loads accurately, even on uneven surfaces.
* **Auto-Tare on Startup:** Automatically calculates and subtracts the "dead load" (the weight of the wooden platform) to zero the scale.
* **Zero-Snapping:** Software algorithm to hide microscopic thermal drift and sensor noise when the scale is empty, keeping the LCD UI perfectly stable.
* **Flicker-Free LCD Display:** Smooth, real-time weight updates on a 16x2 I2C LCD.
* **Data Logging Mode:** Streams 10-sample averages via Serial over USB only when a load is applied, making it easy to copy/paste data into Excel for statistical analysis.

## 🛠️ Hardware Components
* **Microcontroller:** ESP32 Development Board
* **ADC / Amplifier:** HX711 Module
* **Sensors:** 4x 50kg Load Cells (3-wire half-bridge)
* **Display:** 16x2 LCD with I2C Backpack (Address: `0x27`)
* **Platform:** Custom wooden board with 3D-printed load cell mounts

## 🔌 Wiring & Assembly

### 1. Load Cell Configuration (The Outer Loop)
Unlike standard tutorials, the true electrical center of these specific load cells is the **Yellow** wire.
* Solder the **Red** and **Black** wires in an alternating continuous square (Red-to-Red, Black-to-Black) to form the outer excitation loop.
* The 4 **Yellow** wires act as the signal/excitation nodes and route directly to the HX711:
  * Top-Left Yellow -> `E+`
  * Bottom-Right Yellow -> `E-`
  * Top-Right Yellow -> `A+`
  * Bottom-Left Yellow -> `A-`

### 2. Microcontroller Connections
| Component | Pin | ESP32 Pin |
| :--- | :--- | :--- |
| **HX711** | VCC | 3.3V |
| | GND | GND |
| | DT (Data) | GPIO 16 |
| | SCK (Clock)| GPIO 17 |
| **I2C LCD** | VCC | 5V / VIN *(Required for backlight)* |
| | GND | GND |
| | SDA | GPIO 21 |
| | SCL | GPIO 22 |

> **Note:** Ensure the backlight jumper on the I2C backpack is installed, and tune the blue contrast potentiometer if the screen appears blank!

## 🚀 Software & Setup
This project is written in C++ using the Arduino framework (PlatformIO/Arduino IDE).

### Dependencies
You will need to install the following libraries:
* `HX711` by Bogdan Necula
* `LiquidCrystal I2C` by Frank de Brabander

### Calibration
Load cells are heavily affected by mechanical leverage and the physical flex of the scale's platform. The default `CALIBRATION_FACTOR` in `main.cpp` is set to `13800.0`. 
To recalibrate for your specific hardware:
1. Place a known, heavy weight (or a human of known weight) on the scale.
2. Note the raw ADC reading.
3. Divide the raw reading by the known weight in kg to get your new custom calibration factor.

## 📊 Error Analysis & Measurement Science
The serial output is optimized for gathering data for the project report. By capturing the data during ascending and descending load tests, you can import the serial data directly into Excel to calculate:
* **Absolute & Percentage Error:** Comparing the scale's output against standardized weights.
* **Mechanical Hysteresis:** Analyzing the difference in output when weights are loaded vs. unloaded to detect physical binding in the scale structure.

## 👥 Contributors
* Lê Ngọc Tuân
* Đinh Gia Khánh
* Cao Anh Minh Huy
* Nguyễn Trọng Ninh
* Vũ Tiến Dương
