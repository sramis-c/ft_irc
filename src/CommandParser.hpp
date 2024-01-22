#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>

#pragma once

enum TokenType{PREFIX, COMMAND, PARAMETER, MESSAGE, ERROR};
enum IRCCommand{USER, NICK, PRIVMSG, JOIN, UNKNOWN}; //Pointers to functions?

struct Token
{
	TokenType	type;
	std::string	value;
};

class CommandParser
{
	private:
		IRCCommand 					_command;
		std::vector<std::string>	_parameters;
		std::string					_message;

		void						processToken(Token token);
		
		//Utils
		IRCCommand					stringToCommand(std::string);
		std::vector<std::string>	splitString(std::string);

	public:
		CommandParser();
		~CommandParser();
		
		void		parse(std::string message);

		//Getters
		IRCCommand					getCommand(void);
		std::vector<std::string>	getParameters(void);
		std::string					getMessage(void);
};