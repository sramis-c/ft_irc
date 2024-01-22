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
		Command(User* user, std::vector<std::string> parameters, std::string message) : _user(user), _parameters(parameters), _message(message){};
		virtual ~Command(){};

		virtual int		execute() = 0;
		virtual int		validate() = 0;
	
	protected:
		User*						_user;
		std::vector<std::string>	_parameters;
		std::string					_message;
};

class UserCommand : public Command
{
	private:

	public:
		UserCommand(User* user, std::vector<std::string> parameters, std::string message) : Command(user, parameters, message){};
		~UserCommand();

		int		execute();
		int		validate();
};

class NickCommand : public Command
{
	private:

	public:
		NickCommand(User* user, std::vector<std::string> parameters, std::string message) : Command(user, parameters, message){};
		~NickCommand();

		int		execute();
		int		validate();
};

class PrivMsgCommand : public Command
{
	private:
		User*		_target;

	public:
		PrivMsgCommand(User* user, std::vector<std::string> parameters, std::string message);
		~PrivMsgCommand();

		int		execute();
		int		validate();

		void	setTarget(User* target);
};

class JoinCommand : public Command
{
	private:
		Channel*		_target;
		IChannelObserver*	_observer;

	public:
		JoinCommand(User* user, std::vector<std::string> parameters, std::string message) : Command(user, parameters, message){};
		~JoinCommand();

		int	execute();
		int	validate();

		void	setTarget(Channel* target);
		void	setObserver(IChannelObserver* observer);
};

/*Temporary*/
class UnknownCommand : public Command
{
	private:

	public:
		UnknownCommand(User* user, std::vector<std::string> parameters, std::string message) : Command(user, parameters, message){};
		int		execute(){std::cout << "UNKNOWN command" << std::endl; return(0);} //TODO
		int		validate(){return(0);} //TODO
};