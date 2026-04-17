# 4x4x4 Volumetric LED Cube (ESP32)

A 3D LED visualization project that uses an ESP32 (ESP-WROOM-32) to control 64 blue LEDs through high-frequency multiplexing. This project demonstrates the principles of Persistence of Vision (POV), transistor switching, and spatial 3D animation.

## 🚀 The Core Idea
The goal of this project is to create a "volumetric display"—a screen where pixels (voxels) exist in three-dimensional space. By arranging 64 LEDs in a 4x4x4 grid, we can render shapes, moving planes, and complex animations that move through X, Y, and Z axes.

### The Problem
Controlling 64 LEDs individually would require 64 GPIO pins, which exceeds the capacity of the ESP32 (and most microcontrollers). Additionally, driving 64 LEDs simultaneously would draw more current than the board can safely provide.

### The Solution: Multiplexing & POV
This project uses **Multiplexing** to solve the pin limitation:
- **Structure:** The cube is wired into 16 vertical columns (Anodes) and 4 horizontal layers (Cathodes). 
- **Efficiency:** Instead of 64 pins, we only use **20 pins** (16 for columns + 4 for layers).
- **Logic:** The ESP32 turns on one layer at a time, sets the LED pattern for that layer, and then moves to the next. By cycling through all 4 layers faster than 60Hz, the human eye perceives a single, flicker-free 3D image due to **Persistence of Vision (POV)**.

---

## 🛠️ Hardware Requirements
- **Microcontroller:** ESP32 Dev Board (30 or 38 pin)
- **LEDs:** 64 × 5mm Blue LEDs
- **Switching:** 4 × BC547 NPN Transistors (for layer grounding)
- **Resistors:** - 16 × 220Ω (Current limiting for columns)
  - 4 × 1kΩ (Base resistors for transistors)
- **Build Surface:** Perfboard (Zero PCB)
- **Power:** 5V via Micro-USB (ESP32 regulates to 3.3V)

---

## 🏗️ Connection Map

### Columns (Anodes) - Active HIGH
Controlled via 220Ω resistors to limit current from ESP32 GPIOs.

| Column | GPIO | Column | GPIO |
| :--- | :--- | :--- | :--- |
| C1 | D2 | C9 | D13 |
| C2 | D4 | C10 | D12 |
| C3 | D5 | C11 | D14 |
| C4 | D18 | C12 | D27 |
| C5 | D19 | C13 | D26 |
| C6 | D21 | C14 | D25 |
| C7 | D22 | C15 | D33 |
| C8 | D23 | C16 | D32 |

### Layers (Cathodes) - Active HIGH (via Transistor)
Each GPIO triggers a BC547 transistor to connect the entire layer to GND.

| Layer | GPIO | Function |
| :--- | :--- | :--- |
| Layer 1 | D15 | Bottom Layer |
| Layer 2 | GPIO16 | Layer 2 |
| Layer 3 | GPIO17 | Layer 3 |
| Layer 4 | GPIO1 | Top Layer (TX0) |

---

## 💻 Software Logic
The firmware follows a continuous refresh loop:
1. **Clear:** Turn OFF all layers.
2. **Select:** Set the 16 column pins to HIGH or LOW based on the desired pattern for the current layer.
3. **Activate:** Turn ON the transistor for the specific layer.
4. **Hold:** Delay for 1–3ms.
5. **Repeat:** Move to the next layer.

### Features Implemented:
- **Voxel Control:** Address any specific LED using (x, y, z) coordinates.
- **Layer Scanning:** Smooth transitions between horizontal planes.
- **Plane Movement:** Vertical and horizontal "sheets" of light moving through the cube.
- **3D Animations:** Pre-programmed sequences including "Rain," "Spinning I," and "Expanding Box."

---

## ⚙️ Setup & Installation

1. **Hardware Assembly:**
   - Use a wooden jig (holes drilled 2cm apart) to align LEDs during soldering.
   - Solder all 16 anodes in a column together.
   - Solder all 16 cathodes in a layer together.
   - Ensure all Transistor Emitters are connected to a **Common Ground** with the ESP32.

2. **Software Setup:**
   - Install [Arduino IDE](https://www.arduino.cc/en/software).
   - Add ESP32 Board Support: `File > Preferences > Additional Boards Manager URLs` -> `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`.
   - Select your board: `Tools > Board > ESP32 Dev Module`.

3. **Flashing:**
   - Clone this repository.
   - Open `.ino` file in Arduino IDE.
   - Connect ESP32 via USB and click **Upload**.

---

## ⚠️ Lessons Learned & Troubleshooting
- **Ghosting:** If LEDs appear dimly lit when they should be off, ensure the `delay` between layer switching is optimized (1ms is usually ideal) and that all layers are pulled LOW before switching the next one HIGH.
- **Transistor Switching:** BC547 NPN transistors are essential because the ESP32 cannot sink the combined current of 16 LEDs on a single GPIO.
- **Alignment:** Using a template/jig is critical for a professional-looking cube.

## 🔮 Future Improvements
- [ ] Integration with **Web Server (WiFi)** to control animations via smartphone.
- [ ] Music visualization using an I2S Microphone.
- [ ] Scaling to an 8x8x8 structure using Shift Registers (74HC595).

---
**Author:** Kohinoor N. Kale  
**GitHub:** [kohinoorkale](https://github.com/kohinoorkale)
