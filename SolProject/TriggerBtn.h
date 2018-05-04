// TriggerBtn.h

#ifndef _TRIGGERBTN_h
#define _TRIGGERBTN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#ifndef _TRIGGER_h
#include "Trigger.h"
#endif


#ifndef OneButton_h
#include "OneButton.h"
#endif


#include "MemoryFree.h"

class TriggerBtn: public Trigger
{
 protected:
	 //Button helloButton = Button(50, LOW);
	 OneButton * TheButton;

 public:


	 //TriggerBtn(int id, int _pin, byte _totalChannels, MqttCmd * _mqttCmdHelper, Log * logger);
	 
	 TriggerBtn(int _id, int _pin, char id[], MqttCmd * _mqttCmdHelper, Log * _logger);
	 void onClick();
	 void onDblClick();
	 void onLongPressStart();
	 void onLongPressStop();
	 virtual void loop();
	 virtual void CallEvent(int _event);





	
	 
};



#endif

