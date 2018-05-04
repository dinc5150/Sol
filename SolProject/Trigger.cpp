// 
// 
// 

#include "Trigger.h"

Trigger::Trigger(int _id, int _pin, char id[], MqttCmd * _mqttCmdHelper, Log * _logger): MqttObj::MqttObj(id) {
	Id = _id;
	pin = _pin;
	totalChannels = 0;
	totalFeedbackChannels = 0;
	mqttCmdHelper = _mqttCmdHelper;
	logger = _logger;
}
//
//Trigger::Trigger() {
//}






void Trigger::AddChannel(Channel * channel) {
	if (totalChannels >= MAX_CHANNELS) {
		logger->WriteLn((String)"ERR: TOO MANY CHANNELS ON TRIGGER", Id);
		return;
	}
	channels[totalChannels] = channel;
	totalChannels++;
}
void Trigger::AddFeedbackChannel(Channel * channel) {
	if (totalFeedbackChannels >= MAX_FEEDBACK_CHANNELS) {
		logger->WriteLn((String)"ERR: TOO MANY FEEDBACK CHANNELS ON TRIGGER", Id);
		return;
	}
	feedbackChannels[totalFeedbackChannels] = channel;
	totalFeedbackChannels++;
}

//void Trigger::CallEvent(int _event)
//{
//	Serial.print("EventCalled: ");
//	Serial.println(GetEventText(_event));
//}

String Trigger::GetEventText(int _event) {
	switch (_event) {
	case 1: return "Click";
		break;
	case 2: return "Double Click";
		break;
	case 3: return "Long Press Start";
		break;
	case 4: return "Long Pressing";
		break;
	case 5: return "Long Press Stop";
		break;
		
	}
	return "";
}






