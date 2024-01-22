#include "Server.hpp"
#include "ClientManager.hpp"
#include "Replies.hpp"
#include <stdio.h>
#include <string.h>

irc::Server::Server()
{
	this->isRuning = true;
//	this->_FD = -1;
	
}

irc::Server::~Server()
{
	
}

bool irc::Server::validate_config(std::map<std::string, std::string> const &config)
{
	(void)config;
	return(true);
}

void irc::Server::init(std::map<std::string, std::string> const &config, Log::Logger &logger)
{
	int port;
	struct pollfd poll_socket;
	(void)logger;


	this->_config = config;
	std::istringstream SSport(this->_config["port"]);
	SSport >> port;

	this->listener = new irc::socket::SocketListener("0.0.0.0", port);
	listener->start();
	this->_FD = listener->getSocketFd();
	
	poll_socket.fd = this->_FD;
	poll_socket.events = POLLIN;
	this->_fds.push_back(poll_socket);
}

void irc::Server::run()
{
	int	stat_poll;
	(void)stat_poll;
	int	i = 0;
	ClientManager client;
	std::string		reply;
	while(isRuning)
	{
		stat_poll = poll(&this->_fds[0], this->_fds.size(), -1);
		if(stat_poll == -1)
		{
			std::cout << "PollFalild" << std::endl;
		}
		handleNewConnections();

		i = 0;
		for(std::vector<struct pollfd>::iterator it = this->_fds.begin() + 1; it != this->_fds.end(); ++it)
		{
			if(it->revents & POLLIN)
			{
				char buffer[1024];
				memset(buffer, '\0', 1024);
				int bytesRead = recv(it->fd, buffer, sizeof(buffer),0);
				//(void)bytesRead;
				if(bytesRead <= 0)
				{
					this->_disconnected.push_back(std::distance(this->_fds.begin(), it));
				}
				char* token = strtok(buffer, "\r\n");
            	while (token != NULL)
				{
					std::cout << "------------> Received data:\n" << token << "\n" << std::endl;
               		client.handleRequest(it->fd, token);
					std::cout << "<------------ Sent data:\n" << client.getReply() << std::endl;
					reply = client.getReply();
					if (!reply.empty())
						send(it->fd, reply.c_str(), 1024, 0);
            		token = strtok(NULL, "\r\n");
				}
				//send(it->fd, client.getReply(), 1024, 0);
			}
			i++;
		}
		for (std::vector<int>::reverse_iterator it = _disconnected.rbegin(); it != _disconnected.rend(); ++it) {
			std::cout << "\t" << *it << std::endl;
			close((this->_fds.begin() + *it)->fd);
			this->_fds.erase(this->_fds.begin() + *it);
		}
		 _disconnected.clear();
	}
}
void irc::Server::handleNewConnections(void)
{
	if(this->_fds[0].revents & POLLIN)
	{
		struct pollfd poll_NewConection;
		int NewClient = listener->acceptNewConnection();
		poll_NewConection.fd = NewClient;
		poll_NewConection.events = POLLIN;
		this->_fds.push_back(poll_NewConection);
	}
}

void irc::Server::setLogger(const Log::Logger *logger)
{
	if(this->logger == NULL)
		this->logger = logger;
}