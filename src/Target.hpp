#pragma once
#include <string>

enum AttributeType {username, nickname, realname};

class ITarget
{
    public:
        virtual ~ITarget(){};

        virtual void modifyAttributes(const AttributeType& attribute, std::string data) = 0;
        //virtual void manageMembership(User* user, MembershipAction action) = 0;
        //virtual void receiveMessage(const std::string& message) = 0;
};