#include "Pathfinder.h"

// Find the coordinates of the start and end nodes on the grid
void Pathfinder::findStartEndNodes()
{
    for (int row = 0; row < grid.size(); ++row)
    {
        for (int col = 0; col < grid[0].size(); ++col)
        {
            if (grid[row][col].type == Node::NodeType::Start)
            {
                startRow = row;
                startCol = col;
            }
            else if (grid[row][col].type == Node::NodeType::End)
            {
                endRow = row;
                endCol = col;
            }
        }
    }
}

// Obtain the adjacent nodes for a given node position
std::vector<Position> Pathfinder::getAdjacentNodes(const Position &pos)
{
    std::vector<Position> adjacentNodes;

    if (pos.row > 0)
    {
        adjacentNodes.emplace_back(pos.row - 1, pos.col);
    }
    if (pos.row < grid.size() - 1)
    {
        adjacentNodes.emplace_back(pos.row + 1, pos.col);
    }
    if (pos.col > 0)
    {
        adjacentNodes.emplace_back(pos.row, pos.col - 1);
    }
    if (pos.col < grid[0].size() - 1)
    {
        adjacentNodes.emplace_back(pos.row, pos.col + 1);
    }

    return adjacentNodes;
}

// Obtain the path through the parent nodes
void Pathfinder::obtainPath()
{
    int row = endRow;
    int col = endCol;

    while (row != startRow || col != startCol)
    {
        pathPositions.emplace_back(row, col);
        
        // Get the parent coordinates of the current node
        int parentRow = grid[row][col].parent.first;
        int parentCol = grid[row][col].parent.second;

        row = parentRow;
        col = parentCol;
    }

    // Add the start node to the path
    pathPositions.emplace_back(startRow, startCol);

    // Reverse the vector to ensure the correct order of nodes in the path
    std::reverse(pathPositions.begin(), pathPositions.end());
}

// Update node type to represent the path
void Pathfinder::visualizePath()
{
    for (const auto &pos : pathPositions)
    {
        int row = pos.first;
        int col = pos.second;
        if (grid[row][col].type != Node::NodeType::Start && grid[row][col].type != Node::NodeType::End)
        {
            grid[row][col].type = Node::NodeType::Path;
        }
    }
}