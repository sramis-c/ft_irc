#pragma once

#include "Command.hpp"
#include <vector>

class CommandInvoker
{
	private:
		Command*					_command;
		std::vector<std::string>	_targets;
		int							_RPLnumeric;

	public:
		CommandInvoker();
		~CommandInvoker();

		void	setCommand(ITarget* user, int fd, CommandParser& parser, std::map<int, User*>& users, std::map<std::string, Channel*>& channels);
        User*  	findTarget(std::string name, std::map<int, User*>& usermap);
        Channel*   findTarget(std::string name, std::map<std::string, Channel*>& channelmap);		
		int		executeCommand();

		std::vector<std::string>	getTargets(void)const{return(this->_targets);}
};