output: pathPlanning.o graphtest.o graph.o
	g++ pathPlanning.o graphtest.o graph.o -o output

pathPlanning.o: pathPlanning.h pathPlanning.cpp
	g++ -c pathPlanning.cpp

graphtest.o: graphtest.cpp
	g++ -c graphtest.cpp

graph.o: graph.h graph.cpp
	g++ -c graph.cpp


