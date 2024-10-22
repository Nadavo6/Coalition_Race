# Coalition_Race

The objective of this assignment is to design an object-oriented system and gain
implementation experience in C++ while using classes, standard data structures, and unique
C++ properties such as the “Rule of 5”. You will learn how to handle memory in C++ and avoid
memory leaks.

After 5 elections, the SPLand president decided to change the method of forming a coalition by
letting multiple "agents" from different parties try their best to create a 61 coalition as fast as
possible.
In this assignment, you will write a C++ program that simulates the "Coalition Race" and report
the first coalition formed (or failure).
The simulator should be based on a graph that contains:
● Parties as vertices
● Collaborations as edges (2 parties that agree to cooperate)
● “Similarity score” as edge weight, for every 2 connected parties
Here is an example for a graph at the beginning of the simulation. The colors represent the
state of the parties (will be explained later).
The program will receive a config file (JSON) as input, which includes the parties' details (id,
name, number of mandates, join policy), the graph, and the list of agents (id, party id, selection
policy). “Join policy” and “Selection policy” will be explained later.
Each agent belongs to a party. In every step, the agent offers an adjacent party to join. When a
party has decided to join a coalition, it should clone the agent who made the offer to the
newly joined party (so the joined party can now help the coalition).
To clarify:
● Coalition is a set of connected parties (in SPLand, connectivity is enough).
● In each party, there is a single agent if the party belongs to a coalition (state Joined).
● The total number of agents in the simulation equals the number of parties in the graph
belonging to some coalition (state Joined).
Example
Suppose an agent from party#0 offered party#1 to join its coalition.
If party#1 accepts the offer, it adds itself to the coalition and adds a clone of the agent to the
vector of agents (as well as updating the id and party id).