# Temperature Measuring for Arduino
Standalone temperature logger, saving measured data onto SD card in CSV format. Creates one CSV file for each month.
Will also work with DHT22, see setup function.

## Hardware
- Arduino Uno
- SD shield (with compatible SD card and RTC (real time clock))
- DHT11 sensor on PIN 5

## Dependencies
- SD by Arduino
- RTCLib by Adafruit
- DHTNEW by Rob Tilaart
