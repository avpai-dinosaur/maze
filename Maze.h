#include <vector>
#include <ncurses.h>
#include <utility>
#include <stack>
#include <string>
#include <string.h>
#include <random>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class Maze
{
private:
    std::vector<std::vector<int>> nodes;
    std::stack<int> stack;
    std::vector<std::vector<bool>> visited;
    int nodesHeight;
    int nodesWidth;
    int winHeight;
    int winWidth;
    int player_node_y;
    int player_node_x;
    bool solved;
    WINDOW *win;

    const int UP_MASK = 0b0010;
    const int DOWN_MASK = 0b1000;
    const int RIGHT_MASK = 0b0001;
    const int LEFT_MASK = 0b0100;

    // helper function for constructors to initialize nodes vector
    // and set ncurses window dimension
    void init();

    // Returns window coordinates (y, x)
    std::pair<int, int> nodeToWinCoordinates(int node_y, int node_x);

    // Draws node onto window. Each node is 3x3 and they overlap borders.
    void drawNode(int node_y, int node_x);

    // random generator function:
    static int myrandom(int i) { return std::rand() % i; }

public:
    Maze();

    Maze(int height_in, int width_in);
    ~Maze();

    // Draws entire maze and player
    void draw();

    // Performs randomized depth first search to
    // generate maze
    void dfs(int node_y, int node_x);

    // gets moves player using arrow keys
    void movePlayer();

    // returns if maze is solved or not
    bool isSolved();

    void printWinMessage(const char *message)
    {
        wclear(win);
        mvwprintw(win, winHeight / 2, (winWidth - strlen(message)) / 2, message);
        wrefresh(win);
        return;
    }
};