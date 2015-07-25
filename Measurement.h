#ifndef __SENSORS_H__
#define __SENSORS_H__

#define MAX_SENSOR_INSTANCES 2

#include "Arduino.h"

//TODO: move data definition to BLE library, separate out setter functions to free helper functions in this app
class __attribute__((packed)) Measurement{
public:
	enum Type {
		RSSI = 0, // link quality // unit: raw
		BATTERY_CELL_VOLTAGE, // voltage of each cell // prec: 2 // unit: Volt
		TEMPERATURE, // temperature measurement, prec: 0 // unit: Celsius
		RPM, //p rec: 0 
		FUEL, // prec: 0 // unit: percent
		BARO_ALTITUDE, // prec: 2 // unit: meter
		ACCELERATION_X, // G sensor // prec: 2 // unit: G
		ACCELERATION_Y, 
		ACCELERATION_Z, 
		AIR_SPEED,  // prec: 1 // unit: m/s
		CURRENT, // ampers // prec: 1 // unit: Amper
		GPS_SPEED, // prec: 3 // unit: knots
		GPS_LATITUDE, // signed integer in format: +/-DDMMMMMM where the degree minutes decimal point is after the second digit so it translates to DD MM.MMMM
		GPS_LONGITUDE,
		GPS_ALTITUDE, // prec: 2 // unit: meter
		GPS_COURSE, // direction in degrees // prec: 2
		GPS_DATE,
		GPS_TIME, // utc
		LAST
		//TODO: Vario, ADC1-2, A3-4, VFAS, FuelQty, SwrId
	};

	struct __attribute__((packed)) BatteryCellVoltage{
		uint8_t cellCount; // total cell count in pack
		uint8_t cellIndex; 
		uint16_t cellValue;

	};

	struct __attribute__((packed)) GpsCoord{
		uint16_t year;
		uint8_t month;
		uint8_t day;
	};
	struct __attribute__((packed)) GpsDate{
		uint16_t year;
		uint8_t month;
		uint8_t day;
	};

	struct __attribute__((packed)) GpsTime{
		uint8_t hour;
		uint8_t min;
		uint16_t sec;
	};

	union Data {
		int32_t genericValue;
		uint8_t rssi;
		BatteryCellVoltage batteryVoltage;
		GpsTime gpsTime;
		GpsDate gpsDate;
	};

	uint8_t type;
	uint8_t sensorId;
	Data data;


	Measurement():type(LAST), sensorId(-1) {}

};



#endif