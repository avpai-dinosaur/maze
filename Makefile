CXX ?= g++
CXXFLAGS ?= -Wall -Werror -pedantic -g --std=c++17 -Wno-sign-compare -Wno-comment

# Compile the main executable
maze: main.cpp Maze.cpp
	$(CXX) $(CXXFLAGS) main.cpp Maze.cpp -lncurses -o maze
