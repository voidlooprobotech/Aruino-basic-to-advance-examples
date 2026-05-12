#ifndef MODBUS_HANDLER_H
#define MODBUS_HANDLER_H

/* 
 * =================================================================
 * MODBUS MEMORY ADDRESSING REFERENCE TABLE
 * =================================================================
 * Address Range  | Register Type     | Access     | Description
 * -----------------------------------------------------------------
 * 00001 – 09999  | Coil              | Read/Write | 1-bit Digital Outputs
 * 10001 – 19999  | Discrete Input    | Read-Only  | 1-bit Digital Inputs
 * 30001 – 39999  | Input Register    | Read-Only  | 16-bit Analog Inputs
 * 40001 – 49999  | Holding Register  | Read/Write | 16-bit Config/Data
 * =================================================================
 * NOTE: In code, use 0-based addressing (e.g., 40001 is address 0).
 */


#include <Arduino.h>
#include <ModbusMaster.h>
#include <SoftwareSerial.h>

#define MODBUS_BAUD 9600
#define SLAVE_ID 1  
#define MAX485_RE_DE 3
#define MODBUS_RX 10  //RO
#define MODBUS_TX 11  //DI

void setupModbus();

// Read Functions for all 4 types
bool readCoil(uint16_t address);             // FC 01: Read Coils (1-bit)
bool readDiscreteInput(uint16_t address);    // FC 02: Read Discrete Inputs (1-bit)
uint16_t readHoldingRegister(uint16_t addr); // FC 03: Read Holding Regs (16-bit)
uint16_t readInputRegister(uint16_t addr);   // FC 04: Read Input Regs (16-bit)

#endif
