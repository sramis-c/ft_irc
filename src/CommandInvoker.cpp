#include "CommandInvoker.hpp"

CommandInvoker::CommandInvoker()
{}

CommandInvoker::~CommandInvoker()
{
}

void	CommandInvoker::setCommand(ITarget* user,int fd, CommandParser& parser, std::map<int, User*>& users, std::map<std::string, Channel*>& channels)
{
	(void)channels;
	std::vector<std::string> parameters = parser.getParameters();
	std::string message = parser.getMessage();
	switch(parser.getCommand())
	{
		case USER:
		{
			this->_command = new UserCommand(parameters, message);
			break;
		}
		case NICK:
		{
			this->_command = new NickCommand(parameters, message);
			break;
		}
		case PRIVMSG:
		{
			this->_targets.push_back(parameters[0]);
			this->_command = new PrivMsgCommand(parameters, message);
			break;
		}
		case JOIN:
		{
			this->_command = new JoinCommand(parameters, message);
			this->_targets.push_back(parameters[0]);
			break;
		}
		case UNKNOWN: //TODO
		{
			this->_command = new UnknownCommand(parameters, message);
			break;
		}
	}
}

User*    CommandInvoker::findTarget(std::string name, std::map<int, User*>& usermap)
{
    User*                           result;
	std::map<int, User*>::iterator  it;

	for (it = usermap.begin(); it != usermap.end(); it++)
	{
		if (it->second->getNickname() == name)
		{
			result = it->second;
			return (result);
		}
		else
            result = NULL;
	}
	return (result);
}

Channel*    CommandInvoker::findTarget(std::string name, std::map<std::string, Channel*>& channelmap)
{
    Channel*                           result;
	std::map<std::string, Channel*>::iterator  it;

	result = NULL;
	for (it = channelmap.begin(); it != channelmap.end(); it++)
	{
		if (it->first == name)
		{
			result = it->second;
			return (result);
		}
		else
            result = NULL;
	}
	return (result);
}

int		CommandInvoker::executeCommand()
{
	this->_RPLnumeric = 0;
	if ((this->_RPLnumeric = this->_command->validate()) == 0)
		this->_RPLnumeric = this->_command->execute();
	delete (this->_command);
	return(this->_RPLnumeric);
}