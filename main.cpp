#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.h"
#include "Pathfinder.h"

int main()
{
    // Initialize the map with grid dimensions and node sizes
    Map map(40, 60, 20, 20);

    sf::RenderWindow window(sf::VideoMode(map.getWindowWidth(), map.getWindowHeight()), "Pathfinding - SFML", sf::Style::Close);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    if (map.button1.getGlobalBounds().intersects(map.cursor_sprite.getGlobalBounds()) && !map.getStartStatus())
                    {
                        switch (map.alg_type)
                        {
                        case Map::AlgorithmType::BFS:
                            map.alg_type = Map::AlgorithmType::Astar;
                            break;
                        case Map::AlgorithmType::Astar:
                            map.alg_type = Map::AlgorithmType::Dijkstra;
                            break;
                        case Map::AlgorithmType::Dijkstra:
                            map.alg_type = Map::AlgorithmType::DFS;
                            break;
                        case Map::AlgorithmType::DFS:
                            map.alg_type = Map::AlgorithmType::BFS;
                            break;
                        }
                    }
                    else if (map.button2.getGlobalBounds().intersects(map.cursor_sprite.getGlobalBounds()) && !map.getStartStatus())
                    {
                        switch (map.alg_type)
                        {
                        case Map::AlgorithmType::BFS:
                            map.alg_type = Map::AlgorithmType::DFS;
                            break;
                        case Map::AlgorithmType::DFS:
                            map.alg_type = Map::AlgorithmType::Dijkstra;
                            break;
                        case Map::AlgorithmType::Dijkstra:
                            map.alg_type = Map::AlgorithmType::Astar;
                            break;
                        case Map::AlgorithmType::Astar:
                            map.alg_type = Map::AlgorithmType::BFS;
                            break;
                        }
                    }
                }
            }
        }

        // Update Drawing tools
        map.updateTools(window);

        if (map.getStartStatus())
        {
            if (map.alg_type == Map::AlgorithmType::BFS)
            {
                BFS bfs(map.grid);
            }
            else if (map.alg_type == Map::AlgorithmType::DFS)
            {
                DFS dfs(map.grid);
            }
            else if (map.alg_type == Map::AlgorithmType::Dijkstra)
            {
                Dijkstra dijstra(map.grid);
            }
            else
            {
                Astar astar(map.grid);
            }
        }

        if (map.getStartDungeon())
        {
            map.moveCharacter(map.grid);
        }

        window.clear();

        if (!map.getStartDungeon())
        {
            map.updateNodes(window);
            map.drawGrid(window);
            map.drawNodes(window, map.grid);
        }
        else
        {
            map.dungeonMap(window, map.grid);
        }

        map.drawMenu(window);

        window.display();
    }
    return 0;
}