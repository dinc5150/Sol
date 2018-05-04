// Log.h

#ifndef _LOG_h
#define _LOG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SD.h>
//#include "GlobalConst.h"
#define LOGFILE "datalog.txt"
#define LOG_TO_FILE_ON_BOOT = false;
#define LOG_TO_SERIAL_ON_BOOT = true;
const int MAX_STRING_LENGTH = 255;

class Log
{
 protected:
	 
	 bool _logToFile;
	 bool _logToSerial;
	 void writeToFile(char value[], bool LineEnding);
	 void writeToSerial(String value, bool LineEnding);
	 void writeToSerial(char value[], bool LineEnding);

 public:
	 Log();

	 void WriteLn(String name, int value);
	 
	 bool logToFile();
	 bool logToFile(bool LogToFile);
	 bool logToSerial();
	 bool logToSerial(bool shouldILog);

	 bool PauseLogToFile = false;
	 
	void init();

	void Write(String value);
	void WriteLn(String value);

	void WriteLn(char name[], int value);

	void WriteLn(String name, char value[]);

	void WriteLn(String name, bool value);

	void WriteLn(char name[], char value[]);

	void WriteLn(char name[], String value);
	

	void Write(int value);



	void Write(char value[]);

	void WriteLn(char value[]);


	
};

//extern LogClass Log;

#endif

