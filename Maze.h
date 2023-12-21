#include <vector>
#include <ncurses.h>
#include <utility>
#include <stack>
#include <string>
#include <random>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class Maze
{
private:
    std::vector<std::vector<int>> nodes;
    int nodesHeight;
    int nodesWidth;
    int winHeight;
    int winWidth;
    int player_y;
    int player_x;
    std::stack<int> stack;
    std::vector<std::vector<bool>> visited;
    WINDOW* win;

    const int UP = 1;
    const int DOWN = -1;
    const int RIGHT = 1;
    const int LEFT = -1;

    // helper function for constructors to initialize nodes vector
    // and set ncurses window dimension
    void init();

    // Returns window coordinates (y, x)
    std::pair<int, int> nodeToWinCoordinates(int node_y, int node_x);

    // Draws node onto window. Each node is 3x3 and they overlap borders.
    void drawNode(int node_y, int node_x);

    // random generator function:
    static int myrandom (int i) { return std::rand()%i;}

public:
    Maze();
    Maze(int height_in, int width_in);
    ~Maze();

    // Draws entire maze
    void draw();
    void dfs(int node_y, int node_x);
    void movePlayer(int y, int x);
};