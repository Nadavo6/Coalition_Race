#include "Graph.h"
#include "Party.h"

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges) 
{
    // You can change the implementation of the constructor, but not the signature!
}

Graph::Graph(const Graph &other) : mVertices(other.mVertices), mEdges(other.mEdges) 
{
    // You can change the implementation of the constructor, but not the signature!
}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

vector<Party> Graph::getmVertices() const{return mVertices;}

std::vector<std::pair<int, int>> Graph::getNeighbors(Party curr)
{
    std::vector<std::pair<int, int>> a;
    for( Party &ver : mVertices)
    {
        if (ver.getmId() != curr.getmId())
        {
            int edgeWeight = getEdgeWeight(curr.getmId(),ver.getmId());
            if (edgeWeight>0)
            {
                a.push_back(std::pair<int, int>(edgeWeight,ver.getmId()));
            }
            
        }
        
    }
    return a;
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}


int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}
Party &Graph::getParty2(int partyId) 
{
    return mVertices[partyId];
}
