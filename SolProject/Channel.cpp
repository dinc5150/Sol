
#include "Channel.h"

Channel::Channel(byte _pin, Log * _logger, char id[]) : MqttObj::MqttObj(id){
	strncpy(ID, id, 10);

	pin = _pin;
	pinMode(pin, OUTPUT);
	currentValue = LOW;
	//mqttHelper = _mqttHelper;
	logger = _logger;

}

void Channel::BroadcastStatus() {

}

void Channel::On(){
	digitalWrite(pin, maxValue);
	currentValue = maxValue;
	//logger->WriteLn("On", ID);
};

void Channel::Off(){
	digitalWrite(pin, minValue);
	currentValue = minValue;
	//logger->WriteLn("Off", ID);
}
bool Channel::IsOn()
{
	return (currentValue > 0);
}
bool Channel::IsOff()
{
	return (currentValue == 0);
	
}
//void Channel::Cmd(int cmd, int value)
//{
//	Serial.print(cmd);
//	Serial.print(":");
//	Serial.print(value);
//}

void Channel::Cmd(int cmd, int value)
{
	logger->WriteLn((String)"ID", ID);
	switch (cmd) {
	case Channel::Cmd_SetCurrValue:
		if (value == minValue) {
			Off();
		}
		else {
			On();
		}
		break;
	case Channel::Cmd_SetCurrPercentage:
		SetValuePercentage(value);
		break;
	default:

		logger->Write(cmd);
		logger->WriteLn("", value);
		break;
	}
}

//Sets the current brightness Value
//Shortcut to command
void Channel::SetValue(int value) {
	//Cmd(Cmd_SetCurrValue, value);
	digitalWrite(pin, value);
}

//Gets the current brightness value
int Channel::GetValue() {
	return currentValue;
}

int Channel::SetValuePercentage(int value) {
	int range = (maxValue - minValue);
	logger->WriteLn("percentVal", int(value / 100.0 * range) + minValue);
	SetValue(int(value / 100.0 * range) + minValue); //percent of range + base value (minValue)
}




