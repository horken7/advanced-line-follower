output: graph.o graphtest.o
	g++ graph.o graphtest.o -o output

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

graphtest.o: graphtest.cpp
	g++ -c graphtest.cpp

clean:
	rm *.o output
