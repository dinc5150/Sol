// ChannelPwm_Base.h

#ifndef _CHANNELPWM_BASE_h
#define _CHANNELPWM_BASE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#ifndef _CHANNEL_h
#include "Channel.h"
#endif


#include "External Libs\Adafruit-PWM-Servo-Driver-Library-master\Adafruit_PWMServoDriver.h";
//#include "Adafruit-PWM-Servo-Driver-Library-master\Adafruit-PWM-Servo-Driver-Library-master\Adafruit_PWMServoDriver.h";

class ChannelPwm_Base : public Channel
{
protected:
	Adafruit_PWMServoDriver * pwm = NULL;

public:
	ChannelPwm_Base(byte _pin, Log * _logger, char id[], Adafruit_PWMServoDriver * _pwm);
	virtual void On();
	virtual void Off();
	virtual void Cmd(int cmd, int value);
	virtual bool IsOn();
	virtual bool IsOff();
	virtual void SetValue(int value);
	virtual int SetValuePercentage(int value);

};
#endif

