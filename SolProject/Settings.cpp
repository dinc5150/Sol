// 
// 
// 

#include "Settings.h"

void SettingsClass::init(Channel * channels[], Trigger * triggers[], byte &Total_Triggers, byte &Total_Channels, Adafruit_PWMServoDriver * pwm, MqttCmd * MqttCmdHelper, Log * logger) {

	logger->Write("Opening Settings.ini file...");
	logger->PauseLogToFile = true;
	myFile = SD.open("settings.ini");

	if (myFile) {
		logger->WriteLn("Success");
		byte lineSection = 0;
		char character;
		String sType;
#define TOTALOPTIONS 7
		String sOptions[TOTALOPTIONS];


		// read from the file until there's nothing else in it:
		while (myFile.available()) {
			character = myFile.read();

			if (character == ' ') {
				//Skip Spaces
			} else if (character == '/') {
				logger->WriteLn(myFile.readStringUntil('\n'));
			} else {
				if (lineSection == 0 && character == '[') {
					//Reset all variables
					sType = "";
					for (int i = 0; i < TOTALOPTIONS; i++) {
						sOptions[i] = "";
					}
					lineSection++;
				} else if (lineSection == 1 && character != ',') {
					sType = sType + character;
				} else if (lineSection == 1 && character == ',') {
					logger->WriteLn("sType", sType);

					lineSection++;
				} else if (lineSection > 1) {

					if (character == ']') {
						logger->Write("Option ");
						logger->Write(lineSection - 2);
						logger->Write(": ");
						logger->WriteLn(sOptions[lineSection - 2]);
						Serial.println(sType);

						//Finished reading line
						if (sType == "debug") {
							//LOG_TO_SERIAL = toBoolean(sOptions[0]);
							//LOG_TO_FILE = toBoolean(sOptions[1]);
							logger->logToSerial(toBoolean(sOptions[0]));
							logger->logToFile(toBoolean(sOptions[1]));
						} else if (sType == "light") {
							//Create a light
							char ObjId[20];
							strcpy(ObjId, sOptions[2].c_str());
							channels[sOptions[0].toInt()] = new ChannelLight(sOptions[1].toInt(), logger, ObjId);
							MqttCmdHelper->AddMqttObject(channels[sOptions[0].toInt()]);
							Total_Channels++;
						}
						else if (sType == "pwm") {
							//Create a light
							char ObjId[20];
							strcpy(ObjId, sOptions[2].c_str());
							channels[sOptions[0].toInt()] = new ChannelPwm_Base(sOptions[1].toInt(), logger, ObjId, pwm);
							MqttCmdHelper->AddMqttObject(channels[sOptions[0].toInt()]);
							Total_Channels++;
						}else if (sType == "pwmLightDim") {
							//Create a light
							char ObjId[20];
							strcpy(ObjId, sOptions[2].c_str());
							channels[sOptions[0].toInt()] = new ChannelPwmLightDimmable(sOptions[1].toInt(), logger, ObjId, pwm);
							MqttCmdHelper->AddMqttObject(channels[sOptions[0].toInt()]);
							Total_Channels++;
						}else if (sType == "btn") {
							//create a Button
							triggers[sOptions[0].toInt()] = new TriggerBtn(sOptions[0].toInt(), sOptions[1].toInt(), "THISNEEDSTOBEUNIQUE", MqttCmdHelper, logger);
							Total_Triggers++;
						} else if (sType == "addChannel") {
							//Add a channel to a trigger
							triggers[sOptions[0].toInt()]->AddChannel(channels[sOptions[1].toInt()]);
						} else if (sType == "addFeedback") {
							//Add a channel to a trigger
							//triggers[sOptions[1].toInt()]->feedbackChannels[sOptions[0].toInt()] = channels[sOptions[2].toInt()];
							triggers[sOptions[0].toInt()]->AddFeedbackChannel(channels[sOptions[1].toInt()]);
						} else if (sType == "network") {
							//Add a channel to a trigger
							triggers[sOptions[1].toInt()]->channels[sOptions[0].toInt()] = channels[sOptions[2].toInt()];
						} else if (sType == "mqttIp") {

							MQTT_SERVER_IP[0] = sOptions[0].toInt();
							MQTT_SERVER_IP[1] = sOptions[1].toInt();
							MQTT_SERVER_IP[2] = sOptions[2].toInt();
							MQTT_SERVER_IP[3] = sOptions[3].toInt();
							MQTT_SERVER_PORT = sOptions[4].toInt();
							MqttCmdHelper->MqttClient->setServer(IPAddress(MQTT_SERVER_IP[0], MQTT_SERVER_IP[1], MQTT_SERVER_IP[2], MQTT_SERVER_IP[3]), MQTT_SERVER_PORT);
							
						} else if (sType == "ip") {
							IP[0] = sOptions[0].toInt();
							IP[1] = sOptions[1].toInt();
							IP[2] = sOptions[2].toInt();
							IP[3] = sOptions[3].toInt();
						} else if (sType == "mac") {
							MAC[0] = sOptions[0].toInt();
							MAC[1] = sOptions[1].toInt();
							MAC[2] = sOptions[2].toInt();
							MAC[3] = sOptions[3].toInt();
							MAC[4] = sOptions[4].toInt();
							MAC[5] = sOptions[5].toInt();
						}
						else {
							Serial.print("UnknownType: ");
							Serial.println(sType);
						}

						lineSection = 0;
					} else if (character == ',') {
						logger->Write("Option ");
						logger->Write(lineSection - 2);
						logger->Write(": ");
						logger->WriteLn(sOptions[lineSection - 2]);
						lineSection++;
					} else {
						sOptions[lineSection - 2] = sOptions[lineSection - 2] + character;
					}


				}
			}
		}



		// close the file:
		myFile.close();
		logger->PauseLogToFile = false;
	} else {
		logger->PauseLogToFile = false;
		// if the file didn't open, print an error:
		logger->WriteLn("Failed");

		logger->WriteLn("Could not open settings.ini. Loading Defaults");
		logger->WriteLn("Light pin 13 and button pin 6");



		channels[0] = new ChannelLight(13, logger, "TEMP");
		MqttCmdHelper->AddMqttObject(channels[0]);
		Total_Channels++;
		triggers[0] = new TriggerBtn(0,8, "THISNEEDSTOBEUNIQUE", MqttCmdHelper, logger);
		Total_Triggers++;
		triggers[0]->AddChannel(channels[0]);

		channels[2] = new ChannelLight(12, logger, "TEMP");
		MqttCmdHelper->AddMqttObject(channels[2]);
		Total_Channels++;
		triggers[0]->AddFeedbackChannel(channels[2]);


		
		channels[1] = new ChannelPwmLightDimmable(14, logger, "light14", pwm);
		MqttCmdHelper->AddMqttObject(channels[1]);
		Total_Channels++;
		triggers[1] = new TriggerBtn(1, 7, "THISNEEDSTOBEUNIQUE2", MqttCmdHelper, logger);
		Total_Triggers++;
		triggers[1]->AddChannel(channels[1]);

		

	}


}


// converting string to Float
float SettingsClass::toFloat(String settingValue) {
	char * floatbuf = new char[settingValue.length() + 1]();
	settingValue.toCharArray(floatbuf, settingValue.length() + 1);
	float f = atof(floatbuf);
	delete[] floatbuf; //Dispose of dynamic array
	return f;
}

long SettingsClass::toLong(String settingValue) {

	char * longbuf = new char[settingValue.length() + 1]();
	settingValue.toCharArray(longbuf, settingValue.length() + 1);
	long l = atol(longbuf);
	delete[] longbuf; //Dispose of dynamic array
	return l;
}




// Converting String to integer and then to boolean
// 1 = true
// 0 = false
boolean SettingsClass::toBoolean(String settingValue) {
	if (settingValue.toInt() == 1) {
		return true;
	} else {
		return false;
	}
}




SettingsClass Settings;

