// 
// 
// 

#include "ChannelPwmLightDimmable.h"


ChannelPwmLightDimmable::ChannelPwmLightDimmable(byte _pin, Log * _logger, char id[], Adafruit_PWMServoDriver * _pwm) : ChannelPwm_Base::ChannelPwm_Base(_pin, _logger, id, _pwm){
	//pwm = _pwm;
	//maxValue = 4095;
	Serial.print("PWMDimmable Channel Created: ");
	//Serial.println(_pin);
}


//void ChannelPwmDimmable::SetValue(int value) {
//
//	if (value > maxValue) {
//		value = maxValue;
//	} else if (value < minValue) {
//		value = minValue;
//	}
//	currentValue = value;
//	pwm->setPWM(pin, 0, value);
//
//}
