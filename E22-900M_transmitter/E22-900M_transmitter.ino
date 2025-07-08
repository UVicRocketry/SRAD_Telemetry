#include <SRAD_config.h>
#include <HardwareSerial.h>
#include <Adafruit_GPS.h>

#define USB_Serial Serial
#define GPS_Serial Serial1

//Set up SPI for transmitter
SPIClass spi(MOSI, MISO, SCK);
SPISettings spiSettings(1000000, MSBFIRST, SPI_MODE0);
SX1262 radio = new Module(NSS, TX_DONE, TRESET, BUSY, spi, spiSettings);
int transmissionState = RADIOLIB_ERR_NONE;
volatile bool transmittedFlag = false;

 
  
void setup() {

  
  //Setup UART
  USB_Serial.begin(9600);
  GPS_Serial.begin(9600);

  spi.begin();

  transmitter_init();

}


void loop(){


  char* sentence = readGPSSentence();
  if (sentence != nullptr) {
    USB_Serial.print(sentence);
  }

  int state = radio.startTransmit(sentence);


  // if (state == RADIOLIB_ERR_NONE) {
  //   // the packet was successfully transmitted
  //   USB_Serial.println(F("success!"));
  // }
  // else {
  //   // some other error occurred
  //   USB_Serial.print(F("failed, code "));
  //   USB_Serial.println(state);
  // }

  delay(1000);

}

/**
  Function that will read a GPS sentence

*/
char* readGPSSentence() {
  static char gpsBuffer[100];
  static int gpsIndex = 0;

  while (GPS_Serial.available()) {
    char c = GPS_Serial.read();

    if (gpsIndex < sizeof(gpsBuffer) - 1) {
      gpsBuffer[gpsIndex++] = c;

      if (c == '\n') {
        gpsBuffer[gpsIndex] = '\0';
        gpsIndex = 0;
        return gpsBuffer;  // Return full sentence
      }
    } else {
      gpsIndex = 0;  // Prevent overflow
    }
  }

  return nullptr;  // No complete sentence yet
}

void transmitter_init(){

  USB_Serial.println("[SX1262] Initializing ... ");
  int state = radio.begin();
  USB_Serial.println(state);

  USB_Serial.println("Set Frequency:");
  state = radio.setFrequency(915);
  USB_Serial.println(state);
  
  USB_Serial.println("Set TCXO:");
  // //state = radio.setBitRate(100.0);
  state = radio.setTCXO(TX_TCXO);
  USB_Serial.println(state);

  USB_Serial.println("Set Output Power: ");
  state = radio.setOutputPower(TX_POWER);
  USB_Serial.println(state);
  
  USB_Serial.println("Set Bandwidth: ");
  state = radio.setBandwidth(TX_BW);
  USB_Serial.println(state);

  USB_Serial.println("Set Spreading Factor: ");
  state = radio.setSpreadingFactor(TX_SF);
  USB_Serial.println(state);

  USB_Serial.println("Set Sync Word: ");
  state = radio.setSyncWord(SYNC_WORD);
  USB_Serial.println(state);

  USB_Serial.println("Set Preamble Length: ");
  state = radio.setPreambleLength(PREAMBLE_LENGTH);
  USB_Serial.println(state);

  USB_Serial.println("Set Coding Rate: ");
  state = radio.setCodingRate(TX_CODING_RATE);
  USB_Serial.println(state);
  
  
  radio.setRfSwitchPins(RX_EN,TX_EN);
  

}

