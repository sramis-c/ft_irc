#include "../Command.hpp"

JoinCommand::~JoinCommand(){}

int JoinCommand::execute()
{
    if (this->_target == NULL)
        this->_observer->onChannelCreationRequest(this->_parameters[0], this->_user);
    //std::cout << this->_user->getNickname() << " joined the channel: " << this->_target->getChannelName() << std::endl;

    return(0);
}

int JoinCommand::validate()
{
    return(0);
}

void    JoinCommand::setTarget(Channel* target)
{
    this->_target = target;
}

void    JoinCommand::setObserver(IChannelObserver* observer)
{
    this->_observer = observer;
}