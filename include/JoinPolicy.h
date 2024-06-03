#pragma once
#include <string>
#include "Party.h"

using std::string;
class Agent;

class JoinPolicy 
{
    public:
        virtual ~JoinPolicy() = default;
        virtual Agent Choose(Agent &aAgent,Agent &bAgent)=0;
        virtual int whichPolicy()=0;
};

class MandatesJoinPolicy : public JoinPolicy 
{
    public:
        virtual ~MandatesJoinPolicy() = default;
        Agent Choose(Agent &aAgent,Agent &bAgent) override;
        int whichPolicy() override;
    
};

class LastOfferJoinPolicy : public JoinPolicy 
{
    public:
        virtual ~LastOfferJoinPolicy() = default;
        Agent Choose(Agent &aAgent,Agent &bAgent) override;
        int whichPolicy() override;
};