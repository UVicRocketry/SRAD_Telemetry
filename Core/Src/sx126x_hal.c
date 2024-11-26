/*
 * sx126x_hal.c
 *
 * Implementation of the sx126x_h file for the STM32
 * platform.
 *
 *
 *  Created on: Nov 20, 2024
 *      Author: Zarina Guzman
 */



/*The SPI interface (from SX1262 Datasheet) :
 * synchronous full-duplex
 *  CPOL = 0
 *  CPHA = 0
 *  Motorola/Freescale nomenclature
 *
 *  An address byte followed by a data byte is sent for a write access
 *  whereas an address byte is sent and a read byte is received for the read access.
 *  The NSS pin goes low at the beginning of the frame and goes high after the data byte.
 *
 */

#include "sx126x_hal.h"
#include "main.h"




/*
sx126x_hal_write
Purpose: Write data to the transceiver via SPI.
Parameters:
Command opcode to write.
Pointer to the data buffer.
Length of the data.
Implementation:
Drive the NSS line low.
Send the command opcode over SPI.
Send the data buffer over SPI.
Drive the NSS line high.
*/
sx126x_hal_status_t sx126x_hal_write( const void* context, const uint8_t* command, const uint16_t command_length,
                                      const uint8_t* data, const uint16_t data_length ){
	// Activate chip select (active low)
	HAL_GPIO_WritePin(GPIOA, CHIP_SELECT, GPIO_PIN_RESET);

	// Transmit command
   if (HAL_SPI_Transmit(&hspi1, (uint8_t*)command, command_length, 1) != HAL_OK) {
		return SX126X_HAL_STATUS_ERROR; // Error if transmission fails
	}


    // Poll the busy line to ensure the device is ready
    uint32_t timeout = 1000; // Timeout limit
    while (HAL_GPIO_ReadPin(GPIOA, BUSY_PIN) == GPIO_PIN_SET && timeout--) {
        // If timeout occurs, return error
        if (timeout == 0) {
            return SX126X_HAL_STATUS_ERROR;
        }
    }

	// Transmit data
   if (HAL_SPI_Transmit(&hspi1, (uint8_t*)command, command_length, 1) != HAL_OK) {
		return SX126X_HAL_STATUS_ERROR; // Error if transmission fails
	}
	// Deactivate chip select
	HAL_GPIO_WritePin(GPIOA, CHIP_SELECT, GPIO_PIN_SET);

	return SX126X_HAL_STATUS_OK;
}

/*
Purpose: Read data from the transceiver via SPI.
Parameters:
Command opcode to read.
Pointer to the buffer where data will be stored.
Length of data to read.
Implementation:
Drive the cs line low.
Send the command opcode over SPI.
Receive the requested data via SPI into the buffer.
Drive the cs line high.
*/
sx126x_hal_status_t sx126x_hal_read( const void* context, const uint8_t* command, const uint16_t command_length,
                                     uint8_t* data, const uint16_t data_length ){

    // Activate chip select (active low)
    HAL_GPIO_WritePin(GPIOA, CHIP_SELECT, GPIO_PIN_RESET);

    // Transmit command (read request)
    if (HAL_SPI_Transmit(&hspi1, (uint8_t*)command, command_length, 1) != HAL_OK) {
        return SX126X_HAL_STATUS_ERROR; // Error if transmission fails
    }

    // Poll the busy line to ensure the device is ready
    uint32_t timeout = 1000; // Timeout limit
    while (HAL_GPIO_ReadPin(GPIOA, BUSY_PIN) == GPIO_PIN_SET && timeout--) {
        // If timeout occurs, return error
        if (timeout == 0) {
            return SX126X_HAL_STATUS_ERROR;
        }
    }

    // Receive data from SX126x
    if (HAL_SPI_Receive(&hspi1, data, data_length, 1) != HAL_OK) {
        return SX126X_HAL_STATUS_ERROR; // Error if reception fails
    }

    // Deactivate chip select (active high)
    HAL_GPIO_WritePin(GPIOA, CHIP_SELECT, GPIO_PIN_SET);

    return SX126X_HAL_STATUS_OK;

}
/*
sx126x_hal_reset
Purpose: Resets the SX126X transceiver.
Implementation: Toggle the reset GPIO pin connected to the transceiver.
Operation:
Set the reset pin low.
Wait at least 100 microseconds (according to the SX126X datasheet).
Set the reset pin high.
 */
sx126x_hal_status_t sx126x_hal_reset( const void* context ){

	HAL_GPIO_WritePin(GPIOA, RESET_PIN, GPIO_PIN_RESET);  // Reset pin (optional) active low
	HAL_Delay(10);  // Wait for reset to complete
	HAL_GPIO_WritePin(GPIOA, RESET_PIN, GPIO_PIN_SET);  // Release reset pin

	return SX126X_HAL_STATUS_OK;
}

/*
sx126x_hal_wakeup
Purpose: Wakes the transceiver from sleep mode.
Implementation: Perform a simple SPI transaction or toggle GPIOs based on the datasheet instructions.
Operation:
Drive the NSS (chip select) line low.
Perform a no-op SPI transaction to generate a clock signal.
Drive the NSS line high.
Wait for the busy pin to indicate readiness.
 */

sx126x_hal_status_t sx126x_hal_wakeup( const void* context ){




	return SX126X_HAL_STATUS_OK;
}
