// 
// 
// 

#include "TriggerBtn.h"


TriggerBtn::TriggerBtn(int _id, int _pin, char id[], MqttCmd * _mqttCmdHelper, Log * _logger) : Trigger::Trigger(_id, _pin, id, _mqttCmdHelper, logger) {

	_logger->WriteLn("trigger created", _pin);
	pinMode(_pin, INPUT_PULLUP);

	TheButton = new OneButton(_pin, true, this);
	mqttCmdHelper = _mqttCmdHelper;
}

void TriggerBtn::onClick() {
	bool setOn = !channels[0]->IsOn();
	logger->WriteLn("Click", totalChannels);

	for (byte i = 0; i < totalChannels; i++) {

		if (setOn) {
			channels[i]->On();
		}
		else {

			channels[i]->Off();
		}
	}
	//feedbackChannels[0]->On();
	logger->WriteLn("switching feedback", totalFeedbackChannels);

	for (byte i = 0; i < totalFeedbackChannels; i++) {
		
		//Feed back code causes arduino ro reboot. Dont know why!
		if (setOn) {
			feedbackChannels[i]->Off();
		} else {
			feedbackChannels[i]->On();
		}
		
	}
	logger->WriteLn("Click done");
	
	mqttCmdHelper->PublishEvent("btn", Id, "click");
	
	//client.publish("/house/btn/1/evt", "click");
}

void TriggerBtn::onDblClick() {
	for (byte i = 0; i < totalChannels; i++) {
		channels[i]->SetValuePercentage(60);
		logger->WriteLn((String)"Double Click");
	}

	//logger->WriteLn("freeMemory", freeMemory());
}

void TriggerBtn::onLongPressStart() {
	for (byte i = 0; i < totalChannels; i++) {
		logger->WriteLn((String)"Long Press Start");
	}
}
void TriggerBtn::onLongPressStop() {
	for (byte i = 0; i < totalChannels; i++) {
		logger->WriteLn((String)"Long Press Stop");
	}
}

void TriggerBtn::loop() {
	TheButton->tick();
}

void TriggerBtn::CallEvent(int _event)
{
	switch (_event) {
	case Evt_Click: 
		this->onClick();
		break;
	case Evt_DoubleClick: this->onDblClick();
		break;
	case Evt_LongPressStart: this->onLongPressStart();
		break;
	case Evt_LongPressStop: this->onLongPressStop();
		break;
	default:
	
		logger->WriteLn("Unknown EventCalled", GetEventText(_event));
	}
}



