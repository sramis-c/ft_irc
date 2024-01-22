#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <sstream>

#pragma once

#define LOG_INF Info
#define LOG_WAR Warning
#define LOG_ERR Error

namespace Log
{
	enum logType{
		Info,
		Warning,
		Error
	};

	class Logger
	{
		private:
			std::string _filename;
			bool _outToFile;
			bool _outToTerminal;
			std::ofstream _outfile;

			std::string getTimeStamp() const;
			//logType type;

			std::string getLogType(logType type) const;
			void logToStream(std::ostream &stream, logType type, const std::string& message, const std::string& file, int line);

		public:
			Logger(const std::string& filename);
			Logger(Logger const &src);
			~Logger();
			Logger &operator=(Logger const &rhs);

			bool fileExists(const std::string &filename);
			std::string genLogFile(const std::string &base);

			void enableFileOutput();
			void enableTerminalOutput();

			void log(logType type, const std::string& message);
			void log(logType type, const std::string& message, const std::string file, const int line);

	};
}