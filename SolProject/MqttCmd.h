// Mqtt.h

#ifndef _MQTTCMD_h
#define _MQTTCMD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "External Libs\pubsubclient-master\src\PubSubClient.h"
#include "Channel.h"
#include "GlobalConst.h"
class MqttCmd
{
 protected:
	 unsigned long _connectionStartTime = 0;

	

	 void TopicCmdItemType(String location, String itemType, int itemID, int cmd, byte * payload);

	 void TopicCmdChannels(String location, String itemType, int itemID, int cmd, byte * payload);

	
	

	 
 public:
	 PubSubClient * MqttClient = NULL;
	 char * Location = "house";
	 char * Device = "sol";

 Channel * mychannels[TOTAL_CHANNELS];
 MqttObj * MqttObjects[TOTAL_CHANNELS + TOTAL_TRIGGERS];
 int totalMqttObjs = 0;

 MqttCmd();
 void AddMqttObject(MqttObj * newMqttObj);

	void callback(char * topic, byte * payload, unsigned int length);



	

	



	void PublishEvent(char ObjType[], int ObjId, char EventType[]);
	//void PublishEvent(String ObjType, int ObjId, String EventType);
	void loop();


	
};

//extern MqttClass Mqtt;

#endif

