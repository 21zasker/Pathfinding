#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include "Map.h"

struct Position
{
    int row;
    int col;

    Position(int r, int c) : row(r), col(c) {}

    // Custom comparison operator for positions
    bool operator<(const Position &other) const
    {
        if (row == other.row)
        {
            return col < other.col;
        }
        return row < other.row;
    }
};

class Pathfinder
{
public:
    Pathfinder(std::vector<std::vector<Node>> &grid) : grid(grid)
    {
        findStartEndNodes();
    }

    void findStartEndNodes();
    void obtainPath();
    void visualizePath();
    std::vector<Position> getAdjacentNodes(const Position &pos);

    std::vector<std::vector<Node>> &grid;
    int startRow = -1;
    int startCol = -1;
    int endRow = -1;
    int endCol = -1;
    std::vector<std::pair<int, int>> pathPositions;
};

class BFS : public Pathfinder
{
public:
    BFS(std::vector<std::vector<Node>> &grid) : Pathfinder(grid)
    {
        findStartEndNodes();
        searchPath();
        visualizePath();
    }

    void searchPath();
};

class DFS : public Pathfinder
{
public:
    DFS(std::vector<std::vector<Node>> &grid) : Pathfinder(grid)
    {
        findStartEndNodes();
        searchPath();
        visualizePath();
    }

    void searchPath();
};

class Dijkstra : public Pathfinder
{
public:
    Dijkstra(std::vector<std::vector<Node>> &grid) : Pathfinder(grid)
    {
        findStartEndNodes();
        searchPath();
        visualizePath();
    }

    void searchPath();
};

class Astar : public Pathfinder
{
public:
    Astar(std::vector<std::vector<Node>> &grid) : Pathfinder(grid)
    {
        findStartEndNodes();
        searchPath();
        visualizePath();
    }

    void searchPath();
};