#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <sstream>
#include <poll.h>
#include <vector>
#include "SocketListener.hpp"
#include "Logger.hpp"
#include <map>

namespace irc
{
	class Client;
	class Channels;
	class Server
	{
		private:
			bool									isRuning;
			//nfds_t									_nfds;
			int										_FD;
			//int										_port;
			int										timeout;
			std::vector<struct pollfd>				_fds;
			std::vector<int>						_disconnected;
			std::map<std::string, std::string>		_config;
			std::map<int, Client*>					_Clients;
			std::map<std::string, Channels*>		_Channels;

			irc::socket::SocketListener				*listener;
			const Log::Logger						*logger;

		public:
			Server();
			~Server();

			bool validate_config(std::map<std::string, std::string> const &config);
			void init(std::map<std::string, std::string> const &config, Log::Logger &logger);
			void run();

			void handleNewConnections(void);
			void acceptNewUser(void);
			void closeDisconections(void);

			void setLogger(const Log::Logger *logger);
	};
};
#endif