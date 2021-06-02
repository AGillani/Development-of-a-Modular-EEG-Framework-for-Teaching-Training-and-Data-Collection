This is the code that is intended to be uploaded to the ESP32 module. The libraries include the code we have written for configuring the AD1299 using the ESP-32. 
The source code is used to set the parameters for the ADS1299, initialize the ADS1299 and initialize bluetooth and accelerometer.
This will collect 8 channel data as well as 3 channel accelerometer data. 
This data is transmitted via bluetooth to the PC.
The pattern of the data transmitted is ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8-ax,ay,az.
