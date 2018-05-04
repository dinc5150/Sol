// 
// 
// 

#include "Log.h"


Log::Log() {}

void Log::WriteLn(String name, int value) {
	char buffer[MAX_STRING_LENGTH];
	name.toCharArray(buffer, MAX_STRING_LENGTH);
	WriteLn(buffer, value);
}

void Log::WriteLn(char name[], int value) {
	char buffer[MAX_STRING_LENGTH];
	sprintf(buffer, "%s: %d", name, value);

	WriteLn(buffer);
}

void Log::WriteLn(String name, char value[]) {
	char buffer[MAX_STRING_LENGTH];
	name.toCharArray(buffer, MAX_STRING_LENGTH);
	WriteLn(buffer, value);
}
//void Log::WriteLn(String name, bool value) {
//	char buffer[MAX_STRING_LENGTH];
//	name.toCharArray(buffer, MAX_STRING_LENGTH);
//	WriteLn(buffer, value);
//}
//void Log::WriteLn(char name[], bool value) {
//	char buffer[MAX_STRING_LENGTH];
//	name.toCharArray(buffer, MAX_STRING_LENGTH);
//	WriteLn(buffer, value);
//}

void Log::WriteLn(char name[], char value[]) {
	char buffer[MAX_STRING_LENGTH];
	sprintf(buffer, "%s: %s", name, value);

	WriteLn(buffer);
}

void Log::WriteLn(char name[], String value) {
	char buffer[MAX_STRING_LENGTH];
	value.toCharArray(buffer, MAX_STRING_LENGTH);
	Write(name);
	Write(": ");
	WriteLn(buffer);
}

void Log::Write(String value) {
	
	char buffer[MAX_STRING_LENGTH];
	value.toCharArray(buffer, MAX_STRING_LENGTH);
	writeToSerial(buffer, false);
	writeToFile(buffer, false);
}

void Log::Write(int value) {
	char buffer[MAX_STRING_LENGTH];
	sprintf(buffer, "%d", value);
	writeToSerial(buffer, false);
	writeToFile(buffer, false);
}

void Log::Write(char value[]) {
	writeToSerial(value, false);
	writeToFile(value, false);
}

void Log::WriteLn(String value) {
	char buffer[MAX_STRING_LENGTH];
	value.toCharArray(buffer, MAX_STRING_LENGTH);
	writeToSerial(buffer, true);
	writeToFile(buffer, true);
}

void Log::WriteLn(char value[]) {
	writeToSerial(value, true);
	writeToFile(value, true);
}


void Log::writeToFile(char value[], bool LineEnding) {
	if (!PauseLogToFile && logToFile()) {
		File dataFile = SD.open(LOGFILE, FILE_WRITE);
		if (dataFile) {
			if (LineEnding) {
				dataFile.println(value);
			}
			else {
				dataFile.print(value);
			}
			dataFile.close();
		}
		else {
			// if the file isn't open, pop up an error:
			logToFile(false);
			writeToSerial((String)"Cant write to SD Card", true);
		}
	}
}

void Log::writeToSerial(String value, bool LineEnding) {
	char buffer[MAX_STRING_LENGTH];
	value.toCharArray(buffer, MAX_STRING_LENGTH);
	writeToSerial(buffer, LineEnding);
}
void Log::writeToSerial(char value[], bool LineEnding) {
	if (logToSerial() && Serial) { //Check log flag and if port is open
		if (LineEnding) {
			Serial.println(value);
		}
		else {

			Serial.print(value);
		}
	}
}

bool Log::logToFile()
{
	return _logToFile;
}

bool Log::logToFile(bool shouldILog)
{
	_logToFile = shouldILog;
	return _logToFile;
}

bool Log::logToSerial()
{
	return _logToSerial;
}

bool Log::logToSerial(bool shouldILog)
{
	_logToSerial = shouldILog;
	return _logToSerial;
}

//LogClass Log;

