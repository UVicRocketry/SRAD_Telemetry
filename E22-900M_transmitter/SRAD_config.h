#ifndef CONFIG_H


//Transmitter
#define BUSY     PB7
#define TX_DONE  PB8
#define TRESET   PB6

//SPI - for transmitter
#define SCK  PB3
#define MISO PB4
#define MOSI PB5
#define CS   PA15

//Transmitter control pins
#define TX_EN PA8     ```
#define RX_EN PA15     

//Transmitter parameters
#define TX_POWER           5   // dBm
#define TX_FREQ          915   // MHz   
#define TX_TCXO          1.8   // V
#define TX_BW            250   // Hz
#define TX_SF             12   // Spreading factor
#define TX_CR              8   // Coding rate
#define SYNC_WORD       0x12   // Sync word for LoRa
#define PREAMBLE_LENGTH   12   // Preamble length for LoRa


//UART - for GPS
#define GPS_TX PB12
#define GPS_RX PB13

//UART - for flight computer
#define FC_TX PA2
#define FC_RX PA3   

typedef enum {
    TX_MODE,
    RX_MODE,
    GPS_MODE
} state_t;


#endif