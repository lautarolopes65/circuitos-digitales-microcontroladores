# Circuitos Digitales y Microcontroladores

Proyectos desarrollados usando **AVR-GCC** con firmware bare-metal y **Proteus** para la simulación de los circuitos electrónicos.

## Proyectos

### TP1 — Leds y Superloop No bloqueante

Sistema de visualización basado en **multitarea cooperativa** mediante un superbucle no bloqueante.

El sistema controla:

* 8 LEDs conectados a PORTD.
* 2 pulsadores.
* 8-LED WS2812/NeoPixel.
* Dos secuencias LED independientes.
* Dos secuencias NeoPixel independientes.

---

### TP2 — Controlador de Microondas

Controlador de firmware para un horno microondas doméstico utilizando una **máquina de estados finitos (FSM) periódica** controlada por una **interrupción de timer**.

El sistema incluye:

* 16x2 LCD display.
* 4x4 matrix keypad.
* Luz interna indicadora.
* Alarma end-of-process.
* Cooking timer.
* Funciones start, stop, clear, pause y quick-start.
* Simulación de apertura/cierre de puerta.

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
