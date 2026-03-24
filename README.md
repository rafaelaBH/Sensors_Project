# Multi-Threaded Sensor Monitoring System

## Description
This project is a C++ multi-threaded sensor monitoring system that reads and manages temperature and humidity sensors in real time. It features automatic detection and replacement of flawed sensors, noise reduction using a Kalman filter, and thread-safe data handling through mutexes and atomic variables.

## Features
- Base `Sensor` class with `TemperatureSensor` and `HumiditySensor` subclasses
- Multi-threaded design with per-sensor threads and a central controller
- Thread-safe data collection using mutexes and atomic flags
- Automatic detection and replacement of flawed sensors during runtime
- Kalman filter for reducing sensor noise and improving measurement accuracy
- Configurable thresholds for temperature and humidity
- Fully version-controlled using Git

## Build Instructions
This project uses CMake for building.
