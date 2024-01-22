#include "CommandInvoker.hpp"

CommandInvoker::CommandInvoker()
{}

CommandInvoker::~CommandInvoker()
{
}

void	CommandInvoker::setCommand(IChannelObserver* client,int fd, CommandParser& parser, std::map<int, User*>& users, std::map<std::string, Channel*>& channels)
{
	std::vector<std::string> parameters = parser.getParameters();
	std::string message = parser.getMessage();
	switch(parser.getCommand())
	{
		case USER:
		{
			this->_command = new UserCommand(users[fd], parameters, message);
			break;
		}
		case NICK:
		{
			this->_command = new NickCommand(users[fd], parameters, message);
			break;
		}
		case PRIVMSG:
		{
			this->_command = new PrivMsgCommand(users[fd], parameters, message);
			PrivMsgCommand* cmd = dynamic_cast<PrivMsgCommand*>(this->_command);
			cmd->setTarget(findTarget(parameters[0], users));
			break;
		}
		case JOIN:
		{
			this->_command = new JoinCommand(users[fd], parameters, message);
			JoinCommand* cmd = dynamic_cast<JoinCommand*>(this->_command);
			cmd->setTarget(findTarget(parameters[0], channels));
			cmd->setObserver(client);
			break;
		}
		case UNKNOWN: //TODO
		{
			this->_command = new UnknownCommand(users[fd], parameters, message);
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