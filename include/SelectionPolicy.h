#pragma once
#include "Party.h"

class Party;

class SelectionPolicy
{
    public:
        virtual ~SelectionPolicy() = default;
        virtual Party Choose(Party aParty,Party bParty,int edgeWeight1,int edgeWeight2)=0;  
        virtual int whichPolicy()=0;  
};

class MandatesSelectionPolicy : public SelectionPolicy 
{
    public:
        virtual ~MandatesSelectionPolicy() = default;
        Party Choose(Party aParty,Party bParty,int edgeWeight1,int edgeWeight2) override;
        int whichPolicy() override;
    
};

class EdgeWeightSelectionPolicy : public SelectionPolicy 
{
    public:
        virtual ~EdgeWeightSelectionPolicy() = default;
        Party Choose(Party aParty,Party bParty,int edgeWeight1,int edgeWeight2) override;
        virtual int whichPolicy() override;
};