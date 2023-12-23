#include <iostream>
#include <ncurses.h>
#include "Maze.h"

using namespace std;

int main(int argv, char** argc) 
{
    if (argv != 3) {
        std::cerr << "Error, usage is maze [maze height] [maze width]" << endl; 
        return 1;
    }
    int mazeHeight = atoi(argc[1]);
    int mazeWidth = atoi(argc[2]);

    // Start ncurses
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    noecho();

    // Create Maze
    Maze maze(mazeHeight, mazeWidth);
    Maze maze2(mazeHeight, mazeWidth);
    maze.draw();
    maze.dfs(0, 0);
    maze.draw();

    // main game loop
    while(!maze.isSolved()) {
        maze.movePlayer();
        maze.draw();
    }

    maze.printWinMessage("You WIN!");
    getch();

    // end ncurses
    endwin();
    return 0;
}