# ELEX4618 Lab 3 - Serial Control

## Overview
PC-side C++ program that communicates with a Tiva C microcontroller using a simple serial protocol.
Supports analog reads, digital reads/writes, button debounce, and servo control.

## Features
- Auto-detect COM port + reconnect
- Analog joystick read (CH11, CH4)
- Digital read (SW1 CH33, active-low)
- Servo control (CH0-3)

## Build
- Visual Studio 2022
- Windows 10/11

## Run
1. Connect the microcontroller over USB
2. Launch the program
3. Choose an option from the menu

## Notes
- Buttons are active-low
- Channels based on lab handout
