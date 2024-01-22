#include "../Command.hpp"

NickCommand::~NickCommand()
{
}

int		NickCommand::execute()
{
	this->_user->setNickname(this->_parameters[0]);

	/*if (this->_user.isWelcomed() == false)
	{
		this->_user.setWelcomed(); 
		return(1);
	}*/
	return (0);
}

int		NickCommand::validate()
{
	if (this->_parameters.size() == 0)
		return(7); //Change this
	if (this->_parameters.size() != 1) //TODO: check? expectedSize as variable?
		return(Replies::Numerics::ERR_NEEDMOREPARAMS);
	/*if (this->_user.isRegistred())
		return(Replies::Numerics::ERR_ALREADYREGISTRED);*/
	/*
	** Ckeck here if the username is already taken; ??
	**	if (this->_parameters[1] == )
	*/
	return(0);
}