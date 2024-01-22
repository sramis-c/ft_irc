#include "../Command.hpp"

UserCommand::~UserCommand()
{
}

int		UserCommand::execute()
{
	this->_user->setUsername(this->_parameters[0]);
	this->_user->setUsermode(this->_parameters[1]);
	this->_user->setRealname(this->_message);
	this->_user->setRegistred();

	if (this->_user->isWelcomed() == false)
	{
		this->_user->setWelcomed(); 
		return(1);
	}
	return (0);
}

int		UserCommand::validate()
{
	if (this->_parameters.size() != 3) //TODO: check? expectedSize as variable?
		return(Replies::Numerics::ERR_NEEDMOREPARAMS);
	if (this->_user->isRegistred())
		return(Replies::Numerics::ERR_ALREADYREGISTRED);
	/*
	** Ckeck here if the username is already taken; ??
	**	if (this->_parameters[1] == )
	*/
	return(0);
}