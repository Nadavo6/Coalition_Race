all: clean bin/cRace

bin/cRace: bin/main.o bin/Agent.o bin/Graph.o bin/JoinPolicy.o bin/SelectionPolicy.o bin/Parser.o bin/Party.o bin/Simulation.o bin/Coalition.o  
	g++ -o bin/cRace bin/main.o bin/Agent.o bin/Graph.o bin/JoinPolicy.o bin/SelectionPolicy.o bin/Parser.o bin/Party.o bin/Simulation.o bin/Coalition.o

bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

bin/Agent.o: src/Agent.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Agent.o src/Agent.cpp

bin/Graph.o: src/Graph.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Graph.o src/Graph.cpp

bin/JoinPolicy.o: src/JoinPolicy.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/JoinPolicy.o src/JoinPolicy.cpp

bin/SelectionPolicy.o: src/SelectionPolicy.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/SelectionPolicy.o src/SelectionPolicy.cpp

bin/Parser.o: src/Parser.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Parser.o src/Parser.cpp

bin/Party.o: src/Party.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Party.o src/Party.cpp

bin/Simulation.o: src/Simulation.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Simulation.o src/Simulation.cpp

bin/Coalition.o: src/Coalition.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Coalition.o src/Coalition.cpp



clean:
	rm -f bin/*
