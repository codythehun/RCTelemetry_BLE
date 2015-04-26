# RCTelemetry_arduino
Arduino library to publish remote controlled (air)craft telemetry data over bluetooth low energy. It's based on Adafruit's nrf8001 breakout.


## nrf8001 PINOUT ##

The pin locations are defined in **ble_system.h**, the supported systems are defined in **hal_aci_tl.cpp**. The following pinout is used by default for the Arduino Uno:

* SCK -> Pin 13
* MISO -> Pin 12
* MOSI -> Pin 11
* REQ -> Pin 10
* RDY -> Pin 2 (HW interrupt)
* ACT -> Not connected
* RST -> Pin 9
* 3V0 - > Not connected
* GND -> GND
* VIN -> 5V

RDY must be on pin 2 since this pin requires a HW interrupt.

3V0 is an optional pin that exposes the output of the on-board 3.3V regulator. You can use this to supply 3.3V to other peripherals, but normally it will be left unconnected.

ACT is not currently used in any of the existing examples, and can be left unconnected if necessary.
