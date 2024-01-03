#include "Maze.h"

Maze::Maze() {
    nodesHeight = 50;
    nodesWidth = 100;
    init();
}

Maze::Maze(int height_in, int width_in) {
    nodesHeight = height_in;
    nodesWidth = width_in;
    init();
}

Maze::~Maze() {
    
}

void Maze::init() {
    std::srand ( unsigned ( std::time(0) ) );

    player_node_x = 0;
    player_node_y = 0;
    solved = false;

    nodes.resize(nodesHeight);
    for (int row = 0; row < nodesHeight; ++row) {
        nodes[row].resize(nodesWidth, 0b1111);
    }

    visited.resize(nodesHeight);
    for (int row = 0; row < nodesHeight; ++row) {
        visited[row].resize(nodesWidth, false);
    }

    winHeight = 2 * nodesHeight + 1;
    winWidth = 5 * nodesWidth + 1;

    // calculate for a center placement of the window
    int stdscr_row;
    int stdscr_col;
    int start_x;
    int start_y;
    getmaxyx(stdscr, stdscr_row, stdscr_col);
    start_x = (stdscr_col - winWidth) / 2;
    start_y = (stdscr_row - winHeight) / 2;
    win = newwin(winHeight, winWidth, start_y, start_x);
    // keypad(win, TRUE);
    refresh();
}

std::pair<int, int> Maze::nodeToWinCoordinates(int node_y, int node_x) {
    return {2 * node_y + 1, 5 * node_x + 1};
}

void Maze::drawNode(int node_y, int node_x) {
    std::pair<int, int> winCoords = nodeToWinCoordinates(node_y, node_x);
    int win_y = winCoords.first;
    int win_x = winCoords.second;
    mvwprintw(win, win_y, win_x, "    ");
    int node_val = nodes[node_y][node_x];

    // Add walls in counter clockwise starting with right wall
    if (RIGHT_MASK & node_val) {
        mvwprintw(win, win_y, win_x + 4, "|");
    }
    else {
        mvwprintw(win, win_y, win_x + 4, " ");
    }
    if (UP_MASK & node_val) {
        mvwprintw(win, win_y - 1, win_x, "----");
    }
    else {
        mvwprintw(win, win_y - 1, win_x, "    ");
    }
    if (LEFT_MASK & node_val) {
        mvwprintw(win, win_y, win_x - 1, "|");
    }
    else {
        mvwprintw(win, win_y, win_x - 1, " ");
    }
    if (DOWN_MASK & node_val) {
        mvwprintw(win, win_y + 1, win_x, "----");
    }
    else {
        mvwprintw(win, win_y + 1, win_x, "    ");
    }

    // Add corners
    mvwprintw(win, win_y - 1, win_x - 1, "+");
    mvwprintw(win, win_y + 1, win_x - 1, "+");
    mvwprintw(win, win_y - 1, win_x + 4, "+");
    mvwprintw(win, win_y + 1, win_x + 4, "+");
}

void Maze::draw() {
    for (int node_y = 0; node_y < nodesHeight; ++node_y) {
        for (int node_x = 0; node_x < nodesWidth; ++node_x) {
            drawNode(node_y, node_x);
        }
    }

    int player_win_y = nodeToWinCoordinates(player_node_y, player_node_x).first;
    int player_win_x = nodeToWinCoordinates(player_node_y, player_node_x).second;
    mvwprintw(win, player_win_y, player_win_x, " :/ ");
    wrefresh(win);
}

void Maze::dfs(int node_y, int node_x) {
    visited[node_y][node_x] = true;

    // Randomize order in which neighbors are visited
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
                Maze::dfs(node_y + 1, node_x);
            }
            break;
        default:
            break;
        }
    }
    return;
}

void Maze::movePlayer() {
    int key_input = getch();
    switch (key_input)
    {
    case KEY_LEFT:
        if (!(LEFT_MASK & nodes[player_node_y][player_node_x])) {
            --player_node_x;
        }
        break;
    case KEY_RIGHT:
        if (!(RIGHT_MASK & nodes[player_node_y][player_node_x])) {
            ++player_node_x;
        }
        break;
    case KEY_UP:
        if (!(UP_MASK & nodes[player_node_y][player_node_x])) {
            --player_node_y;
        }
        break;
    case KEY_DOWN:
        if (!(DOWN_MASK & nodes[player_node_y][player_node_x])) {
            ++player_node_y;
        }
        break;
    default:
        break;
    }
    return;
}

bool Maze::isSolved() {
    if (player_node_x == nodesWidth - 1 && player_node_y == nodesHeight - 1) {
        return true;
    }
    else {
        return false;
    }
}