#include "SocketHandler.hpp"

irc::socket::SocketHandler::SocketHandler(int fd)
{
	this->_fd = fd;
}

irc::socket::SocketHandler::~SocketHandler()
{
	::close(this->_fd);
}

irc::socket::SocketHandler::SocketHandler( SocketHandler const &copy)
{
	*this = copy;
}

irc::socket::SocketHandler &irc::socket::SocketHandler::operator=( SocketHandler const &rhs)
{
	this->_fd = rhs._fd;
	memcpy(this->_buff, rhs._buff, BUFFER_SOCKET);
	return *this;
}

int irc::socket::SocketHandler::send(std::string &msg)
{
	size_t bytes;
	bytes = ::send(this->_fd,  msg.c_str(), msg.size(), NO_FLAGS);
	return(bytes);
}

std::string irc::socket::SocketHandler::receive(void)
{
	size_t bytes;

	memset(this->_buff, 0, BUFFER_SOCKET);
	bytes = recv(this->_fd, this->_buff, sizeof(this->_buff), NO_FLAGS);
	if (bytes <= 0)
		return(std::string(""));
	return(std::string(_buff, bytes));
}

int		irc::socket::SocketHandler::close()
{
	return(::close(this->_fd));
}

int	irc::socket::SocketHandler::getSocket(void)
{
	return(this->_fd);
}
/*
std::ostream &operator<<( std::ostream & o, SocketHandler const &i)
{
	o << std::endl;
	return (o);
}
*/