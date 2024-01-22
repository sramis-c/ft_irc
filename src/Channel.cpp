#include "Channel.hpp"

Channel::Channel() : _isFull(false), _isInviteOnly(false), _isProtected(false)
{
	std::cout << "Channel created" << std::endl;
}

Channel::Channel(const std::string name) : _channelName(name), _isFull(false), _isInviteOnly(false), _isProtected(false)
{
	std::cout << "Channel [" << name << "] created" << std::endl;
}

Channel::Channel(const Channel& other)
{
	*this = other;
	std::cout << "Channel created (copy)" << std::endl;
}

Channel::~Channel()
{
	std::cout << "Channel destroyed" << std::endl;
}

Channel&	Channel::operator=(const Channel& rhs)
{   //Needs to copy Users
	this->_channelName = rhs._channelName;
	this->_channelKey = rhs._channelKey;
	this->_channelTopic = rhs._channelTopic;
	this->_channelMode = rhs._channelMode;

	this->_isFull = rhs._isFull;
	this->_isInviteOnly = rhs._isInviteOnly;
    this->_isProtected = rhs._isProtected;

	return(*this);
}

void        Channel::addUser(User* user)
{
    this->_userList.push_back(user);
}

//Getters

std::string     Channel::getChannelName(void) const
{
    return(this->_channelName);
}