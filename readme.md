# Hemodialysis Equipment Product Readme

This repository contains the code for a basic hemodialysis equipment system. It is developed as a task for a medical equipment subject.

## Overview

The code provided here facilitates the monitoring and control of hemodialysis equipment. It includes functionalities such as:

- Flow rate monitoring using a Hall-effect sensor.
- Detection of potential blood leakage using a color sensor.
- Providing warnings through a buzzer in case of blood leakage detection.

## Hardware Requirements
- Hall-effect sensor connected to digital pin 2 for flow rate monitoring.
- Color sensor with specific pins assigned for reading red, green, and blue pulse widths.
- Status LED connected to digital pin 13.
- Buzzer connected to digital pin 12.

## Functionality

### Flow Rate Monitoring

The code continuously monitors the flow rate of the hemodialysis equipment by counting pulses from the Hall-effect sensor. It calculates the flow rate in milliliters per minute based on the pulse count and a calibration factor.

### Blood Leakage Detection

Blood leakage detection is achieved using a color sensor. If the detected levels of red and green exceed a certain threshold, indicating the presence of blood, the buzzer is activated to alert the user.

## Setup

Ensure all hardware components are connected properly according to the pin configurations specified in the code. Upload the code to the microcontroller.

## Usage

Upon successful setup, the code will start monitoring the flow rate and detecting potential blood leakage. If blood leakage is detected, the buzzer will sound to alert the user.

## Note
- This is a basic implementation. For educational medical purposes only.

## Author
- Mohamed Hazem Yahya

Feel free to contribute or modify the code to suit your specific requirements and improve its functionality.
