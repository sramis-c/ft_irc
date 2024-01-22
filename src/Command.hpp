#pragma once

#include <string>
#include <vector>
#include <sys/socket.h>
#include "User.hpp"
#include "Channel.hpp"
#include "Replies.hpp"
#include "CommandParser.hpp"

class Command
{
	public:
		Command(std::vector<std::string> parameters, std::string message) : _parameters(parameters), _message(message){};
		virtual ~Command(){};

		virtual int		execute() = 0;
		virtual int		validate() = 0;

	protected:
		std::vector<ITarget*>		_targets;
		std::vector<std::string>	_parameters;
		std::string					_message;
};

class UserCommand : public Command
{
	private:

	public:
		UserCommand(std::vector<std::string> parameters, std::string message) : Command(parameters, message){};
		~UserCommand();

		int		execute();
		int		validate();
};

class NickCommand : public Command
{
	private:

	public:
		NickCommand(std::vector<std::string> parameters, std::string message) : Command(parameters, message){};
		~NickCommand();

		int		execute();
		int		validate();
};

class PrivMsgCommand : public Command
{
	private:

	public:
		PrivMsgCommand(std::vector<std::string> parameters, std::string message);
		~PrivMsgCommand();

		int		execute();
		int		validate();
};

class JoinCommand : public Command
{
	private:
		IChannelObserver*	_observer;

	public:
		JoinCommand(std::vector<std::string> parameters, std::string message) : Command(parameters, message){};
		~JoinCommand();

		int	execute();
		int	validate();

		void	setObserver(IChannelObserver* observer);
};

/*Temporary*/
class UnknownCommand : public Command
{
	private:

	public:
		UnknownCommand(std::vector<std::string> parameters, std::string message) : Command(parameters, message){};
		int		execute(){std::cout << "UNKNOWN command" << std::endl; return(0);} //TODO
		int		validate(){return(0);} //TODO
};