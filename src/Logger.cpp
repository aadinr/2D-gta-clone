#include "Logger.h"

CLogger::CLogger() {
	FileName = "log.txt";
	FileState = false;
	IsDST = 0;
	HourForward = 0;
}

CLogger::~CLogger() {
	LogFile.close();
	FileState = false;
	return true;
}

bool CLogger::OpenLog(std::string FileName, bool IsDST) {
	LogFile.open(FileName.c_str());
	FileState = true;

	this->IsDST = IsDST;
	if(IsDST == true) HourForward = 2;
	if(IsDST == false) HourForward = 1;

	if(LogFile != NULL) return true;
	else return false;
}

void CLogger::ChangeLogFile(std::string FileName) {
	CloseLog();
	OpenLog(FileName, IsDST);
}

bool CLogger::Log(std::string Message) {
	// check if log file is opened
	if(FileState == false) return false;

	time_t RawTime = time(0);
	tm Time;

	gmtime_s(&Time, &RawTime);

	// log current time
	if((Time.tm_hour + HourForward % 24) < 10) LogFile << "0" << ((Time.tm_hour + HourForward) % 24);
	if((Time.tm_hour + HourForward % 24) >= 10) LogFile << ((Time.tm_hour + HourForward) % 24);
	LogFile << ":";
	if(Time.tm_min < 10) LogFile << "0" << Time.tm_min;
	if(Time.tm_min >=10) LogFile << Time.tm_min;
	LogFile << ":";
	if(Time.tm_sec < 10) LogFile << "0" << Time.tm_sec;
	if(Time.tm_sec >= 10) LogFile << Time.tm_sec;
	LogFile << ": ";

	LogFile << Message << std::endl;
	LogFile.flush();

	return true;
}