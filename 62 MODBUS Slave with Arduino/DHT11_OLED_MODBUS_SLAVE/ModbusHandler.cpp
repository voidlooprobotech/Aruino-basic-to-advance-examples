#include "ModbusHandler.h"

// 1. Setup the "Highway" for Data
// We create a SoftwareSerial port so we don't interfere with the USB cable.
SoftwareSerial RS485(MODBUS_RX, MODBUS_TX);

// 2. Setup the "Modbus Worker"
// We tell the library to use our RS485 port and Pin 3 to control data flow direction.
ModbusRTUSlave mbSlave(RS485, RS485_CTRL);
//ModbusRTUSlave mbSlave(RS485);
// 3. Create the "Storage Box"
// This array holds the values that the Master (PC) will eventually read.
uint16_t HoldingRegs[HOLDING_COUNT]; 

void setupModbus() {
  // Open the communication line at 9600 speed
  RS485.begin(MODBUS_BAUD);

  // THE LINKING STEP (Crucial for Beginners):
  // We tell the Modbus Worker: "Whenever a Master asks for Holding Registers, 
  // look inside our 'HoldingRegs' array."
  mbSlave.configureHoldingRegisters(HoldingRegs, HOLDING_COUNT);
  
  // Start the Slave with its unique ID
  mbSlave.begin(SLAVE_ID, MODBUS_BAUD);
}

/**
 * This function acts as the bridge between your Sensors and the Modbus Network.
 */

void updateModbus(int temp, int hum) {
  // Step A: Load your sensor data into the storage box (0-based addresses)
  HoldingRegs[REG_TEMP] = (uint16_t)temp; // Goes to Modbus Address 0 (40001)
  HoldingRegs[REG_HUM]  = (uint16_t)hum;  // Goes to Modbus Address 1 (40002)
  
  // Step B: The "Listening" Step
  // The Slave stays quiet until it hears the Master ask for ID 1.
  // When requested, it automatically sends the data from HoldingRegs.
  mbSlave.poll(); 
}