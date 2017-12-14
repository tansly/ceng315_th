CXX=g++
CXXFLAGS=-std=c++14 -Wall -Wextra -O2

runTH: main.cpp graph.cpp graph.h
	$(CXX) $(CXXFLAGS) main.cpp graph.cpp -o runTH

clean:
	rm -f *.o runTH
