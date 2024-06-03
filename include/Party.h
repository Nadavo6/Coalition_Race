#pragma once
#include <string>
#include <utility>
#include "JoinPolicy.h"
#include "Agent.h"

using std::string;

class Simulation;
class Agent;
class JoinPolicy;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 
    Party();
    State getState() const;
    void setState(State state);
    int getMandates() const;
    int getmId() const;
    void step(Simulation &s);
    const string &getName() const;
    int timer;
    void recieveOffer(Agent &agent);
    virtual ~Party();//destructor
    Party(const Party &other);//copy constractor
    Party(Party&& other);
    Party& operator=(const Party &other);
    Party& operator=(Party &&other);
    int getPolicy() const;
    void closeState();

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    Agent *bestOfferedAgent;
};
