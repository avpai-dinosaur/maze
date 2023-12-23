# Maze Generator
This is a command line application which generates a random maze given height and width dimensions. The maze can then be solved by moving a simple player icon to the bottom right corner.

♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯
♯o  ♯           ♯           ♯           ♯
♯♯♯ ♯ ♯ ♯♯♯♯♯♯♯ ♯♯♯♯♯ ♯♯♯♯♯ ♯ ♯♯♯♯♯♯♯♯♯ ♯
♯   ♯ ♯   ♯   ♯ ♯   ♯ ♯     ♯     ♯   ♯ ♯
♯ ♯♯♯♯♯♯♯ ♯ ♯♯♯ ♯ ♯ ♯ ♯♯♯♯♯♯♯♯♯ ♯♯♯ ♯ ♯ ♯
♯ ♯     ♯ ♯     ♯ ♯   ♯         ♯   ♯ ♯ ♯
♯ ♯ ♯ ♯ ♯ ♯ ♯♯♯♯♯ ♯♯♯♯♯ ♯♯♯♯♯♯♯♯♯ ♯♯♯ ♯ ♯
♯ ♯ ♯ ♯   ♯   ♯   ♯     ♯ ♯   ♯   ♯   ♯ ♯
♯ ♯♯♯ ♯♯♯♯♯♯♯ ♯ ♯♯♯ ♯♯♯♯♯ ♯ ♯ ♯ ♯♯♯♯♯ ♯ ♯
♯     ♯     ♯ ♯           ♯ ♯   ♯   ♯   ♯
♯♯♯♯♯♯♯♯♯♯♯ ♯ ♯♯♯♯♯♯♯♯♯♯♯ ♯ ♯♯♯♯♯ ♯ ♯♯♯ ♯
♯       ♯   ♯       ♯ ♯   ♯       ♯ ♯   ♯
♯ ♯♯♯ ♯ ♯ ♯♯♯♯♯♯♯♯♯ ♯ ♯ ♯♯♯♯♯♯♯♯♯♯♯ ♯ ♯♯♯
♯ ♯ ♯ ♯   ♯       ♯ ♯ ♯   ♯   ♯   ♯ ♯ ♯ ♯
♯ ♯ ♯ ♯♯♯♯♯ ♯ ♯♯♯♯♯ ♯ ♯♯♯ ♯ ♯♯♯ ♯ ♯ ♯ ♯ ♯
♯   ♯     ♯ ♯       ♯       ♯   ♯   ♯   ♯
♯♯♯ ♯♯♯♯♯ ♯ ♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯ ♯ ♯♯♯♯♯♯♯♯♯ ♯
♯ ♯   ♯ ♯   ♯     ♯   ♯   ♯ ♯ ♯   ♯   ♯ ♯
♯ ♯♯♯ ♯ ♯♯♯♯♯♯♯ ♯ ♯ ♯ ♯ ♯ ♯♯♯ ♯ ♯♯♯ ♯ ♯ ♯
♯               ♯   ♯   ♯     ♯     ♯   ♯
♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯♯

## Getting Started
The following instruction aim to help get a copy of this project running on your local machine.

### Prerequisites
The project uses the ncurses library to display maze and player movement. Ncurses usually comes with installation. The [NCURSES Progamming HOW-TO](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html) guide by Pradeep Padala gives more information.

### Compiling
To compile the project run 

```
make maze
```

Alternatively, you can compile directly with

```
g++ -Wall -Werror -pedantic -g --std=c++17 -Wno-sign-compare -Wno-comment main.cpp Maze.cpp -lncurses -o maze
```

### Running
Run by calling maze executable and passing height and width arguments

```
./maze [height] [width]
```

## Algorithms
Currently the only maze generating algorithm implemented is depth-first search. More maze-generating algorithms can be implemented in the future so as to create mazes with differing characteristics.

## Potential Additions
1. Adding color elements to make maze more visible.
2. Randomized Kruskal's for maze generation.
3. Adding enemy entities to make traversing maze harder for player.
4. Adding time constraints to solving maze.
