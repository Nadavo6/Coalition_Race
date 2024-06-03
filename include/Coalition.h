#pragma once

#include <vector>


using std::vector;
class Party;
class Simulation;
class Agent;
class SelectionPolicy;

class Coalition
{
public:
    Coalition(int partyId, SelectionPolicy *mselectionPolicy);
    Coalition(const Coalition &other);
    void addParty(Party &party,Simulation &s);
    void addOfferedParty(int partyId);
    bool hasBeenOffered(int party);
    int getTotalMandates();
    int getCoalitionId();
    void addMandates(int mandates);
    vector<int> coalitionList;
private:
    int totalMandates;
    vector<int> offeredParties;
    int selectionPolicy;
    int coalitionId;
};