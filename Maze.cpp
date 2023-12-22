#include "Maze.h"

Maze::Maze() {
    nodesHeight = 50;
    nodesWidth = 100;
    player_y = 1;
    player_x = 1;
    init();
}

Maze::Maze(int height_in, int width_in) {
    nodesHeight = height_in;
    nodesWidth = width_in;
    player_y = 1;
    player_x = 1;
    init();
}

Maze::~Maze() {
    
}

void Maze::init() {
    std::srand ( unsigned ( std::time(0) ) );

    nodes.resize(nodesHeight);
    for (int row = 0; row < nodesHeight; ++row) {
        nodes[row].resize(nodesWidth, 0b1111);
    }

    visited.resize(nodesHeight);
    for (int row = 0; row < nodesHeight; ++row) {
        visited[row].resize(nodesWidth, false);
    }

    winHeight = 2 * nodesHeight + 1;
    winWidth = 2 * nodesWidth + 1;
    win = newwin(winHeight, winWidth, 0, 0);
    refresh();
}

std::pair<int, int> Maze::nodeToWinCoordinates(int node_y, int node_x) {
    return {2 * node_y + 1, 2 * node_x + 1};
}

void Maze::drawNode(int node_y, int node_x) {
    std::pair<int, int> winCoords = nodeToWinCoordinates(node_y, node_x);
    int win_y = winCoords.first;
    int win_x = winCoords.second;
    mvwprintw(win, win_y, win_x, " ");
    int mask = 0b0001;
    int node_val = nodes[node_y][node_x];

    // Add walls in counter clockwise starting with right wall
    if (mask & node_val) {
        mvwprintw(win, win_y, win_x + 1, "#");
    }
    else {
        mvwprintw(win, win_y, win_x + 1, " ");
    }
    mask = mask << 1;
    if (mask & node_val) {
        mvwprintw(win, win_y - 1, win_x, "#");
    }
    else {
        mvwprintw(win, win_y - 1, win_x, " ");
    }
    mask = mask << 1;
    if (mask & node_val) {
        mvwprintw(win, win_y, win_x - 1, "#");
    }
    else {
        mvwprintw(win, win_y, win_x - 1, " ");
    } 
    mask = mask << 1;
    if (mask & node_val) {
        mvwprintw(win, win_y + 1, win_x, "#");
    }
    else {
        mvwprintw(win, win_y + 1, win_x, " ");
    }

    // Add borders
    mvwprintw(win, win_y - 1, win_x - 1, "#");
    mvwprintw(win, win_y + 1, win_x - 1, "#");
    mvwprintw(win, win_y - 1, win_x + 1, "#");
    mvwprintw(win, win_y + 1, win_x + 1, "#");
}

void Maze::draw() {
    for (int node_y = 0; node_y < nodesHeight; ++node_y) {
        for (int node_x = 0; node_x < nodesWidth; ++node_x) {
            drawNode(node_y, node_x);
        }
    }
    wrefresh(win);
}

void Maze::dfs(int node_y, int node_x) {
    // int win_y;
    // int win_x;
    // win_y = nodeToWinCoordinates(node_y, node_x).first;
    // win_x = nodeToWinCoordinates(node_y, node_x).second;
    visited[node_y][node_x] = true;

    std::vector<int> neighbors = {0, 1, 2, 3};
    std::random_shuffle(neighbors.begin(), neighbors.end(), myrandom);

    for (auto neighbor : neighbors) {
        switch (neighbor)
        {
        case 0: // right neighbor
            if (node_x == nodesWidth - 1) {
                // right neighbor is out of bounds
                continue;
            }
            else {
                if (visited[node_y][node_x + 1]) {
                    continue;
                }
                nodes[node_y][node_x] &= 0b1110;
                nodes[node_y][node_x + 1] &= 0b1011;
                // mvwprintw(win, win_y, win_x + 1, " ");
                Maze::dfs(node_y, node_x + 1);
            }
            break;
        case 1: // up neighbor
            if (node_y == 0) {
                // up neighbor is out of bounds
                continue;
            }
            else {
                if (visited[node_y - 1][node_x]) {
                    continue;
                }
                nodes[node_y][node_x] &= 0b1101;
                nodes[node_y - 1][node_x] &= 0b0111;
                // mvwprintw(win, win_y - 1, win_x, " ");
                Maze::dfs(node_y - 1, node_x);
            }
            break;
        case 2: // left neighbor
            if (node_x == 0) {
                // left neighbor is out of bounds
                continue;
            }
            else {
                if (visited[node_y][node_x - 1]) {
                    continue;
                }
                nodes[node_y][node_x] &= 0b1011;
                nodes[node_y][node_x - 1] &= 0b1110;
                // mvwprintw(win, win_y, win_x - 1, " ");
                Maze::dfs(node_y, node_x - 1);
            }
            break;
        case 3: // down neighbor
            if (node_y == nodesHeight - 1) {
                // down neighbor is out of bounds
                continue;
            }
            else {
                if (visited[node_y + 1][node_x]) {
                    continue;
                }
                nodes[node_y][node_x] &= 0b0111;
                nodes[node_y + 1][node_x] &= 0b1101;
                //mvwprintw(win, win_y + 1, win_x, " ");
                Maze::dfs(node_y + 1, node_x);
            }
            break;
        default:
            break;
        }
    }
    return;
}

void Maze::movePlayer(int y, int x) {
    mvwprintw(win, player_y, player_x, " ");
}