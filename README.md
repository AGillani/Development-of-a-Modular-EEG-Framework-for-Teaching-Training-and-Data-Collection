# Development-of-a-Modular-EEG-Framework-for-Teaching-Training-and-Data-Collection
Source code for FYP project titled: Development of a Modular EEG Framework for Teaching, Training and Data Collection

This code has 2 major parts:

**-Hardware:**
This is code for Expressive ESP-32 module. The code is responsible for initializing the registers of the ADS1299 used in the sEEGs board
In order to run this code:
  -Download the Arduino IDE: https://www.arduino.cc/en/software
  -Download the libraries for ESP-32 (instructions available at https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
  -Upload the code on to the ESP-32 module
  
**-GUI**
This is the C++ code for real time multi-threaded data reading via bluetooth, data processing (filtering for noise removal, alpha waves segmentation and FFT), real-time data visualisation of 8 channel EEG and 3 channel accelerometer data and data storage.
In order to run this code:
  -Download Visual Studio 2019 (https://visualstudio.microsoft.com/downloads/)
  -Configure Dear ImGUI. This can be done conveniently by running the GUI.sln file which will automatically download and cofigure the library.
  -run main.cpp
