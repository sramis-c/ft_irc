#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "User.hpp"
#include "CommandParser.hpp"
#include "CommandInvoker.hpp"
#include "Command.hpp"
#include "Replies.hpp"
#include <sstream>

class ClientManager : public IChannelObserver
{
	private:
		CommandParser	_parser;
		CommandInvoker	_invoker;

		std::map<int, User*> 				_users;
		std::map<std::string, Channel*>		_channels;

		std::string		_reply;

		

	public:
		ClientManager();
		~ClientManager();

		void		handleRequest(int fd, std::string message);
		void		onChannelCreationRequest(const std::string& channelName, User* user);

		
		void		setReply(int num);
		
		std::string			getReply();
		std::string			formatReply(std::string reply, int fd);
};