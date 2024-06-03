#include <Simulation.h>
#include "Coalition.h"
#include "Agent.h"
#include "Party.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mCoalitions(),mGraph(graph), mAgents(agents),max(0,0) 
{
    int a = mAgents.size();
    for (int i=0;i<a;i++)
    {
        mCoalitions.push_back(Coalition(mAgents[i].getPartyId(),mAgents[i].getSPType()));
        mCoalitions[i].addMandates(mGraph.getParty2(mAgents[i].getPartyId()).getMandates());    
    }
}

void Simulation::step()
{
   
    for (int i=0;i<getGraph().getNumVertices();i++)
    {
        mGraph.getParty2(i).step(*this);
            
    }
    for (Agent& agent : mAgents)
    {
        agent.step(*this);
        
    }
    for (Coalition &coalition : mCoalitions)
    {
        if (max.first<coalition.getTotalMandates())
        {
            max.first = coalition.getTotalMandates();
            max.second = coalition.getCoalitionId();
        }
    }
         
    
    
}

void Simulation::addAgent(int partyId)
{
    if (getParty2(partyId).getPolicy() == 1)
    {
        Agent newAgent = Agent(mAgents.size(),getParty2(partyId).getmId(),new MandatesSelectionPolicy);
        newAgent.start = false;
        std::vector<std::pair<int,int>> neighboors = getGraph().getNeighbors(getParty2(newAgent.getPartyId()));  
        int neighboorSize = neighboors.size(); 
        for (int i = 1; i < neighboorSize; i++)
        {
            std::pair<int,int> value = neighboors[i];
            while (i>0 && (newAgent.getSPType())->Choose(getParty2(value.second),getParty2(neighboors[i-1].second),value.first,neighboors[i-1].first).getmId() != value.second)
            {
                neighboors[i] = neighboors[i-1];
                i=i-1;
            }
            neighboors[i] = value;
            
        }
        for(int i=(neighboorSize-1);i>=0;i--)
        {
            newAgent.pickingOrder.push(neighboors[i].second);
        }
        mAgents.push_back(newAgent);

    }
    else
    {
        Agent newAgent = Agent(mAgents.size(),getParty2(partyId).getmId(),new EdgeWeightSelectionPolicy);
        newAgent.start = false;
        std::vector<std::pair<int,int>> neighboors = getGraph().getNeighbors(getParty2(newAgent.getPartyId()));  
        int neighboorSize = neighboors.size(); 
        for (int i = 1; i < neighboorSize; i++)
        {
            std::pair<int,int> value = neighboors[i];
            while (i>0 && (newAgent.getSPType())->Choose(getParty2(value.second),getParty2(neighboors[i-1].second),value.first,neighboors[i-1].first).getmId() != value.second)
            {
                neighboors[i] = neighboors[i-1];
                i=i-1;
            }
            neighboors[i] = value;
            
        }
        for(int i=(neighboorSize-1);i>=0;i--)
        {
            newAgent.pickingOrder.push(neighboors[i].second);
        }
        mAgents.push_back(newAgent);
    }
}

Coalition &Simulation::findCoalition(int partyId)
{
    int k = mCoalitions.size();
    for (int i = 0; i < k; i++)
    {
        for (int num : mCoalitions[i].coalitionList)
        {
            if (num == partyId)
            {
                return mCoalitions[i];
            }
            
        }   
    }
    return mCoalitions[0];
}

std::vector<Agent> Simulation::getAgentsList() const{return mAgents;}

void Simulation::addCoalition(Coalition &coalition)
{
    if (max.first<coalition.getTotalMandates())
    {
        max.first = coalition.getTotalMandates();
        max.second = coalition.getCoalitionId();
    }
    
    mCoalitions.push_back(coalition);
}

Graph& Simulation::getGraph()
{
    return mGraph;
}

bool Simulation::isEveryoneJoined() const
{
    for (Party &party :  mGraph.getmVertices())
    {
        if (party.getState() != Joined)
        {
            return false;
        }
        
    }
    return true;
    
}

bool Simulation::shouldTerminate() const
{
    if (max.first >= 61)
    {
        return true;
    }
    else if (isEveryoneJoined())
    {
        return true;
    }
    else{
        return false;
    }
    
}


const Graph &Simulation::getGraph() const
{
    return mGraph;
}


const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

Party &Simulation::getParty2(int partyId)
{
    return mGraph.getParty2(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> allParties = vector<vector<int>>();
    for (Coalition coalition : mCoalitions)
    {
        vector<int> curCoalition = vector<int>();
        for (int &partyId : coalition.coalitionList)
        {
            curCoalition.push_back(partyId);
        }
        allParties.push_back(curCoalition);
    }
    
    return allParties;
}
