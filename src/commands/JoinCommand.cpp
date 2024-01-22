#include "../Command.hpp"

JoinCommand::~JoinCommand(){}

int JoinCommand::execute()
{/*
    if (this->_target == NULL)
        this->_observer->onChannelCreationRequest(this->_parameters[0], this->_user);
    else
        this->_target->addUser(this->_user);*/
    //std::cout << this->_user->getNickname() << " joined the channel: " << this->_target->getChannelName() << std::endl;

    return(0);
}

int JoinCommand::validate()
{
    return(0);
}

void    JoinCommand::setObserver(IChannelObserver* observer)
{
    this->_observer = observer;
}