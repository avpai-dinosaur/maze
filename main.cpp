#include <iostream>
#include <ncurses.h>
#include "Maze.h"

using namespace std;

int main(int argv, char** argc) 
{
    if (argv != 3) {
        std::cerr << "Error, usage is main.exe [maze height] [maze width]" << endl; 
        return 1;
    }
    int mazeHeight = atoi(argc[1]);
    int mazeWidth = atoi(argc[2]);

    // Start ncurses
    initscr();

    Maze maze(mazeHeight, mazeWidth);
    maze.draw();
    std::srand ( unsigned ( std::time(0) ) );
    getch();

    maze.dfs(0, 0);
    maze.draw();
    
    getch();

    // end ncurses
    endwin();
    return 0;
}