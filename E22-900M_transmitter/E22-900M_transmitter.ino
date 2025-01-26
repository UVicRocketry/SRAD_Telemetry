#include <RadioLib.h>



SPIClass spi(PB5, PB4, PB3);
SPISettings spiSettings(1000000, MSBFIRST, SPI_MODE0);
SX1262 radio = new Module(PA15, PB8, PB7, PB6, spi, spiSettings);
int transmissionState = RADIOLIB_ERR_NONE;

  void setup() {
  Serial.begin(9600);

  Serial.print(F("[SX1262] Initializing ... "));
  spi.begin();
  int state = radio.begin();
  state = radio.setFrequency(915);
  //state = radio.setBitRate(100.0);
  state = radio.setTCXO(1.6);
  state = radio.setOutputPower(5);
  radio.setBandwidth(250.0);
  radio.setSpreadingFactor(9);
  radio.setSyncWord(0x12);
  radio.setPreambleLength(12);
  radio.setCodingRate(5);
  radio.setRfSwitchPins(PA11,PA12);


  

}

void loop() {
  
  int state = radio.transmit("Hello_World");


  if (state == RADIOLIB_ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F("success!"));
  }
  else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);
  }
  
  delay(2000);
  // put your main code here, to run repeatedly:

}
