#include "Pathfinder.h"

void Astar::searchPath()
{
    std::priority_queue<std::pair<int, Position>, std::vector<std::pair<int, Position>>, std::greater<std::pair<int, Position>>> openSet;
    
    // Priority queue with the start node's position and estimated F score
    openSet.push(std::make_pair(0, Position(startRow, startCol)));

    std::vector<std::vector<int>> gScore(grid.size(), std::vector<int>(grid[0].size(), INT_MAX));
    
    // G score to start node as 0
    gScore[startRow][startCol] = 0;

    while (!openSet.empty())
    {
        Position current = openSet.top().second;
        openSet.pop();

        // Check if the current node is the "End" node
        if (current.row == endRow && current.col == endCol)
        {
            obtainPath();
            return;
        }

        // Mark the current node as visited if it's not the start node
        if (grid[current.row][current.col].type != Node::NodeType::Start)
        {
            grid[current.row][current.col].type = Node::NodeType::Visited;
        }

        // Get adjacent nodes for the current position
        std::vector<Position> adjacentNodes = getAdjacentNodes(current);
        for (const Position& adjNode : adjacentNodes)
        {
            int row = adjNode.row;
            int col = adjNode.col;

            // Check if the adjacent position is valid
            if (row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size() &&
                grid[row][col].type != Node::NodeType::Wall)
            {
                int tentativeGScore = gScore[current.row][current.col] + 1;

                // If the tentative G score is better than the current G score
                if (tentativeGScore < gScore[row][col])
                {
                    // Update G score, calculate H score and calculate F score
                    gScore[row][col] = tentativeGScore;
                    int hScore = std::abs(endRow - row) + std::abs(endCol - col);
                    int fScore = tentativeGScore + hScore;
                    openSet.push(std::make_pair(fScore, Position(row, col)));
                    grid[row][col].parent = std::make_pair(current.row, current.col);
                }
            }
        }
    }
}