#pragma once

#include "Command.hpp"
#include <vector>

class CommandInvoker
{
	private:
		Command*				_command;
		int				_RPLnumeric;

	public:
		CommandInvoker();
		~CommandInvoker();

		void	setCommand(IChannelObserver* client, int user, CommandParser& parser, std::map<int, User*>& users, std::map<std::string, Channel*>& channels);
        User*  	findTarget(std::string name, std::map<int, User*>& usermap);
        Channel*   findTarget(std::string name, std::map<std::string, Channel*>& channelmap);		
		int		executeCommand();

};