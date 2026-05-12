#include "ModbusHandler.h"

SoftwareSerial modbusSerial(MODBUS_RX, MODBUS_TX);
ModbusMaster node;

void preTransmission() { digitalWrite(MAX485_RE_DE, HIGH); }
void postTransmission() { digitalWrite(MAX485_RE_DE, LOW); }

void setupModbus() {
  pinMode(MAX485_RE_DE, OUTPUT);
  digitalWrite(MAX485_RE_DE, LOW);
  modbusSerial.begin(MODBUS_BAUD);
  node.begin(SLAVE_ID, modbusSerial);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

// FC 01 - Read Coils
bool readCoil(uint16_t address) {
  uint8_t result = node.readCoils(address, 1);
  return (result == node.ku8MBSuccess) ? node.getResponseBuffer(0) : false;
}

// FC 02 - Read Discrete Inputs
bool readDiscreteInput(uint16_t address) {
  uint8_t result = node.readDiscreteInputs(address, 1);
  return (result == node.ku8MBSuccess) ? node.getResponseBuffer(0) : false;
}

// FC 03 - Read Holding Registers
uint16_t readHoldingRegister(uint16_t addr) {
  uint8_t result = node.readHoldingRegisters(addr, 1);
  return (result == node.ku8MBSuccess) ? node.getResponseBuffer(0) : 0xFFFF;
}

// FC 04 - Read Input Registers
uint16_t readInputRegister(uint16_t addr) {
  uint8_t result = node.readInputRegisters(addr, 1);
  return (result == node.ku8MBSuccess) ? node.getResponseBuffer(0) : 0xFFFF;
}
