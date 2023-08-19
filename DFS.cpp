#include "Pathfinder.h"

void DFS::searchPath()
{
    std::stack<Position> s;
    s.push(Position(startRow, startCol));

    while (!s.empty())
    {
        Position current = s.top();
        s.pop();

        // Get adjacent nodes for the current position
        std::vector<Position> adjacentNodes = getAdjacentNodes(current);
        for (const Position &adjNode : adjacentNodes)
        {
            int row = adjNode.row;
            int col = adjNode.col;

            // Check if the current adjacent node is the "End" node
            if (grid[row][col].type == Node::NodeType::End)
            {
                // Store parent node
                grid[row][col].parent.first = current.row;
                grid[row][col].parent.second = current.col;

                obtainPath();

                return;
            }

            // Check if the adjacent node is valid (not a wall and not visited)
            else if (grid[row][col].type == Node::NodeType::Empty)
            {
                s.push(Position(row, col));
                
                // Store parent node
                grid[row][col].parent.first = current.row;
                grid[row][col].parent.second = current.col;
                grid[row][col].type = Node::NodeType::Visited;
            }
        }
    }
}