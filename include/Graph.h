#pragma once
#include <vector>
#include "Party.h"

using std::vector;
class Party;

class Graph
{
public:
    Graph(vector<Party> vertices, vector<vector<int>> edges);
    Graph(const Graph &other);
    int getMandates(int partyId) const;
    int getEdgeWeight(int v1, int v2) const;
    int getNumVertices() const;
    const Party &getParty(int partyId) const;
    Party &getParty2(int partyId);
    std::vector<std::pair<int, int>> getNeighbors(Party curr) ;
    vector<Party> getmVertices() const;

private:
    vector<Party> mVertices;
    vector<vector<int>> mEdges;
};
