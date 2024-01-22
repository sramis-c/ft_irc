#include "../Command.hpp"
#include <stdio.h>

PrivMsgCommand::PrivMsgCommand(User* user, std::vector<std::string> parameters, std::string message) : Command(user, parameters, message)
{
    this->_target = NULL;
}

PrivMsgCommand::~PrivMsgCommand()
{
}

int         PrivMsgCommand::execute()
{
    if (this->_target)
    {
        if (!send(this->_target->getID(), this->_message.c_str(), 1024, 0))
            perror("Not properly sent");                    //NW
    }
    return(0);
}

int         PrivMsgCommand::validate()
{   //TODO
    return(0);
}

void        PrivMsgCommand::setTarget(User* target)
{
    this->_target = target;
}