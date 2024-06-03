#include "Coalition.h"
#include "Party.h"
#include "Simulation.h"
#include <algorithm>


Coalition::Coalition(int partyId, SelectionPolicy *mselectionPolicy) : coalitionList(1,partyId),totalMandates(0),offeredParties(),selectionPolicy(mselectionPolicy->whichPolicy()),coalitionId(partyId)
{
    
}

Coalition::Coalition(const Coalition &other): coalitionList(other.coalitionList),totalMandates(other.totalMandates),offeredParties(other.offeredParties),selectionPolicy(other.selectionPolicy),coalitionId(other.coalitionId){}

int Coalition::getTotalMandates()
{
    return totalMandates;
}

int Coalition::getCoalitionId()
{
    return coalitionId;
}

void Coalition::addMandates(int mandates)
{
    totalMandates = totalMandates + mandates;
}

void Coalition::addParty(Party &party,Simulation &sim)
{
    party.closeState();
    coalitionList.push_back(party.getmId());
    totalMandates = totalMandates + party.getMandates();
    sim.addAgent(party.getmId());

   
    
}

void Coalition::addOfferedParty(int partyId)
{
    offeredParties.push_back(partyId);//if we have time we can make it more efficient by doing a binary search and sorting the vector
}

bool Coalition::hasBeenOffered(int partyId)
{
    if(std::find(offeredParties.begin(),offeredParties.end(),partyId) != offeredParties.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}