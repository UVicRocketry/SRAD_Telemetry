#ifndef CONFIG_H




#define CALL_SIGN "VE7DAS"

#define SET_LED_BLUE       pixels.setPixelColor(0, pixels.Color(0, 0, 150)); \
                           pixels.show()

#define SET_LED_RED        pixels.setPixelColor(0, pixels.Color(150, 0, 0)); \
                           pixels.show()

#define SET_LED_YELLOW     pixels.setPixelColor(0, pixels.Color(150, 150, 0)); \
                           pixels.show()                           

#define TURN_LED_OFF       pixels.setPixelColor(0, pixels.Color(0, 0, 0)); \
                           pixels.show()


#define INPUT_TIMEOUT_MS  5000

#define BUZZER_DURATIONS     \
  4, 4, 4, 8, 16, \
  4, 8, 16, 2, \
  \
  4, 4, 4, 8, 16,\
  4, 8, 16, 2,\
  \
  8, 8, 8, 8,\
  8, 16, 16, 8,\
  8, 4, 8, 8, 8, 8,\
  8, 8, 2

#define BUZZER_MELODY     NOTE_A4, NOTE_A4, NOTE_A4, NOTE_F4, NOTE_C5,\
  NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,\
  \
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_C5,\
  NOTE_GS4, NOTE_F4, NOTE_C5, NOTE_A4,\
  \
  NOTE_A5, NOTE_A4, NOTE_A4, NOTE_A5,\
  NOTE_GS5, NOTE_G5, NOTE_FS5, NOTE_F5,\
  NOTE_FS5, REST, NOTE_AS4, NOTE_DS5, NOTE_D5, NOTE_CS5,\
  NOTE_C5, NOTE_B4, NOTE_C5
  
#define TEMPO 300


// Your typedefs
typedef struct {

  String status;
  String UTCtime;
  String lat;
  String lon;
  uint8_t fix;
  String alt;

} gps_data_t;

typedef struct {
  String callsign;
  gps_data_t gpsData;
  String gpsBuff;
  String fcBuff;
} telemetry_data_t;

//Buzzer
#define BUZZER_PIN PA5

// Pixel LED
#define LED_COUNT 1
#define LED_PIN   PB14

//Transmitter pins
#define BUSY     PB7
#define TX_DONE  PB8
#define TRESET   PB6

//SPI - for transmitter
#define SCK  PB3
#define MISO PB4
#define MOSI PB5
#define NSS  PA15

//Transmitter control pins
#define RX_EN PA11      
#define TX_EN PA12      


// //Transmitter control pins
// #define TX_EN PA8    
// #define RX_EN PA15     


//Transmitter parameters
#define TX_POWER           5   // dBm
#define TX_FREQ          915   // MHz   
#define TX_TCXO          1.8   // V
#define TX_BW            250   // kHz
#define TX_SF             9   // Spreading factor
#define SYNC_WORD       0x12   // Sync word for LoRa
#define PREAMBLE_LENGTH   12   // Preamble length for LoRa
#define TX_CRC             0   // Enable CRC
#define TX_CODING_RATE     5   // Coding rate for LoRa (4/5)


//UART - for GPS
#define GPS_TX PB13
#define GPS_RX PB12

//UART - for flight computer
#define FC_TX PA2
#define FC_RX PA3   



#endif