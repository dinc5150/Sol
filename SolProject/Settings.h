// Settings.h

#ifndef _SETTINGS_h
#define _SETTINGS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SPI.h>
#include <SD.h>
#include "Log.h"
#include "Channel.h"
#include "Trigger.h"
#include "ChannelLight.h"
#include "ChannelPwm_Base.h"
#include "ChannelPwmLightDimmable.h"
//#include "ChannelPwmLight.h"
#include "TriggerBtn.h"
#include "External Libs\Adafruit-PWM-Servo-Driver-Library-master\Adafruit_PWMServoDriver.h";
class SettingsClass
{
 protected:
	 File myFile;
 public:


	


	
	

	
	
	
	void init(Channel * channels[], Trigger * triggers[], byte & Total_Triggers, byte & Total_Channels, Adafruit_PWMServoDriver * pwm, MqttCmd * MqttCmdHelper, Log * logger);

	float toFloat(String settingValue);

	long toLong(String settingValue);

	boolean toBoolean(String settingValue);


	
};

extern SettingsClass Settings;

#endif

