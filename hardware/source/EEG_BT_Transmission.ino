#include <ADS1299ESP32.h>
#include "Wire.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

long channelData [8];
ADS1299ESP32 ADS;
  //SCLK = 14, MISO = 12, MOSI = 13, SS = 15, RESET = 32 , DRDY = 33
#define MICROVOLTS_PER_COUNT (0.02235174f) 
const int MPU_ADDR = 0x68; 
int16_t a_x, a_y, a_z;


void setup() {
  // don't put anything before the initialization routine for recommended POR  
   ADS.initialize(); // (DRDY pin, RST pin, CS pin, SCK frequency in MHz);

  Serial.begin(115200);
  //Serial.println("Opening Serial Connection on COM4");
  SerialBT.begin("ESP32"); //Bluetooth device name
  SerialBT.println("Opening Serial Bluetooth Connection on COM5");             
  i2cinit();
  delay(1000); 
  
  ADS.disp = false;      // when verbose is true, there will be Serial feedback 
  ADS.reset();             // all registers set to default
  ADS.sdatac();            // stop Read Data Continuous mode to communicate with ADS
  delay(1);
  //Enabling BIAS measurement buffer for channel 1
 //enabling BIAS signal 
  ADS.wreg(CH1SET,0x68);  //0110 1000  PGA=24 for low noise PGA must be high and SPS should be low 
  ADS.wreg(CH2SET,0x68);  //0110 1000  PGA=24 for low noise PGA must be high and SPS should be low 
  ADS.wreg(CH3SET,0x68);  //0110 1000  PGA=24 for low noise PGA must be high and SPS should be low 
  ADS.wreg(CH4SET,0x68);  //0110 1000  PGA=24 for low noise PGA must be high and SPS should be low 
  ADS.wreg(CH5SET,0x68);  //0110 1000  PGA=24 for low noise PGA must be high and SPS should be low 
  ADS.wreg(CH6SET,0x68);  //0110 1000  PGA=24 for low noise PGA must be high and SPS should be low 
  ADS.wreg(CH7SET,0x68);  //0110 1000  PGA=24 for low noise PGA must be high and SPS should be low 
  ADS.wreg(CH8SET,0x68);  //0110 1000  PGA=24 for low noise PGA must be high and SPS should be low 

  ADS.wreg(BIAS_SENSP,0xFF);
  ADS.wreg(BIAS_SENSN,0xFF);
  ADS.wreg(CONFIG3,0xEC);  //1110 0000    Open BCI 0b1110 1100
  delay(1);
  delay(500);


 


  //Reading all registers  
  ADS.rregs(ID,CONFIG4);         // read out what we just did to verify the write
  ADS.rdatac();                      // enter Read Data Continuous mode
  ADS.start();
  delay(30);
} // end of setup
 
void loop(){

  while(digitalRead(ADS.DRDY)){}
   ADS.updatedata();
   accel();
 
   
   //Pattern is ch1,ch2,ch3,ch4,ch5,ch6,ch7-a1,a2,a3.
   for(int i = 0; i<8; i++){
    SerialBT.print(abs((int)(500000+  ADS.channelData[i])));
    SerialBT.print(',');
   } 
   SerialBT.print(a_x+15000);
   SerialBT.print(',');
   SerialBT.print(a_y+15000);
   SerialBT.print(',');
   SerialBT.print(a_z+15000);
   SerialBT.print('.');
   delay(5);
   
}

void i2cinit(void)
{
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); 
  Wire.write(0x6B); //PWR_MGMT_1 register
  Wire.write(0); // wakes up the MPU-6050
  Wire.endTransmission(true);
}
void accel(void)
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 6, true); // request a total of 7*2=14 registers
  
  a_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  a_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  a_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)

  
}
