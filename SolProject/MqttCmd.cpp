// 
// 
// 

#include "MqttCmd.h"
#include "MemoryFree.h"

//#include "External Libs\pubsubclient-master\src\PubSubClient.h"
//#include "Channel.h"



MqttCmd::MqttCmd()
{
	
}

void MqttCmd::AddMqttObject(MqttObj * newMqttObj){
	MqttObjects[totalMqttObjs] = newMqttObj;
	totalMqttObjs++;
}

void MqttCmd::callback(char* topic, byte* payload, unsigned int length) {
	payload[length] = '\0';
	Serial.println("Callback");
	Serial.print("topic: "); Serial.println(topic);
	Serial.print("length: "); Serial.println(length);

	Serial.print("payload: "); Serial.println(atoi((char*)payload));

	Serial.println();





	//this is the fixed way to catch it
	if (strcmp(topic, "/house/lights/1/com") == 0) {
		mychannels[0]->Cmd(Channel::Cmd_SetCurrValue, atoi((char*)payload));
	}

	if (strcmp(topic, "/house/memstatus") == 0) {
		MqttClient->publish("/house/sol/mem", (char*)freeMemory());
		//logger->WriteLn("Mem", freeMemory());
	}



	//Split Topic and find what we want to do
	//I got the example from - http://forum.arduino.cc/index.php?topic=42137.0 
	char * Topics[6];
	//char *p = sz;
	char *str;
	int totalTopics = 0;
	while ((str = strtok_r(topic, "/", &topic)) != NULL){ // delimiter is the semicolon
		Serial.println(str);
		Topics[totalTopics] = str;
		totalTopics++;
	}

	if (totalTopics >= 4) {

		TopicCmdItemType(Topics[0], String(Topics[1]), atoi(Topics[2]), atoi(Topics[3]), payload);
	}else if (totalTopics >= 2) {
		// /command/itemId
		if (Topics[0] == "command") {
			for (int i = 0; i < totalMqttObjs; i++) {
				if (MqttObjects[i]->MqttID == Topics[1]) {
					MqttObjects[i]->ExecuteCmd(NULL, payload);
				}
			}
		}
	}

	

	






	/*if (strcmp(topic, "/home/1/ard1/p1/com") == 0) {
	if (payload[0] == '0')
	{
	digitalWrite(4, LOW);
	lcd.home();
	lcd.clear();
	lcd.write((uint8_t)1);
	lcd.print("Turning Fan OFF");
	delay(100);
	client.publish("/home/1/ard1/p1/state", "0");
	}
	else if (payload[0] == '1')
	{
	digitalWrite(4, HIGH);
	lcd.home();
	lcd.clear();
	lcd.write((uint8_t)1);
	lcd.print("Turning Fan ON");
	delay(100);
	client.publish("/home/1/ard1/p1/state", "1");
	}
	}

	if (strcmp(topic, "/home/1/ard1/p2/com") == 0) {
	if (payload[0] == '0')
	{
	digitalWrite(5, LOW);
	lcd.home();
	lcd.clear();
	lcd.write((uint8_t)1);
	lcd.print("Turning Light OFF");
	delay(100);
	client.publish("/home/1/ard1/p2/state", "0");
	}
	else if (payload[0] == '1')
	{
	digitalWrite(5, HIGH);
	lcd.home();
	lcd.clear();
	lcd.write((uint8_t)1);
	lcd.print("Turning Light ON");
	delay(100);
	client.publish("/home/1/ard1/p2/state", "1");
	}
	}*/


}

void MqttCmd::TopicCmdItemType(String location, String itemType, int  itemID, int  cmd, byte* payload){
		//We dont need to check for location yet, so skipping it for now
	Serial.println(location);
	Serial.println(itemType);
		if (itemType == "channel") {
			Serial.println("Channel Command");
			TopicCmdChannels(location, itemType, itemID, cmd, payload);
		}
	}

void MqttCmd::TopicCmdChannels(String location, String itemType, int  itemID, int  cmd, byte* payload) {
	
		Serial.println("channelIdx");

		
		if (!isDigit(((char*)payload)[0])) {
			//Doesn’t start with a number so its not a numeric value
			//IGNORE
			return;
		}
		int value = -1;
		if ((char*)payload == "ON") {
			value = 100;
		}else if((char*)payload == "OFF") {
			value = 0;
		}
		else {
			Serial.println("Default Percentage");
			value = atoi((char*)payload);
		}
		mychannels[itemID]->Cmd(cmd, value);
		
}


void MqttCmd::PublishEvent(char ObjType[], int ObjId, char EventType[]) {
	char  subject[50];

	//char charObjBuffer[50];
	//ObjType.toCharArray(charObjBuffer, 50);

	//char charEventBuffer[50];
	//EventType.toCharArray(charEventBuffer, 50);

	sprintf(subject, "/%s/%s/evt/%s/%d/%s", Location,Device, ObjType,ObjId, EventType);
	Serial.print("Publish: ");
	Serial.println(subject);
	//String subject = "/" + Location + "/" + Device + "/evt/" + ObjType + "/";
	//subject += ObjId;
	//subject += "/" + EventType;
	//MqttClient->publish((char *)subject.c_str(), 0);
	MqttClient->publish(subject, 0);
}

void MqttCmd::loop(){
	if (MqttClient == NULL) {
		Serial.println("ERROR: You need to add MqttClient to MqttObj");
		return;
	}

	if (!MqttClient->connected()) {
		unsigned long now = millis(); // current (relative) time in msecs.
		//Serial.println(now);
		if (_connectionStartTime == 0 && now < MQTT_RECONNECT_TIMEOUT || now > _connectionStartTime + MQTT_RECONNECT_TIMEOUT) { //If only just booted or greater than the timeout
			if (MqttClient->connect(DEVICE_NAME)) {
				Serial.println("MTQQected");
				//MqttClient->publish("outTopic", "hello world");
				MqttClient->subscribe("/house/#");  // Subscribe to all messages for this device
			}
			else {
				Serial.print("Could not connect to MQTT. Error: ");
				Serial.println(MqttClient->state());
				_connectionStartTime = now;
				return;
			}
		}
	}
	MqttClient->loop();

}


