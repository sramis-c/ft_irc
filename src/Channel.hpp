#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "User.hpp"

class IChannelObserver
{
	public:
    	virtual void	onChannelCreationRequest(const std::string& channelName, User* user) = 0;
};

class Channel
{
	private:
		int			_id;

		std::string	_channelName;
		std::string	_channelKey;
		std::string	_channelTopic;
		int			_channelMode;

		bool		_isFull;
		bool		_isInviteOnly;
        bool        _isProtected;

        std::vector<User*>   _userList;

	public:
		Channel();
		Channel(const std::string name);
		Channel(const Channel& other);
		~Channel();

		Channel&	operator=(const Channel& rhs);

		void		addUser(User* user);

		//Getters
		std::string		getChannelName(void) const;


		//Setters

		
};