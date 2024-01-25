
#include <Adafruit_I2CDevice.h>

#define I2C_ADDRESS 0x68
Adafruit_I2CDevice i2c_dev = Adafruit_I2CDevice(I2C_ADDRESS);


uint8_t buffer[32];

void setup()
{
  Serial.begin(9600);
  Serial.println("I2C address detection test");
  if (!i2c_dev.begin()) {
    Serial.print("Did not find device at 0x");
    Serial.println(i2c_dev.address(), HEX);
    while (1);
  }
  Serial.print("Device found on address 0x");
  Serial.println(i2c_dev.address(), HEX);
  // Try to read 32 bytes
  // Config PCF8574
  buffer[0]=0b11111111;               // config all pins to output
  i2c_dev.write(buffer,1);   // send the config to PCF8574

}

void loop()
{
  i2c_dev.read(buffer, 1);
  Serial.println(buffer[0],DEC);
  delay(1000);
}