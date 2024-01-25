#include <Adafruit_I2CDevice.h>

#define PCF8574_Address 0x20

Adafruit_I2CDevice i2c_dev = Adafruit_I2CDevice(PCF8574_Address);
uint8_t buffer[32];

void setup() {

  Serial.begin(9600);
  Serial.println("I2C address detection test");
  if (!i2c_dev.begin()) {
    Serial.print("Did not find device at 0x");
    Serial.println(i2c_dev.address(), HEX);
    while (1);
  }
  Serial.print("Device found on address 0x");
  Serial.println(i2c_dev.address(), HEX);

  // Config PCF8574
  buffer[0]=0b00000001;               // config all pins to output
  i2c_dev.write(buffer,1);   // send the config to PCF8574

}
void loop() {
  // buffer[0]=0b10000000;   // set bit 7 to high
  // i2c_dev.write(buffer,1);  // turn off LED
  // delay(1000);

  // buffer[0]=0b00000000;   // set bit 7 to low
  // i2c_dev.write(buffer,1);  // turn on LED
  // delay(1000);
  i2c_dev.read(buffer, 1);
  if((buffer[0] & 0b00000001) == 0b00000001){
    buffer[0] = 0b10000001;
    i2c_dev.write(buffer, 1);
  }else{
    buffer[0] = 0b00000001;
    i2c_dev.write(buffer, 1);
    Serial.println("LOW");
  }

}