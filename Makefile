CXX ?= g++
CXXFLAGS ?= -Wall -Werror -pedantic -g --std=c++17 -Wno-sign-compare -Wno-comment

# Compile the main executable
maze: main.o Maze.o
	$(CXX) $(CXXFLAGS) main.o Maze.o -lncurses -o maze

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -c

Maze.o: Maze.cpp Maze.h
	$(CXX) $(CXXFLAGS) Maze.cpp -c

# Compile tests
tests: tests-main.o Maze.o tests-maze.cpp
	$(CXX) $(CXXFLAGS) tests-main.o Maze.o tests-maze.cpp -lncurses -o tests && ./tests

tests-main.o: tests-main.cpp
	$(CXX) $(CXXFLAGS) tests-main.cpp -c

clean:
	rm *.o tests maze