// 
// 
// 

#include "ChannelPwm_Base.h"


ChannelPwm_Base::ChannelPwm_Base(byte _pin, Log * _logger, char id[], Adafruit_PWMServoDriver * _pwm) : Channel::Channel(_pin, _logger, id) {
	pwm = _pwm;
	maxValue = 4095;
	Serial.print("PWM Channel Created: ");
	Serial.println(_pin);
}

void ChannelPwm_Base::On() {
	currentValue = maxValue;
	pwm->setPWM(pin, 0, maxValue);
	//logger->WriteLn("On", ID);
}
void ChannelPwm_Base::Off() {
	currentValue = minValue;
	pwm->setPWM(pin, 0, minValue);
	//logger->WriteLn("Off", ID);
}

void ChannelPwm_Base::Cmd(int cmd, int value)
{
	logger->WriteLn("Command ID", cmd);
	logger->WriteLn((String)"For PWM ID", ID);
	logger->WriteLn((String)"Value", value);
	switch (cmd) {
	case Channel::Cmd_SetCurrValue:
		SetValue(value);
		/*if (value == minValue) {
		Off();
		}
		else {
		On();
		}*/
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

bool ChannelPwm_Base::IsOn()
{
	return (currentValue > 0);
}
bool ChannelPwm_Base::IsOff()
{
	return (currentValue == 0);

}

void ChannelPwm_Base::SetValue(int value) {

	if (value > maxValue) {
		value = maxValue;
	}
	else if (value < minValue) {
		value = minValue;
	}
	currentValue = value;
	pwm->setPWM(pin, 0, value);

	//if (value > maxValue) {
	//	value = maxValue;
	//} else if (value < minValue) {
	//	value = minValue;
	//}
	//currentValue = value;
	//pwm->setPWM(pin, 0, value);

//	if (value > minValue) {
//		On();
//	}
//	else {
//		Off();
//	}
}

int ChannelPwm_Base::SetValuePercentage(int value) {
	int range = (maxValue - minValue);

	logger->WriteLn("Percent Val", value);
	logger->WriteLn("Set Val", int(value / 100.0 * range) + minValue);
	SetValue(int(value / 100.0 * range) + minValue); //percent of range + base value (minValue)
}