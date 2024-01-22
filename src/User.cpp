#include "User.hpp"

User::User() : _isRegistred(false), _isWelcomed(false)
{
	std::cout << "User created" << std::endl;
}

User::User(const int id) : _id(id), _isRegistred(false), _isWelcomed(false)
{
	std::cout << "User [" << id << "] created" << std::endl;
}

User::User(const User& other)
{
	*this = other;
	std::cout << "User created (copy)" << std::endl;
}

User::~User()
{
	std::cout << "User destroyed" << std::endl;
}

User&	User::operator=(const User& rhs)
{
	this->_username = rhs._username;
	this->_nickname = rhs._nickname;
	this->_realname = rhs._realname;
	this->_usermode = rhs._usermode;

	this->_isRegistred = rhs._isRegistred;
	this->_isWelcomed = rhs._isWelcomed;

	return(*this);
}

//Getters
int			User::getID(void) const
{
	return(this->_id);
}
std::string	User::getUsername(void) const
{
	return(this->_username);
}
std::string	User::getNickname(void) const
{
	return(this->_nickname);
}
std::string	User::getRealname(void) const
{
	return(this->_realname);
}
int			User::getUsermode(void) const
{
	return(this->_usermode);
}
bool		User::isRegistred(void) const
{
	return(this->_isRegistred);
}
bool		User::isWelcomed(void) const
{
	return(this->_isWelcomed);
}


//Seters
void	User::setUsername(std::string username)
{
	this->_username = username;
}
void	User::setNickname(std::string nickname)
{
	this->_nickname = nickname;
}
void	User::setRealname(std::string realname)
{
	this->_realname = realname;
}
void	User::setUsermode(std::string usermode)
{
	this->_usermode = atoi(usermode.c_str());
}
void	User::setRegistred()
{
	this->_isRegistred = true;
}
void	User::setWelcomed()
{
	this->_isWelcomed = true;
}