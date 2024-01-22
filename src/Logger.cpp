#include "Logger.hpp"


namespace Log
{
	Logger::Logger(const std::string& filename)
	{
		this->_outToFile = false;
		this->_outToTerminal = false;
		this->_filename = genLogFile(filename);
		this->_outfile.open(this->_filename.c_str());
	}

	Logger::~Logger()
	{
		this->log(Log::LOG_INF, "Stopped log system");
		if (this->_outfile.is_open())
			this->_outfile.close();
	}

	Logger::Logger(Logger const &src)
	{
		*this = src;
	}

	void Logger::logToStream(std::ostream &stream, logType type, const std::string& message, const std::string& file, int line)
	{
		stream << "[" << getTimeStamp() << "] "
			<< std::left <<  std::setw(10) << getLogType(type);
		if(!file.empty())
			stream << file ;
		if(line != 0)
			stream <<":"<< line << " ";
		stream << message << std::endl;
	}

	/**
	 * This function  use to print de debug log into file orand terminal
	 * @param logtype: logType: The type of debugo type defined in logger class as logType: Info Warning Error
	 * @param message: std::string: The message to print
	*/
	void Logger::log(logType type, const std::string &message)
	{
		if (this->_outToFile == true)
			logToStream(this->_outfile, type, message, "", 0);
		if (this->_outToTerminal == true)
			logToStream(std::cout, type, message, "", 0);
	}

	/**
	 * This function  use to print de debug log into file and terminal and the file.pp:line
	 * @param logtype: logType: The type of debugo type defined in logger class as logType: Info Warning Error
	 * @param message: std::string: The message to print
	 * @param file: const std::string: __FILE__
	 * @param line: const int: __LINE__
	*/

	void Logger::log(logType type, const std::string& message, const std::string file, const int line)
	{
		if (this->_outToFile == true)
			logToStream(this->_outfile, type, message, file, line);
		if (this->_outToTerminal == true)
			logToStream(std::cout, type, message, file, line);
	}

	std::string Logger::getTimeStamp() const
	{
		time_t		rawtime;
		struct tm	*timeinfo;
		char		buffer[21];
		std::string ret;

		time (&rawtime);
		timeinfo = localtime (&rawtime);
		strftime (buffer, 21, "%Y-%m-%d %H:%M:%S", timeinfo);
		ret = buffer;
		return ret;
	}

	bool Logger::fileExists(const std::string &filename)
	{
		std::ifstream file(filename.c_str());
		if(file.is_open() && file.good()){
			file.close();
			return (true);
		}
		return(false);
	}

	std::string Logger::genLogFile(const std::string & base)
	{
		std::string newName = base + ".log";
		int i = 0;
		while(this->fileExists(newName))
		{
			std::stringstream ss;
			ss << base << "-" << i << ".log";
			newName = ss.str();
			i++;
		}
		return (newName);

	}

	std::string Logger::getLogType(logType type) const
	{
		if (type == Log::LOG_INF)
			return "[INFO]";
		else if (type == Log::LOG_WAR)
			return "[WARNING]";
		else if (type == Log::LOG_ERR) 
			return "[ERROR]";	
		return "[UNK]";
	}

	void Logger::enableFileOutput(){
		this->_outToFile = true;
	}

	void Logger::enableTerminalOutput(){
		this->_outToTerminal = true;
	}

	Logger& Logger::operator=(Logger const &rhs)
	{
		this->_filename = rhs._filename;
		//this->_outfile = rhs._outfile;
		this->_outToTerminal = rhs._outToTerminal;
		this->_outToFile = rhs._outToFile;
		return (*this);
	}

}