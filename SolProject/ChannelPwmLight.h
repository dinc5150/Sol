// ChannelPwm.h

#ifndef _CHANNELPWMLIGHT_h
#define _CHANNELPWMLIGHT_h

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

#include "Adafruit_PWMServoDriver.h";//Adafruit_PWMServoDriver.h"

class ChannelPwmLight : public ChannelPwm_Base, Channel

{
protected:
	Adafruit_PWMServoDriver * pwm = NULL;

public:
	ChannelPwmLight(byte _pin, Log * _logger, char id[], Adafruit_PWMServoDriver * _pwm);

	virtual void SetValue(int value);




};
#endif

