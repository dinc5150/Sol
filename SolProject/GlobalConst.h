// GlobalConst.h

#ifndef _GLOBALCONST_h
#define _GLOBALCONST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

static const byte TOTAL_CHANNELS = 50;
static const byte TOTAL_TRIGGERS = 50;

#define MQTT_RECONNECT_TIMEOUT 100000 //100 seconds
//static bool LOG_TO_FILE = false;
//static bool LOG_TO_SERIAL = true;

static char DEVICE_NAME[] = "sol";
static byte IP[] = { 10, 0, 0, 10 }; // IP for this device
static byte MAC[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
static byte MQTT_SERVER_IP[] = { 10, 0, 0, 132 }; // IP Address of your MQTT Server
static unsigned int MQTT_SERVER_PORT = 1883; // PORT of your MQTT Server



#endif

