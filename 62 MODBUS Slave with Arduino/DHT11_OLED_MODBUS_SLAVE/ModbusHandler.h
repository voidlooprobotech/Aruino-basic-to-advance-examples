/* * =================================================================
 * MODBUS MEMORY ADDRESSING REFERENCE TABLE
 * =================================================================
 * Address Range  | Register Type     | Access     | Description
 * -----------------------------------------------------------------
 * 00001 – 09999  | Coil              | Read/Write | Digital Out (Relays)
 * 10001 – 19999  | Discrete Input    | Read-Only  | Digital In (Buttons)
 * 30001 – 39999  | Input Register    | Read-Only  | Analog In (Sensors)
 * 40001 – 49999  | Holding Register  | Read/Write | Multi-purpose Data
 * =================================================================
 * NOTE: Modbus addresses in software start at 0. 
 * So, "Address 0" in code = "40001" in ModScan software.
 */

#ifndef MODBUS_HANDLER_H
#define MODBUS_HANDLER_H

#include <Arduino.h>
#include <SoftwareSerial.h> // Allows Modbus on pins 10/11 instead of USB port
#include <ModbusRTUSlave.h>  // The main engine for Modbus communication

// --- Hardware Configuration ---
#define SLAVE_ID   1    // Unique ID for this Arduino on the Modbus network
#define RS485_CTRL 3    // Connects to DE and RE pins on MAX485 to switch Send/Receive
#define MODBUS_RX  10   // Connects to RO (Receiver Output) on MAX485
#define MODBUS_TX  11   // Connects to DI (Driver Input) on MAX485

/* * Communication Speed (Baud Rate)
 * 9600 is the industry standard for stable RS485 communication.
 * We define it here so that if we change it to 19200 or 115200, 
 * the entire code updates automatically in one click.
 */
#define MODBUS_BAUD 9600

// --- Memory Configuration ---
// We define how many 16-bit "slots" we need in our data table
#define HOLDING_COUNT 2 

// --- Register Map (0-based) ---
// These are the array indices. 
// REG_TEMP is index 0 -> PC asks for 40001
// REG_HUM  is index 1 -> PC asks for 40002
#define REG_TEMP 0
#define REG_HUM  1

/**
 * @brief Initializes the RS485 Serial and Modbus Slave engine.
 * Call this once in the main setup() function.
 */
void setupModbus();

/**
 * @brief Updates the Modbus registers with fresh data and listens for requests.
 * @param temp The current temperature integer
 * @param hum  The current humidity integer
 * Call this in every loop() to keep communication alive.
 */
void updateModbus(int temp, int hum);

#endif