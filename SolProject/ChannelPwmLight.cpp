// Turns the Channel On or Off without Dimming Capabilities
// To Dim use ChannelPwmDimmable instead
// 

#include "ChannelPwmLight.h"


ChannelPwmLight::ChannelPwmLight(byte _pin, Log * _logger, char id[], Adafruit_PWMServoDriver * _pwm) : ChannelPwm_Base::ChannelPwm_Base(_pin, _logger, id, _pwm), Channel::Channel(_pin, _logger, id) {
	//pwm = _pwm;
	//maxValue = 4095;
	Serial.print("PWMLight Channel Created: ");
	//Serial.println(_pin);
}

//void ChannelPwm::On() {
//	currentValue = maxValue;
//	pwm->setPWM(pin, 0, maxValue);
//	//logger->WriteLn("On", ID);
//}
//void ChannelPwm::Off() {
//	currentValue = minValue;
//	pwm->setPWM(pin, 0, minValue);
//	//logger->WriteLn("Off", ID);
//}

//void ChannelPwm::Cmd(int cmd, int value)
//{
//	logger->WriteLn("Command ID", cmd);
//	logger->WriteLn((String)"For PWM ID", ID);
//	logger->WriteLn((String)"Value", value);
//	switch (cmd) {
//	case Channel::Cmd_SetCurrValue:
//		SetValue(value);
//		/*if (value == minValue) {
//		Off();
//		}
//		else {
//		On();
//		}*/
//		break;
//	case Channel::Cmd_SetCurrPercentage:
//		SetValuePercentage(value);
//		break;
//	default:
//
//		logger->Write(cmd);
//		logger->WriteLn("", value);
//		break;
//	}
//}

//bool ChannelPwm::IsOn()
//{
//	return (currentValue > 0);
//}
//bool ChannelPwm::IsOff()
//{
//	return (currentValue == 0);
//}

void ChannelPwmLight::SetValue(int value) {
	
	/*if (value > maxValue) {
		value = maxValue;
	} else if (value < minValue) {
		value = minValue;
	}
	currentValue = value;
	pwm->setPWM(pin, 0, value);*/

	if (value > minValue) {
		On();
	}
	else {
		Off();
	}
}

//int ChannelPwm::SetValuePercentage(int value) {
//	int range = (maxValue - minValue);
//
//	logger->WriteLn("Percent Val", value);
//	logger->WriteLn("Set Val", int(value / 100.0 * range) + minValue);
//	SetValue(int(value / 100.0 * range) + minValue); //percent of range + base value (minValue)
//}