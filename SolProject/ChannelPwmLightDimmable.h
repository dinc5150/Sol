// ChannelPwmLightDimmable.h

#ifndef _CHANNELPWMLIGHTDIMMABLE_h
#define _CHANNELPWMLIGHTDIMMABLE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef _CHANNEL_h
#include "Channel.h"
#endif


#ifndef _CHANNELPWMBASE_h
#include "ChannelPwm_Base.h"
#endif

#include "External Libs\Adafruit-PWM-Servo-Driver-Library-master\Adafruit_PWMServoDriver.h";

class ChannelPwmLightDimmable : public ChannelPwm_Base{

protected:
	//Adafruit_PWMServoDriver * pwm = NULL;

public:
	ChannelPwmLightDimmable(byte _pin, Log * _logger, char id[], Adafruit_PWMServoDriver * _pwm);
	//virtual void SetValue(int value);
};


#endif