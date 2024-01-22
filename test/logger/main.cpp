#include "../test.hpp"

using namespace Log;

class TestClass {
	public:
		TestClass() : logger("./log/testClass"){
			logger.enableTerminalOutput();
		};
		~TestClass()
		{
			//logger.~Logger();
		};
		void useLogger();

    	Logger logger;
};

void TestClass::useLogger() {
		logger.log(LOG_INF, "This is an informational message");
		logger.log(LOG_ERR, "This is an error message", __FILE__, __LINE__);
}

/*****************
	g++ main.cpp ../../src/logger.cpp 
*****************/

int main(int argc, char **argv)
{
	Logger logs("./log/poc");

	logs.enableTerminalOutput();
	logs.enableFileOutput();
	logs.log(Log::LOG_INF, "test1");
	logs.log(Log::LOG_WAR, "test2");
	logs.log(Log::LOG_ERR, "test3");
	logs.log(Log::LOG_INF, "test4", __FILE__, __LINE__);

	TestClass test;
	test.useLogger();
	test.useLogger();
	test.useLogger();
	
	return(0);
}

