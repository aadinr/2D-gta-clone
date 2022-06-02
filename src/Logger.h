#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <time.h>

class CLogger {
	std::ofstream LogFile;
	std::string FileName;
	bool FileState;
	bool IsDST;
	int HourForward;

public:
	CLogger();
	~CLogger();
	bool OpenLog(std::string FileName, bool IsDST);
	bool CloseLog();
	void ChangeLogFile(std::string FileName);
	bool Log(std::string Message);
};

#endif