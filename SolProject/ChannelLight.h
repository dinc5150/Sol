// ChannelLight.h

#ifndef _CHANNELLIGHT_h
#define _CHANNELLIGHT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#ifndef _CHANNEL_h
#include "Channel.h"
#endif


class ChannelLight : public Channel
{
 protected:


 public:
	 ChannelLight(byte _pin, Log * _logger, char id[]);
	
	 //virtual void On();
	 //virtual void Off();

	 

	 

	

	 // void Cmd(int cmd, int Value);
};



#endif

