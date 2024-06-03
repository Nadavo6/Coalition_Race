#include "Party.h"
#include "Simulation.h"
#include "Agent.h"
#include "JoinPolicy.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : timer(0),mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting),  bestOfferedAgent(new Agent())
{
    // You can change the implementation of the constructor, but not the signature!
}

Party::Party() : timer(0),mId(99), mName("name"), mMandates(0), mJoinPolicy(new MandatesJoinPolicy), mState(Waiting),  bestOfferedAgent(new Agent())
{
    // You can change the implementation of the constructor, but not the signature!
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

int Party::getmId() const
{
    return mId;
}

int Party::getPolicy() const
{
    return mJoinPolicy->whichPolicy();
}

const string &Party::getName() const
{
    return mName;
}

Party::~Party()
{
    if (mJoinPolicy)
        delete mJoinPolicy;
    if (bestOfferedAgent)
        delete bestOfferedAgent;
}

Party::Party(const Party &other) : timer(other.timer),mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(), mState(other.mState),  bestOfferedAgent(other.bestOfferedAgent)
{
    if (other.mJoinPolicy->whichPolicy() == 1)
    {
        mJoinPolicy = new MandatesJoinPolicy;
    }
    else
    {
        mJoinPolicy = new LastOfferJoinPolicy;
    }
}

void Party::closeState(){mState = Joined;}

Party::Party(Party &&other) : timer(other.timer),mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState),  bestOfferedAgent(other.bestOfferedAgent)
{
    other.bestOfferedAgent = nullptr;

    other.mJoinPolicy = nullptr;
}

Party &Party::operator=(const Party &other)
{
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    mState = other.mState;
    timer = other.timer;
    *bestOfferedAgent = *(other.bestOfferedAgent);
    *mJoinPolicy = *(other.mJoinPolicy);
    return *this;
}
Party &Party::operator=(Party &&other)
{
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    mState = other.mState;
    timer = other.timer;
    if (bestOfferedAgent)
        delete bestOfferedAgent;
    bestOfferedAgent = other.bestOfferedAgent;
    other.bestOfferedAgent = nullptr;

    if (mJoinPolicy)
        delete mJoinPolicy;
    mJoinPolicy = other.mJoinPolicy;
    other.mJoinPolicy = nullptr;

    return *this;
}

void Party::recieveOffer(Agent &agent)
{
    if (mState == Waiting)
    {
        mState = CollectingOffers;
        *bestOfferedAgent = agent;
    }
    else if (mState == CollectingOffers)
    {
        *bestOfferedAgent = (*mJoinPolicy).Choose(*bestOfferedAgent, agent); // to ask how to write
    }
}
// we need to to RULE OF 5 here!!!
void Party::step(Simulation &s)
{
    if (mState == CollectingOffers)
    {
        timer++;
        if (timer == 3)
        {
            s.findCoalition(bestOfferedAgent->getPartyId()).addParty(*this, s);
        }
    }
}
