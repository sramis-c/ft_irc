#include "ClientManager.hpp"

ClientManager::ClientManager(){}
	
ClientManager::~ClientManager(){}

void	ClientManager::handleRequest(int fd, std::string message)
{	//QUIT && PING && CAP LS 302
	int numeric = 0;

	std::map<int, User*>::iterator it = this->_users.find(fd);
	if(it == this->_users.end())
		this->_users[fd] = new User(fd);

	this->_parser.parse(message);
	this->_invoker.setCommand(this->_users[fd], fd, this->_parser, this->_users, this->_channels);
	numeric = this->_invoker.executeCommand();
	
	//Class for replies???
	setReply(numeric);
	this->_reply = formatReply(this->_reply, fd); //Needs work
		//TODO handle replies
}

void	ClientManager::onChannelCreationRequest(const std::string& channelName, User* user)
{
	this->_channels[channelName] = new Channel(channelName);
	this->_channels[channelName]->addUser(user);
}

void		ClientManager::setReply(int num)
{	//TODO: more replies
	switch(num)
	{
		case 1:
			this->_reply = Replies::Message::RPL_WELCOME;
			break;
		case 461:
			this->_reply = Replies::Message::ERR_NEEDMOREPARAMS;
			break;
		case 462:
			this->_reply = Replies::Message::ERR_ALREADYREGISTRED;
			break;
		default:		//Temporary. Change this
			this->_reply = Replies::Message::RPL_EMPTY;
			break;
	}
}

std::string			ClientManager::formatReply(std::string reply, int fd)
{	//TODO: <hostname>
	std::string formattedReply;
	size_t		pos;

	formattedReply = reply;

	pos = formattedReply.find("<nick>");
	if(pos != std::string::npos)
		formattedReply.replace(pos, 6, this->_users[fd]->getNickname());

	pos = formattedReply.find("<user>");
	if(pos != std::string::npos)
		formattedReply.replace(pos, 6, this->_users[fd]->getUsername());

	pos = formattedReply.find("<network>");
	if(pos != std::string::npos)
		formattedReply.replace(pos, 9, "ft_irc_network");

	return(formattedReply);
}

std::string	ClientManager::getReply()
{
	return(this->_reply);
}
