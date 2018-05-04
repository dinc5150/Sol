// Channel.h

#ifndef _CHANNEL_h
#define _CHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Log.h"
#include "MqttObj.h"

///Abstract class Channel
class Channel : public MqttObj
{
 protected:
	 
	 virtual void BroadcastStatus();
	 Log * logger = NULL;
	 int minValue=0;
	 int maxValue=1;

 public:
	 static const int Cmd_Off = 0;
	 static const int Cmd_On = 1;
	 static const int Cmd_SetCurrValue = 2;
	 static const int Cmd_SetCurrPercentage = 3;

	// Mqtt * mqttHelper = NULL;

	 char ID[10];
	 byte pin;
	 int currentValue; //This is the current value of the Channel
	 
	 Channel(byte _pin, Log * _logger, char id[]);

	 

	 virtual void On();

	 virtual void Off();

	 virtual bool IsOn();

	 virtual bool IsOff();

	 virtual void Cmd(int cmd, int Value);

	 void SetValue(int value);

	 int GetValue();

	 int SetValuePercentage(int value);

};



#endif

