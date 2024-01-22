#include <string>
#include <iostream>
#include <cstdlib>

#pragma once

class User
{
	private:
		int			_id;

		std::string	_username;
		std::string	_nickname;
		std::string	_realname;
		int			_usermode;

		bool		_isRegistred;
		bool		_isWelcomed;

	public:
		User();
		User(const int id);
		User(const User& other);
		~User();

		User&	operator=(const User& rhs);

		//Getters
		int			getID(void) const;
		std::string	getUsername(void) const;
		std::string	getNickname(void) const;
		std::string	getRealname(void) const;
		int			getUsermode(void) const;
		bool		isRegistred(void) const;
		bool		isWelcomed(void) const;


		//Setters

		void	setUsername(std::string username);
		void	setNickname(std::string nickname);
		void	setRealname(std::string realname);
		void	setUsermode(std::string usermode);
		void	setRegistred(void);
		void	setWelcomed(void);
};