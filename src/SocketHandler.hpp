#include <string>
#include <iostream>

#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>

#define BUFFER_SOCKET 1024
#define NO_FLAGS 0

namespace irc
{
	namespace socket
	{
		class SocketHandler
		{
			private:
				int		_fd;
				char	_buff[BUFFER_SOCKET];

			public:
				SocketHandler(int fd);
				SocketHandler( SocketHandler const &copy);
				~SocketHandler();

				SocketHandler &operator=( SocketHandler const &rhs);

				int				send(std::string &message);
				std::string		receive();
				int				close();

				int				getSocket(void);
		};
		//std::ostream &operator<<( std::ostream &o, SocketHandler const &i);
	}
}


