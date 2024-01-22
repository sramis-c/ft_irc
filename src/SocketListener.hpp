#ifndef SOCKET_LISTENER_HPP
#define SOCKET_LISTENER_HPP
#include <string>
#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <exception>
#include <fcntl.h>

#include "Logger.hpp"
class Logger;

namespace irc
{
	namespace socket
	{
		class SocketListener
		{
			private:
				int					_fd_socket;
				int					_port;
				std::string			_host;
				struct sockaddr_in	_address;
				int					_address_len;

				Log::Logger				*_logger;
				bool				e_log;
			public:
				SocketListener(const char *host, int port);
				SocketListener( SocketListener const &copy);
				~SocketListener();

				SocketListener &operator=( SocketListener const &rhs);

				void	setLogger(Log::Logger *logger);
				void	useLogger(Log::logType type, const std::string& message);

				void	start();
				void	stop();
				int		acceptNewConnection();
				



				int getSocketFd() const;

				class SocketCreationFail: public std::exception
				{
					private:
						int fd;
						std::string msg;
					public:
						SocketCreationFail(int i, const std::string &msg);
						const char *what() const throw();
						~SocketCreationFail() throw();
				};
		};
		//std::ostream &operator<<( std::ostream &o, SocketListener const &i);
	} // namespace socket
} // namespace irc
#endif