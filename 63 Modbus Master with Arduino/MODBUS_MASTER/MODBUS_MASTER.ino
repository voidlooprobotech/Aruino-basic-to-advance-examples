 #include "ModbusHandler.h"

void setup() {
  // Serial for PC Monitor
  Serial.begin(9600);
  while (!Serial) { ; // Wait for serial port to connect
  }
  
  // Initialize Modbus (Hardware pins D10, D11, D2)
  setupModbus();
  Serial.println(F("--- MODBUS MASTER INITIALIZED ---"));
}

void loop() {
  // --- 1. Read Data from ModSim (Using 0-based Addressing) ---
  
  // 40010 -> Holding Register (Address 9)
  uint16_t holdingVal = readHoldingRegister(9);
#if 0  
  // 30005 -> Input Register (Address 4)
  uint16_t inputVal = readInputRegister(4);
  
  // 10012 -> Discrete Input (Address 11)
  bool discreteVal = readDiscreteInput(11);
  
  // 00015 -> Coil Status (Address 14)
  bool coilVal = readCoil(14);
#endif
  // --- 2. Print Data to Serial Monitor ---
  Serial.println(F("-----------------------"));
  Serial.print(F("Holding Reg (40010): ")); Serial.println(holdingVal);
  
#if 0
  Serial.print(F("Input Reg   (30005): ")); Serial.println(inputVal);
  Serial.print(F("Discrete In (10012): ")); Serial.println(discreteVal ? F("ON") : F("OFF"));
  Serial.print(F("Coil Status (00015): ")); Serial.println(coilVal ? F("ON") : F("OFF"));
#endif 
  // ModSim connection check
  if(holdingVal == 0xFFFF /*&& inputVal == 0xFFFF*/) {
    Serial.println(F("Error: Check RS485 Wiring or ModSim connection."));
  }

  delay(500); // Wait 2 seconds between polls
}
