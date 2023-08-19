#include "Pathfinder.h"

void Dijkstra::searchPath()
{
    std::priority_queue<std::pair<int, Position>, std::vector<std::pair<int, Position>>, std::greater<std::pair<int, Position>>> pq;
    
    // Priority queue with the start node's position and distance
    pq.push(std::make_pair(0, Position(startRow, startCol)));

    std::vector<std::vector<int>> distances(grid.size(), std::vector<int>(grid[0].size(), INT_MAX));

    // Distance to start node as 0
    distances[startRow][startCol] = 0;

    while (!pq.empty())
    {
        Position current = pq.top().second;
        int distance = pq.top().first;
        pq.pop();

        // Skip nodes that have been visited with a shorter distance
        if (distance > distances[current.row][current.col])
        {
            continue;
        }

        // Get adjacent nodes for the current position
        std::vector<Position> adjacentNodes = getAdjacentNodes(current);
        for (const Position &adjNode : adjacentNodes)
        {
            int row = adjNode.row;
            int col = adjNode.col;
            int newDistance = distance + 1; // Edge weight

            // Check if the new distance is shorter and the node is not a wall
            if (newDistance < distances[row][col] && grid[row][col].type != Node::NodeType::Wall)
            {
                if (grid[row][col].type == Node::NodeType::End)
                {
                    // Store parent node
                    grid[row][col].parent.first = current.row;
                    grid[row][col].parent.second = current.col;
                    obtainPath();
                    return;
                }

                // Update distances, mark as visited and enqueue the node
                distances[row][col] = newDistance;
                grid[row][col].type = Node::NodeType::Visited;
                pq.push(std::make_pair(newDistance, Position(row, col)));
                grid[row][col].parent.first = current.row;
                grid[row][col].parent.second = current.col;
            }
        }
    }
}