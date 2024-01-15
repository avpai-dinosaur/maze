#include "catch.hpp"
#include "Maze.h"

TEST_CASE("Maze Basics", "[maze]")
{
    Maze maze(10, 10);
    REQUIRE(maze.isSolved() == false);
}
