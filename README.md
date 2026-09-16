# Circuitos Digitales y Microcontroladores

Collection of four practical assignments developed for the **Circuitos Digitales y Microcontroladores** course as part of the **Computer Engineering** degree at the **Universidad Nacional de La Plata (UNLP)**.

The projects were developed using **AVR-GCC** with bare-metal programming and **Proteus** for electronic circuit simulation.

## Projects

### TP1 — Non-Blocking Super Loop

Development of a visualization system based on **cooperative multitasking** using a non-blocking super loop.

The system controls:

* 8 LEDs connected to PORTD.
* Two user push buttons.
* An 8-LED WS2812/NeoPixel strip connected to PORTB0.
* Two independent LED sequences.
* Two independent NeoPixel sequences.

The implementation does **not use interrupts or timer peripherals**. Timing is managed through non-blocking software techniques.

**Main concepts:**

* AVR bare-metal programming
* GPIO
* Cooperative multitasking
* Non-blocking super loop
* Push buttons
* LED control
* WS2812 / NeoPixel communication

---

### TP2 — Microwave Oven Controller

Development of a firmware controller for a domestic microwave oven using a **periodic finite state machine (FSM)** driven by a **timer interrupt**.

The system includes:

* 16x2 LCD display.
* 4x4 matrix keypad.
* Magnetron indicator.
* Interior light indicator.
* End-of-process alarm.
* Cooking timer.
* Start, stop, clear, pause and quick-start functions.
* Door open/close simulation.

The firmware was implemented using a periodic state machine and timer interrupts.

**Main concepts:**

* Finite State Machines (FSM)
* Timer interrupts
* Matrix keypad
* LCD interface
* GPIO
* Timing and state management
* Bare-metal AVR programming

---

### TP3 — Greenhouse Monitor

Implementation of a greenhouse monitoring system using an **RTC**, a **DHT11 temperature and humidity sensor**, and a **UART serial interface**.

The system periodically reports the environmental conditions and determines whether the measured values are within the appropriate ranges depending on the time of day.

The system includes:

* RTC connected through I2C.
* DHT11 temperature and humidity sensor.
* UART communication at 9600 baud, 8N1.
* Periodic telemetry reports.
* Serial commands to configure the RTC and sampling interval.
* Alarm messages when environmental conditions are outside the defined ranges.
* UART reception and transmission interrupts.
* Timer interrupts.

**Main concepts:**

* I2C
* UART
* Interrupt-driven communication
* Timer interrupts
* RTC
* DHT11
* Sensor monitoring
* Serial commands
* Telemetry

---

### TP4 — RGB LED and Ambient Light Control

Development of a system for controlling the **intensity and color of an RGB LED** according to user commands and ambient light measurements.

The system includes:

* RGB LED with common anode configuration.
* LDR sensor connected to the ADC.
* UART serial interface.
* Three PWM signals.
* Hardware PWM using TIMER1.
* Software PWM for the red channel.
* Serial command for selecting the RGB color.
* Ambient light measurement to control the blinking period.
* Fade-in and fade-out effect.

The blinking period is dynamically adjusted according to the ambient light level.

**Main concepts:**

* ADC
* LDR
* PWM
* TIMER1
* Software PWM
* RGB LED control
* UART
* Serial commands
* Analog sensor reading

---

## Technologies and Tools

* **AVR-GCC**
* **C**
* **Proteus**
* **Bare-metal programming**
* **AVR microcontrollers**
* **UART**
* **I2C**
* **ADC**
* **PWM**
* **Timers**
* **Interrupts**
* **Finite State Machines**
* **GPIO**

## Academic Context

**Degree:** Computer Engineering
**University:** Universidad Nacional de La Plata (UNLP)
**Course:** Circuitos Digitales y Microcontroladores
**Year:** 2026

## Repository Structure

```text
circuitos-digitales-microcontroladores/
│
├── TP1/
│   ├── Proteus/
│   └── Firmware/
│
├── TP2/
│   ├── Proteus/
│   └── Firmware/
│
├── TP3/
│   ├── Proteus/
│   └── Firmware/
│
├── TP4/
│   ├── Proteus/
│   └── Firmware/
│
└── README.md
```

## Objective

The objective of these projects is to apply and integrate concepts related to **microcontroller programming, digital interfaces, timing, interrupts, communication protocols, sensors and actuators**, using bare-metal AVR-GCC development and Proteus simulation.
