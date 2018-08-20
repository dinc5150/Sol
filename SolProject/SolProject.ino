#include "ChannelPwm_Base.h"
#include "MqttObj.h"
#include "GlobalConst.h"
#include "Log.h"
#include "Settings.h"
#include "MqttCmd.h"
#include "Ethernet.h"
#include "SPI.h"
#include "SD.h"
#include "External Libs\pubsubclient-master\src\PubSubClient.h"
#include "Wire.h"
#include "External Libs\Adafruit-PWM-Servo-Driver-Library-master\Adafruit_PWMServoDriver.h"
#include "MemoryFree.h"
#include "OneButton.h"
#include "Trigger.h"
#include "TriggerBtn.h"
#include "Channel.h"
#include "ChannelLight.h"
#include "ChannelPwmLightDimmable.h"



//#define TOTAL_CHANNELS = 2;


//MqttObj * MqttObjects[TOTAL_CHANNELS + TOTAL_TRIGGERS];
Channel * channels[TOTAL_CHANNELS];


Trigger * triggers[TOTAL_TRIGGERS];

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);






EthernetClient ethClient;

MqttCmd MqttCmdHelper;


void callback(char* topic, byte* payload, unsigned int length) {
	MqttCmdHelper.callback(topic, payload, length);
	/*char value[100];
	Serial.println("Callback");
	Serial.print("topic: "); Serial.println(topic);
	Serial.print("length: "); Serial.println(length);

	Serial.print("payload: "); Serial.println(atoi((char*)payload));

	Serial.println();


	if (strcmp(topic, "/house/lights/1/com") == 0) {
	channels[1]->Cmd(Channel::Cmd_SetCurrValue, atoi((char*)payload));
	}*/
	/*if (strcmp(topic, "/home/1/ard1/p1/com") == 0) {
	if (payload[0] == '0')
	{
	digitalWrite(4, LOW);
	lcd.home();
	lcd.clear();
	lcd.write((uint8_t)1);
	lcd.print("Turning Fan OFF");
	delay(100);
	client.publish("/home/1/ard1/p1/state", "0");
	}
	else if (payload[0] == '1')
	{
	digitalWrite(4, HIGH);
	lcd.home();
	lcd.clear();
	lcd.write((uint8_t)1);
	lcd.print("Turning Fan ON");
	delay(100);
	client.publish("/home/1/ard1/p1/state", "1");
	}
	}

	if (strcmp(topic, "/home/1/ard1/p2/com") == 0) {
	if (payload[0] == '0')
	{
	digitalWrite(5, LOW);
	lcd.home();
	lcd.clear();
	lcd.write((uint8_t)1);
	lcd.print("Turning Light OFF");
	delay(100);
	client.publish("/home/1/ard1/p2/state", "0");
	}
	else if (payload[0] == '1')
	{
	digitalWrite(5, HIGH);
	lcd.home();
	lcd.clear();
	lcd.write((uint8_t)1);
	lcd.print("Turning Light ON");
	delay(100);
	client.publish("/home/1/ard1/p2/state", "1");
	}
	}*/


}



PubSubClient MqttClient(MQTT_SERVER_IP, MQTT_SERVER_PORT, callback, ethClient);
//PubSubClient * MqttClient;

static Log * logger = new Log();

byte Total_Triggers = 0;
byte Total_Channels = 0;




void setup() {
	//delay(5000);
	Serial.begin(115200);
	delay(5000);
	
	logger->WriteLn((String)"Memory Start = ", freeMemory());


	if (!SD.begin(4)) {
		logger->WriteLn((String)"SD Card initialisation failed!");
		//LOG_TO_FILE = false;
		logger->logToFile(false);
	}
	//delay(5000);
	logger->WriteLn((String)"Booting");

	MqttCmdHelper.MqttClient = &MqttClient;

	Settings.init(channels, triggers, Total_Triggers, Total_Channels, &pwm, &MqttCmdHelper, logger);
	delay(1000);
	logger->WriteLn((String)"Device Name", DEVICE_NAME);

	Ethernet.begin(MAC, IP);
	
	logger->WriteLn((String)"Ethernet Initialised");



	//if (client.connect("arduinoClient")) {
	//	
	//	Serial.println("MTQQected");
	//	client.publish("outTopic", "hello world");
	//	client.subscribe("/house/#");  // Subscribe to all messages for this device
	//}

	pwm.begin();
	pwm.setPWMFreq(40); //A number representing the frequency in Hz, between 40 and 1000

	//pwm.reset(); //resets all pins to 0

	//channels[0] = new ChannelLight(6);
	//channels[1] = new ChannelLight(13);


	//triggers[0] = new TriggerBtn(0, 7, 1, &MqttCmdHelper);
	//triggers[0]->channels[0] = channels[0];
	//triggers[0]->channels[1] = channels[1];



	for (int i = 0; i < TOTAL_CHANNELS; ++i) {
		MqttCmdHelper.mychannels[i] = channels[i];
	}
	
	logger->WriteLn((String)"freeMemory = ", freeMemory());

	logger->WriteLn((String)"READY");


}



// the loop function runs over and over again forever
void loop() {

	MqttCmdHelper.loop();
	for (byte i = 0; i < Total_Triggers; i++) {
		triggers[i]->loop();
	}
	//logger->WriteLn("TotalTriggers", Total_Triggers);
	
	//delay(10000);
	//pwm.setPWM(7, 0, 4095);
	//delay(1000);

	//pwm.setPWM(7, 4096, 0);
	//delay(1000);
	//pwm.setPWM(7, 2000, 0);
	//delay(10);
	//Serial.println("loop");
	delay(10);
}
