#include <string>

#pragma once

namespace Replies
{
	namespace Numerics
	{
		const int	RPL_EMPTY				= 000; //Custom; not final?
		const int	RPL_WELCOME				= 001;
		const int	ERR_NEEDMOREPARAMS		= 461;
		const int	ERR_ALREADYREGISTRED	= 462;
	}

	namespace Message
	{
		static const std::string	RPL_EMPTY				= "";
		static const std::string	RPL_PONG				= "PONG\r\n";
		static const std::string	RPL_WELCOME				= "001 <nick> :Welcome to the <network> Network, <nick>[!<user>@<host>]\r\n";
		static const std::string	ERR_NEEDMOREPARAMS		= "461 <client> <command> : Wrong number of parameters\r\n";
		static const std::string	ERR_ALREADYREGISTRED	= "462 <client> <command> : User already registred\r\n";
	}

}