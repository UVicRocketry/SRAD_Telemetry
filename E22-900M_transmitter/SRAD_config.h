#ifndef CONFIG_H

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


//Transmitter control pins
#define TX_EN PA12      // Set high
#define RX_EN PA11      // Set low


//Transmitter parameters
#define TX_POWER           5   // dBm
#define TX_FREQ          915   // MHz   
#define TX_TCXO          1.8   // V
#define TX_BW            250   // Hz
#define TX_SF              9   // Spreading factor
#define SYNC_WORD       0x12   // Sync word for LoRa
#define PREAMBLE_LENGTH   12   // Preamble length for LoRa
#define TX_CRC			   5   // Coding Rate
#define TX_CRC             0   // Enable CRC
#define TX_CODING_RATE     5   // Coding rate for LoRa (4/5)


//UART - for GPS
#define GPS_TX PA9
#define GPS_RX PA10

//UART - for flight computer
#define FC_TX PA2
#define FC_RX PA3   



#endif