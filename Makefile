CXX=g++
CXXFLAGS=-std=c++14 -Wall -Wextra -g -O2

runTH: main.cpp graph.cpp graph.h priority_queue.cpp priority_queue.h
	$(CXX) $(CXXFLAGS) main.cpp graph.cpp priority_queue.cpp -o runTH

clean:
	rm -f *.o runTH
