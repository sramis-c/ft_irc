#include "CommandParser.hpp"

CommandParser::CommandParser()
{}

CommandParser::~CommandParser()
{}

void		CommandParser::parse(std::string message)
{
	std::istringstream iss(message);
	Token token;

	//Parse command
	iss >> token.value;
	token.type = COMMAND;
	processToken(token);

	//Parse arguments
	std::getline(iss, token.value, ':');
	token.type = PARAMETER;
	processToken(token);

	//Parse nessage
	std::getline(iss, token.value);
	token.type = MESSAGE;
	processToken(token);
}

void		CommandParser::processToken(Token token)
{
	switch(token.type)
	{
		case COMMAND:
			this->_command = stringToCommand(token.value);
			break;
		case PARAMETER:
			this->_parameters = splitString(token.value);
			break;
		case MESSAGE:
			this->_message = token.value;
			break;
		default:
			break;
	}
}

//Getters

IRCCommand					CommandParser::getCommand(void)
{
	return(this->_command);
}

std::vector<std::string>	CommandParser::getParameters(void)
{
	return(this->_parameters);
}

std::string					CommandParser::getMessage(void)
{
	return(this->_message);
}

//Utils

IRCCommand					CommandParser::stringToCommand(std::string str)
{
	static const std::pair<const char*, IRCCommand> commandPairs[] = {
        std::make_pair("USER", USER),
        std::make_pair("NICK", NICK),
		std::make_pair("PRIVMSG", PRIVMSG),
		std::make_pair("JOIN", JOIN)
        //Add more commands
    };
    const size_t numCommands = sizeof(commandPairs) / sizeof(commandPairs[0]);

    for (size_t i = 0; i < numCommands; ++i)
	{
        if (commandPairs[i].first == str)
            return commandPairs[i].second;
    }
    return UNKNOWN;
}

std::vector<std::string>	CommandParser::splitString(std::string str)
{
	std::vector<std::string> params;
    std::istringstream iss(str);

    std::string token;
    while (iss >> token)
        params.push_back(token);

    return params;
}
