#include "SocketListener.hpp"
#include <string>
#include <iostream>

irc::socket::SocketListener::SocketListener(const char *host, int port)
{
	this->_host = std::string(host);
	this->_port = port;
	this->_fd_socket = -1;
	this->_logger = NULL;
	this->e_log = false;
}

irc::socket::SocketListener::SocketListener( SocketListener const &copy)
{
	*this = copy;
}

irc::socket::SocketListener::~SocketListener()
{
}


irc::socket::SocketListener &irc::socket::SocketListener::operator=( SocketListener const &rhs)
{
	this->_fd_socket = rhs._fd_socket;
	this->_port = rhs._port;
	this->_host = rhs._host;
	this->_address = rhs._address;
	this->_address_len = rhs._address_len;
	return *this;
}

void irc::socket::SocketListener::setLogger(Log::Logger *logger)
{
	if(logger != NULL)
		this->e_log = true;
	this->_logger = logger;
}

void irc::socket::SocketListener::useLogger(Log::logType type, const std::string& msg)
{
#ifdef LOGGER
	if(this->_logger != NULL)
		this->_logger->log(type, msg);
# else
	(void)type;
	(void)msg;
#endif
}

void irc::socket::SocketListener::start()
{
	this->_fd_socket = ::socket(AF_INET, SOCK_STREAM, 0);
	this->_address_len = sizeof(this->_address);

	if(this->_fd_socket == -1)
		throw SocketCreationFail(_fd_socket, "Imposible to create de socket");
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = inet_addr(this->_host.c_str());
	this->_address.sin_port = htons(this->_port);
	
	int stat_flags = fcntl(this->_fd_socket, F_SETFL, O_NONBLOCK);
	if(stat_flags == -1)
		throw SocketCreationFail(this->_fd_socket, "Failed to set socket to non-blocking");

	int stat_bind = bind(this->_fd_socket, reinterpret_cast<struct sockaddr*>(&this->_address), sizeof(this->_address));
	if(stat_bind == -1)
		throw SocketCreationFail(_fd_socket, "Failed to bind socket to the address");
	
	int stat_listen = listen(this->_fd_socket, 5);
	if(stat_listen == -1)
		throw SocketCreationFail(_fd_socket, "Failed to listen on the server socket");

}

void irc::socket::SocketListener::stop()
{
	close(this->_fd_socket);
}

int irc::socket::SocketListener::acceptNewConnection()
{
	int new_socket;
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);

	std::cout << "Socket listener server socket fd: " << this->_fd_socket << std::endl;
	new_socket = accept(this->_fd_socket, (sockaddr*)&this->_address, (socklen_t*)&addr_len);
	std::cout << "Socket listener new socket: " << new_socket <<std::endl;
	if(new_socket < 0)
	{
		std::cerr << "Imposible to accept" << std::endl;
		//exit(EXIT_FAILURE);
	}
	std::cout << "Conextion accepted" << std::endl;
	return(new_socket);
}

int irc::socket::SocketListener::getSocketFd() const
{
	return(this->_fd_socket);
}

irc::socket::SocketListener::SocketCreationFail::SocketCreationFail(int i,const std::string &msg) : fd(i), msg(msg) {}

const char* irc::socket::SocketListener::SocketCreationFail::what() const throw ()
{
	close(fd);
	return (this->msg.c_str());
}

irc::socket::SocketListener::SocketCreationFail::~SocketCreationFail() throw(){}

/*
int main(void){
	char buff[1024];
	SocketListener listener("127.0.0.1" , 6667);

	try{
		listener.start();
	}catch(const std::exception &e){
		std::cerr << e.what() << std::endl;
	}
	int fd_client = listener.acceptNewConnection();
	int ret = read(fd_client, buff, 1024);
	(void)ret;
	std::cout << buff << std::endl;
	listener.stop();
	return(0);
}
*/

/*https://www.ibm.com/docs/en/i/7.4?topic=designs-using-poll-instead-select
#include <sys/poll.h>
#include <vector>
int main(void)
{
	SocketListener listener("127.0.0.1" , 6667);
	try{
		listener.start();
	}catch(const std::exception &e){
		std::cerr << e.what() << std::endl;
	}
	int sockfd = listener.getSocketFd();
	struct pollfd pollfds[1];
	pollfds[0].fd = sockfd;
	pollfds[0].events = POLLIN;

	std::vector<int> clientsock;
	while(true){
		std::cout << "Waiting poll.." << std::endl;
		int stat_poll = poll(pollfds, 1, -1);
		std::cout << "poll returned " << stat_poll << std::endl;
		if(stat_poll > 0)
		{
			int newSocket = listener.acceptNewConnection();
			char buff[1024];
			int bytesRead = read(newSocket, buff, sizeof(buff));
			if(bytesRead <= 0)
				std::cout << "client disconected" << std::endl;
			else
				std::cout << "Client text: " << std::string(buff, bytesRead) <<std::endl;
			close(newSocket);
		}
	}
	listener.stop();
	return(0);

}*/
/*
#include <sys/poll.h>
#include <vector>
int main(void)
{
	SocketListener listener("127.0.0.1" , 6667);
	try{
		listener.start();
	}catch(const std::exception &e){
		std::cerr << e.what() << std::endl;
	}
	int sockfd = listener.getSocketFd();
	struct pollfd pollfds[11];
	pollfds[0].fd = sockfd;
	pollfds[0].events = POLLIN;

	for (int i = 0; i <= 10; i++)
	{
		pollfds[i].fd = -1;
		pollfds[i].events = POLLIN;

	}
	std::vector<int> clientsock;
	while(true)
	{
		
	}

	return(0);	
}
*/
/*
std::ostream &operator<<( std::ostream & o, SocketListener const &i)
{
	o << std::endl;
	return (o);
}*/

/*https://beej.us/guide/bgnet/html/#blocking
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}*/