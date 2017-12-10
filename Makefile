CXX=g++
CXXFLAGS=-std=c++14 -Wall -Wextra -g -Og

runTH: main.cpp priority_queue.cpp priority_queue.h
	$(CXX) $(CXXFLAGS) main.cpp priority_queue.cpp -o runTH
