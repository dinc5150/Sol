// 
// 
// 

#include "MqttObj.h"

MqttObj::MqttObj(char * mqttID) {
	MqttID = mqttID;
}


void MqttObj::ExecuteCmd(int CmdType, byte * value) {
	//You need to override this function
	//Default CmdType is passed as null, so make sure you catch null as the default CMD

}



