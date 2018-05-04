// Trigger.h

#ifndef _TRIGGER_h
#define _TRIGGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#ifndef _CHANNEL_h
	#include "Channel.h"
#endif
#ifndef _MQTTCMD_h
#include "MqttCmd.h"
#endif


#include "Log.h"
#include "MqttObj.h"

class Trigger : public MqttObj
{
 protected:
	 Log * logger= NULL;

 public:
	 static const int Evt_Click = 1;
	 static const int Evt_DoubleClick = 2;
	 static const int Evt_LongPressStart = 3;
	 static const int Evt_LongPressing = 4;
	 static const int Evt_LongPressStop = 5;
	 static const byte MAX_CHANNELS = 10;
	 static const byte MAX_FEEDBACK_CHANNELS = 10;
	 MqttCmd * mqttCmdHelper = NULL;


	 //Trigger(int _id, int _pin, byte _totalChannels, MqttCmd * _mqttCmdHelper, Log * _logger);
	 Trigger(int _id, int _pin, char id[], MqttCmd * _mqttCmdHelper, Log * _logger);
	// Trigger();



	 void AddChannel(Channel * channel);

	 void AddFeedbackChannel(Channel * channel);
	 
	 String GetEventText(int _event);
	 byte pin;
	 int Id;
	 byte totalChannels;
	 byte totalFeedbackChannels;

	 Channel * channels[MAX_CHANNELS];
	 Channel * feedbackChannels[MAX_FEEDBACK_CHANNELS]; //These are the button ring lights

	 virtual void loop(){};
	 virtual void CallEvent(int _event) {};


};


#endif

