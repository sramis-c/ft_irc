#include "ArgParser.hpp"
#include "Logger.hpp"
#include "Server.hpp"

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <csignal>
#include <poll.h>

int main(int argc, char **argv)
{
	MyArgParse::ArgParser parse(argc, argv);
	std::map<std::string, std::string> config;
	irc::Server server;
	Log::Logger logger((std::string(argv[0])));

	parse.addArgument("port", "Is the port number on which your server will accept incoming connections", true);
	parse.addArgument("password", "Is the password needed by any IRC client who wants to connect to your server", true);
	try{
		config = parse.parse();
	}catch (std::exception &e){
		std::cerr << e.what() << '\n';
		return(EXIT_FAILURE);
	}

	std::cout << "config: " << std::endl;
	for (std::map<std::string, std::string>::iterator it = config.begin(); it != config.end(); ++it)
		std::cout << "  "<< it->first << " = " << it->second << std::endl;
	server.init(config, logger);
	server.run();
	return(0);
}
