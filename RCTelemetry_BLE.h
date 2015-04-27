
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#ifndef _RCTELEMETRY_BLE_H_
#define _RCTELEMETRY_BLE_H_

#include "utility/aci_evts.h"

/* Uncomment the next line to display debug messages when reading/writing packets */
#define BLE_RW_DEBUG

extern "C" 
{
  /* Callback prototypes */
  typedef void (*aci_callback)(aci_evt_opcode_t event);
}

class RCTelemetry_BLE
{
 public:
	 RCTelemetry_BLE(int8_t req, int8_t rdy, int8_t rst);
  
  bool begin   ( uint16_t advTimeout = 0, uint16_t advInterval = 80 );
  void pollACI ( void );
 
  void setACIcallback(aci_callback aciEvent = NULL);
  void setDeviceName(const char * deviceName);

  void sendRSSI(uint8_t rssi);


  aci_evt_opcode_t getState(void);

 private:  
  void defaultACICallback(aci_evt_opcode_t event);

  // callbacks you can set with setCallback function for user extension
  aci_callback aci_event;

  bool         debugMode;
  uint16_t     adv_timeout;
  uint16_t     adv_interval;
  char         device_name[8];

  aci_evt_opcode_t currentStatus;
  
  // pins usd
  int8_t _REQ, _RDY, _RST;
};

#endif
