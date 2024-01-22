#include "../test.hpp"
#include <map>
#include <string>

int main(int argc, char **argv)
{
	MyArgParse::ArgParser parse(argc, argv);
	std::map<std::string, std::string> config;
	//parse.addSplitArgument("host:port_network:password_network", "" , 3, ':', false);
	//parse.addSplitArgument("host", "Is the hostname on which IRC must connect to join a already existing network", 1, ':', true);
	//parse.addSplitArgument("port_network", "is the server port on which IRC must connect to host", 2, ':', true);
	//parse.addSplitArgument("password_network", "is the password needed to connect on host", 3, ':', true);
	parse.addArgument("port", "Is the port number on which your server will accept incoming connections", true);
	parse.addArgument("password", "Is the password needed by any IRC client who wants to connect to your server", true);

	try{
		config = parse.parse();
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	for(std::map<std::string, std::string>::iterator it = config.begin(); it != config.end(); ++it)
		std::cout	<< std::left << "Key: " << std::setw(10) << it->first 
					<< std::left << std::setw(10) << "Value: " << it->second << std::endl;
	return (0);
}