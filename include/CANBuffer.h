#pragma once

template <class BufferType, unsigned int pi_delay_us>
  class CANBuffer //: public PololuTWISlave
{
  public:

  uint8_t index;
  bool index_set = 0;
  uint8_t i2c_write_length = 0;
  uint8_t i2c_write_buffer[24];

  BufferType i2c_read_buffer;
  BufferType staging_buffer;
  BufferType buffer_old;

  void updateI2CBuffer()
  {
    memcpy(&i2c_read_buffer, &staging_buffer, sizeof(BufferType));
  }

  void finalizeI2CWrites()
  {
    if(i2c_write_length == 0) return;

    for(uint8_t i=0; i < i2c_write_length; i++)
    {
      ((uint8_t *)&staging_buffer)[i] = i2c_write_buffer[i];
    }
    i2c_write_length = 0;
  }

  BufferType buffer;

  void updateBuffer()
  {
    cli();
    memcpy(&buffer, &staging_buffer, sizeof(BufferType));
    sei();
    memcpy(&buffer_old, &buffer, sizeof(BufferType));
  }

  void finalizeWrites()
  {
    uint8_t i;
    cli();
    for(i=0; i < sizeof(BufferType); i++)
    {
      if(((uint8_t *)&buffer_old)[i] != ((uint8_t *)&buffer)[i])
        ((uint8_t *)&staging_buffer)[i] = ((uint8_t *)&buffer)[i];
    }
    sei();
  }

  virtual void receive()
  {
      // Read the CANBus data here...
      // i2c_write_buffer[i2c_write_length] = Wire.read();
      // i2c_write_length ++;
  }

  virtual void transmit()
  {
    Serial.println("transmit");
    uint8_t i;
    for(i=0; i < sizeof(BufferType); i++)
    { 
      Serial.print(((uint8_t *)&i2c_read_buffer)[i]);
      // Write the CANBus data here...
      // Wire.write(((uint8_t *)&i2c_read_buffer)[i]);
    }
    Serial.println();
  }

  virtual void start()
  {
    index_set = false;
  }

  virtual void stop()
  {
    finalizeI2CWrites();
  }

  virtual void printWriteBuffer() {
    uint8_t i;
    for(i=0; i < sizeof(BufferType); i++)
    { 
      Serial.print(((uint8_t *)&i2c_write_buffer)[i], HEX);
    }
    Serial.println();
  }

  virtual void printBuffer() {
    uint8_t i;
    for(i=0; i < sizeof(BufferType); i++)
    { 
      Serial.print(((uint8_t *)&buffer)[i], HEX);
    }
    Serial.println();
  }

  /* Initialize the slave on a given address. */
  void init()
  {
    // Wire.slaveWrite((uint8_t *)&i2c_read_buffer, sizeof(BufferType));
  }
};