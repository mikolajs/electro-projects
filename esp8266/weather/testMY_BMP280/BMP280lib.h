#include <AsyncDelay.h>    //not needed in this example code, but is required by SoftWire. 
#include <SoftWire.h>

#include <BMx280MI.h>

#define I2C_ADDRESS 0x76

//set your desired I2C Pins here
uint8_t sdaPin = 4;
uint8_t sclPin = 5;
SoftWire sw(sdaPin, sclPin);

//class derived from BMx280MI that implements communication via SoftWire. I used low level commands because high
//level commands showed unexpected behaviour (SoftWire V 2.0.0) 
class BMx280SoftWire : public BMx280MI
{
  public: 
    //constructor of the derived class. 
    //@param address i2c address of the sensor.
    BMx280SoftWire(uint8_t i2c_address):
    address_(i2c_address) //initialize the BMx280sw classes private member address_ to the i2c address provided
    {
      //nothing else to do here...
    }
  
  private:
    //this function must be implemented by derived classes. it is used to initialize the interface or check the sensor for example. 
    //@return true on success, false otherwise. 
    bool beginInterface()
    {
      return true;
    }

    //this function must be implemented by derived classes. this function is responsible for reading data from the sensor. 
    //@param reg register to read. 
    //@return read data (1 byte).
    uint8_t readRegister(uint8_t reg)
    {
      uint8_t data;

      sw.startWait(address_, SoftWire::writeMode);
      sw.llWrite(reg);

      sw.repeatedStart(address_, SoftWire::readMode);
      sw.readThenNack(data);  // Read 1 byte and then send ack
      sw.stop();

      return data;
    }
    
    //this function can be implemented by derived classes. implementing this function is optional, but readings may be incorrect if 
    //it is not (see BMP280 / BME280 datasheet). 
    //@param reg register to read. 
    //@param length number of registers to read (max: 4)
    //@return read data. LSB = last register read. 
    uint32_t readRegisterBurst(uint8_t reg, uint8_t length)
    {
      if (length > 4 || length == 0)
        return 0L;

      uint32_t data = 0L;
      uint8_t curr_byte = 0;

      sw.startWait(address_, SoftWire::writeMode);
      sw.llWrite(reg);

      sw.repeatedStart(address_, SoftWire::readMode);

      uint8_t i = 0;
      for (; i < length - 1; i++){
        sw.readThenAck(curr_byte);  // Read 1 byte and then send ack
        data = (data << 8) | curr_byte;
      }

      sw.readThenNack(curr_byte);  // Read 1 byte and then send ack
      data = (data << 8) | curr_byte;

      sw.stop();

      return data;
    }

    //this function must be implemented by derived classes. this function is responsible for sending data to the sensor. 
    //@param reg register to write to.
    //@param data data to write to register.
    void writeRegister(uint8_t reg, uint8_t data)
    {
      sw.startWait(address_, SoftWire::writeMode);
      sw.llWrite(reg);
      sw.llWrite(data);
      sw.stop();
    }
    
    uint8_t address_;   //i2c address of sensor
};
