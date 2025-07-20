# STM32F0 ADC & UART Communication Project

This project is built for an STM32F0 microcontroller (Cortex-M0) and demonstrates the use of ADC inputs, UART communication, and GPIO interaction using the STM32 HAL library.

## 📋 Overview

The firmware reads analog signals from various channels (joystick, distance sensor, gripper, etc.) via the ADC and sends their processed values over UART. The project also interacts with push-buttons and implements simple UART acknowledgment mechanisms for reliable communication.

### ✅ Features

- ADC initialization and channel switching at runtime
- UART communication with ACK-based transmission protocol
- GPIO input reading (button press detection)
- Modular functions for:
  - Base movement control
  - Gripper position
  - Distance sensor
  - Arm height
  - Left and right wheels

---

## ⚙️ Requirements

- **MCU**: STM32F0 series (Cortex-M0)
- **Toolchain**: 
  - STM32CubeMX (for project generation)
  - STM32CubeIDE or compatible compiler (e.g., `arm-none-eabi-gcc`)
- **Peripherals Used**:
  - ADC (Channels 0, 1, 2, 3)
  - UART1 @ 9600 baud (with optional RS-485 support)
  - UART2 @ 38400 baud
  - GPIO (Button on PB5, LED on PA5)

---

## 📡 Communication Protocol

Each function transmits a single character (e.g., `B`, `G`, `L`, etc.) over UART to indicate the data source, waits for an ACK from the receiver, and then sends the converted ADC value.

| Code | Component        |
|------|------------------|
| `B`  | Base joystick Y  |
| `G`  | Gripper X        |
| `L`  | Distance sensor  |
| `A`  | Arm height       |
| `E`  | Left wheels      |
| `D`  | Right wheels     |

ACK values expected by the microcontroller:
- `'1'`, `'2'`, `'3'` ... depending on the function
- `'5'` for wheels

---

## 🧪 Usage

1. Flash the firmware to your STM32F0 device using STM32CubeIDE or an external flasher.
2. Connect appropriate analog devices to ADC channels.
3. Connect UART1 to a serial monitor or RS-485 master device.
4. Use UART2 for debugging or secondary communication.

---

## 📁 Project Structure

```
|── Inc/                    # Header files (main.h, etc.)
│── Src/                    # Source files (main.c, etc.)
├── Drivers/                # STM32 HAL and CMSIS drivers
├── README.md               # This file
└── .gitignore              # Recommended Git exclusions
```

---

## 🚀 Getting Started

To build and flash:

1. Clone the repository:
   ```bash
   git clone https://github.com/marceloholgado/ControleRobo.git
   cd ControleRobo
   ```

2. Open the project with **STM32CubeIDE** or build using Make/CMake with the appropriate toolchain.

---

## 🛠️ License

This project uses the **STMicroelectronics BSD-style license**, as inherited from CubeMX-generated files. See file headers for details.

---

## ✍️ Author

Developed by Marcelo Holgado.  
