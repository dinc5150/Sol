// MqttObj.h

#ifndef _MQTTOBJ_h
#define _MQTTOBJ_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MqttObj {
protected:

public:
	char * MqttID;

	MqttObj(char * mqttID);

	
	virtual void ExecuteCmd(int CmdType, byte * value); //Default CmdType is passed as null

};

#endif

