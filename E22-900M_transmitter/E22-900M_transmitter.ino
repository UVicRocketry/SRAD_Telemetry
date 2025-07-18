#include <RadioLib.h>
#include <SRAD_config.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>

#define USB_Serial Serial


SPIClass spi(MOSI, MISO, SCK);
SPISettings spiSettings(1000000, MSBFIRST, SPI_MODE0);
SX1262 radio = new Module(NSS, TX_DONE, TRESET, BUSY, spi, spiSettings);
int transmissionState = RADIOLIB_ERR_NONE;
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

SoftwareSerial GPS_Serial(GPS_RX, GPS_TX);
SoftwareSerial FC_Serial(FC_RX, FC_TX);

telemetry_data_t data;
int prev_second = 0;

void setup() {

  USB_Serial.begin(9600);
  GPS_Serial.begin(9600);

  spi.begin();

  transmitter_init();
  pixels.begin();

  data.callsign = CALL_SIGN;
  
  
}

void loop() {

  //Read & parse GPS Data
  data.gpsBuff = readGPSSentence();
  gpsParse(data.gpsBuff, &data);
  String payload = serializeTelemetry(data); //Serialize data to transmit

  //Check for GPS lock
  if(!data.gpsData.status.equals("V")){
    SET_LED_BLUE
  }
  
  
  //Transmit on every odd second
  int current_second = data.gpsData.UTCtime.toInt();
  if(current_second != prev_second && (current_second % 2) == 1){
      USB_Serial.println(payload);
      transmissionState = radio.startTransmit(payload);
      radio.transmit(payload);
      prev_second = current_second;
  }

}

String readGPSSentence() {

 String line = GPS_Serial.readStringUntil('\n');
 return line;

}
String readFCData(){

}

int gpsParse(const String gps_sentence, telemetry_data_t* data) {

  // 1) Copy into a mutable buffer
  int bufSize = gps_sentence.length() + 1;
  char buf[bufSize];
  gps_sentence.toCharArray(buf, bufSize);

  // 2) Check header
  char* token = strtok(buf, ",");

  // get  GPS status from header $GPRMC
  if(strcmp(token, "$GPRMC") == 0){
    strtok(nullptr, ",");
    token = strtok(nullptr, ",");
    data->gpsData.status = String(token);
  }

 // get GPS Data from $GPGGA
  else if (strcmp(token, "$GPGGA") == 0 && !data->gpsData.status.equals("V")) {
    
    // 3) UTC time
    token = strtok(nullptr, ".");
    if (!token) return 0;
    data->gpsData.UTCtime = String(token);
    strtok(nullptr, ",");

    // 4) Latitude
    token = strtok(nullptr, ",");
    if (!token) return 0;
    data->gpsData.lat = String(token);
    // hemisphere
    token = strtok(nullptr, ",");
    if (!token) return 0;
    data->gpsData.lat += token;
    
    // 5) Longitude
    token = strtok(nullptr, ",");
    if (!token) return 0;
    data->gpsData.lon = String(token);
    // hemisphere
    token = strtok(nullptr, ",");
    if (!token) return 0;
    data->gpsData.lon += token;
    
    // 6) Fix quality
    token = strtok(nullptr, ",");
    if (!token) return 0;
    data->gpsData.fix = (uint8_t)atoi(token);

    // 7) Skip sats & HDOP
    strtok(nullptr, ",");
    strtok(nullptr, ",");

    // 8) Altitude
    token = strtok(nullptr, ",");
    if (!token) return 0;
    data->gpsData.alt = String(token);
  }

  return 1;
}

String serializeTelemetry(const telemetry_data_t& t) {
  
  String out;
  out.reserve(
    t.callsign.length() +
    t.gpsData.UTCtime.length() +
    t.gpsData.lat.length() +
    t.gpsData.lon.length() +
    t.gpsData.status.length() +
    t.gpsData.alt.length() +
    t.fcBuff.length() +
    6    // commas
  );

  out  = t.callsign;
  out += ',';  
  out += t.gpsData.UTCtime;
  out += ',';
  out += t.gpsData.lat;
  out += ',';
  out += t.gpsData.lon;
  out += ',';
  out += t.gpsData.alt;
  out += ',';
  out += t.gpsData.status;
  out += ',';
  out += t.fcBuff;

  return out;
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
