#include <RadioLib.h>
#include <SRAD_config.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

// #define TEST_GPS // uncomment if you want to test GPS and not transmitter
// #define TEST_E22 // uncomment if you want to test out the transmitter but not gps

// set up radio spi
SPIClass spi(MOSI, MISO, SCK);
SPISettings spiSettings(1000000, MSBFIRST, SPI_MODE0);
SX1262 radio = new Module(CS, TX_DONE, BUSY, TRESET, spi, spiSettings);
int transmissionState = RADIOLIB_ERR_NONE;

//uart for GPS
HardwareSerial GPSSerial(GPS_RX, GPS_TX);

void setup() {

//initialize serial monitor
  Serial.begin(115200);
  #if defined(USBCON)
    while (!Serial) delay(10);
  #endif

  Serial.print(F("[SX1262] Initializing ... "));

//intialize SPI and transmiter

  spi.begin();

  int state = radio.begin();
<<<<<<< Updated upstream
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


  
=======
#ifndef TEST_GPS

  if (state != RADIOLIB_ERR_NONE) {
    Serial.print(F("Radio init failed: "));
    Serial.println(state);
    while (true);
  }
  
  state = radio.setFrequency(TX_FREQ);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.println(F("Failed to set frequency"));
    while (true);
  }

    state = radio.setTCXO(TX_TCXO);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.println(F("Failed to set TCXO"));
    while (true);
  }

    state = radio.setOutputPower(TX_POWER);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.println(F("Failed to set output power"));
    while (true);
  }

  radio.setBandwidth(TX_BW);
  radio.setSpreadingFactor(TX_SF);
  radio.setSyncWord(SYNC_WORD);
  radio.setPreambleLength(PREAMBLE_LENGTH);
  radio.setCodingRate(TX_CODING_RATE);
  radio.setRfSwitchPins(RX_EN,TX_EN);
#endif
//Intialize UART for GPS

#ifdef TEST_GPS
  GPSSerial.begin(9600);
#endif

>>>>>>> Stashed changes

}


void loop() {
  
<<<<<<< Updated upstream
  int state = radio.transmit("Hello_World");
=======


#ifdef TEST_GPS
    if (Serial.available()) {
    char c = Serial.read();
    GPSSerial.write(c);
  }

  if (GPSSerial.available()) {
    char c = GPSSerial.read();
    Serial.write(c);
  }
#endif



#ifdef TEST_E22
  int state = radio.transmit("hello cruel world");
>>>>>>> Stashed changes


  if (state == RADIOLIB_ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F("success!"));
  }
  else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);
  }
  
  delay(1000);
 
#endif
}
