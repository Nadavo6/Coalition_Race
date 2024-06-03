#include "Agent.h"
#include "Simulation.h"
#include "Coalition.h"
#include <bits/stdc++.h>
#include "SelectionPolicy.h"
#include "Party.h"
#include "queue"
using namespace std;



Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : pickingOrder(),neighbors(),start(true),agentsCoalition(Coalition(partyId,selectionPolicy)),mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    
}

Agent::Agent() : pickingOrder(),neighbors(),start(false),agentsCoalition(Coalition(mPartyId,new MandatesSelectionPolicy)),mAgentId(0), mPartyId(0), mSelectionPolicy(new MandatesSelectionPolicy){}


int Agent::getSelectionPolicy() const{return mSelectionPolicy->whichPolicy();}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}



Agent::~Agent()
{
    if(mSelectionPolicy) delete mSelectionPolicy;
}
Agent::Agent(const Agent &other):pickingOrder(other.pickingOrder),neighbors(other.neighbors),start(other.start),agentsCoalition(other.agentsCoalition),mAgentId(other.mAgentId),mPartyId(other.mPartyId),
mSelectionPolicy()
{
    if (other.mSelectionPolicy->whichPolicy() == 1)
    {
        mSelectionPolicy = new MandatesSelectionPolicy;
    }
    else
    {
        mSelectionPolicy = new EdgeWeightSelectionPolicy;
    }
}

Agent& Agent::operator=(const Agent &other)
{
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    agentsCoalition = other.agentsCoalition;
    neighbors = other.neighbors;
    start = other.start;
    pickingOrder = other.pickingOrder;
    *mSelectionPolicy = *(other.mSelectionPolicy);
    return *this;
}

Agent::Agent(Agent&& other):pickingOrder(other.pickingOrder),neighbors(other.neighbors),start(other.start),agentsCoalition(other.agentsCoalition),mAgentId(other.mAgentId),mPartyId(other.mPartyId),
mSelectionPolicy(other.mSelectionPolicy)
{
    other.mSelectionPolicy = nullptr; 
}

Agent& Agent::operator=(Agent &&other)
{
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    agentsCoalition = other.agentsCoalition;
    neighbors = other.neighbors;
    start = other.start;
    pickingOrder = other.pickingOrder;
    if(mSelectionPolicy)
    {
        delete mSelectionPolicy;
    }
    mSelectionPolicy = other.mSelectionPolicy;
    other.mSelectionPolicy = nullptr;
    
    return *this;
}

Coalition &Agent::getAgentCoalition(){return agentsCoalition;}

SelectionPolicy* Agent::getSPType() const{return mSelectionPolicy;}

void Agent::step(Simulation &sim)
{
    if (start)
    {
        start = false;
        agentsCoalition = sim.findCoalition(mPartyId);
        neighbors = sim.getGraph().getNeighbors(sim.getParty2(mPartyId));  
        int neighborSize = neighbors.size(); 
        for (int i = 1; i < neighborSize; i++)
        {
            std::pair<int,int> value = neighbors[i];
            while (i>0 && (*mSelectionPolicy).Choose(sim.getParty2(value.second),sim.getParty2(neighbors[i-1].second),value.first,neighbors[i-1].first).getmId() != value.second)
            {
                neighbors[i] = neighbors[i-1];
                i=i-1;
            }
            neighbors[i] = value;
            
        }
        for(int i=(neighborSize-1);i>=0;i--)
        {
            pickingOrder.push(neighbors[i].second);
        }

        
    }
    
    bool picked = false;
    while (pickingOrder.empty() == false && picked == false)
    {
        
        if(sim.getParty2(pickingOrder.front()).getState() != Joined && sim.findCoalition(mPartyId).hasBeenOffered(sim.getParty2(pickingOrder.front()).getmId())==false)
        {
            picked = true;
            sim.getParty2(pickingOrder.front()).recieveOffer(*this);
        }
        sim.findCoalition(mPartyId).addOfferedParty(sim.getParty2(pickingOrder.front()).getmId());
        pickingOrder.pop();
    }
    
    
}
