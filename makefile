CXX = g++

default: ChordNode

ChordNode: ChordNode.o Utilities.o
	$(CXX) -g -Wall -o ChordNode ChordNode.o Utilities.o

ChordNode.o: ChordNode.cpp ChordNode.hpp Utilities.cpp Utilities.hpp
	$(CXX) -g -Wall -c ChordNode.cpp Utilities.cpp