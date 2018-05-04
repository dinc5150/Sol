
#include "ChannelLight.h"


ChannelLight::ChannelLight(byte _pin, Log * _logger, char id[]) : Channel::Channel(_pin, _logger, id){
	Serial.print("Light Created: ");
	Serial.println(_pin);
}







