#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

struct Node
{
    enum class NodeType
    {
        Empty,
        Wall,
        Visited,
        Start,
        Path,
        End
    };

    std::pair<int, int> parent; // Parent coordinates
    NodeType type;
    sf::RectangleShape shape;
    sf::Sprite nodeSprite;

    Node() : type(NodeType::Empty) {}
};

class Map
{
public:
    Map(int rows, int cols, int nodeSizeX, int nodeSizeY) :
        GRID_ROWS(rows), GRID_COLS(cols), NODE_SIZE_X(nodeSizeX), NODE_SIZE_Y(nodeSizeY),
        WINDOW_WIDTH(GRID_COLS * NODE_SIZE_X), WINDOW_HEIGHT(GRID_ROWS * NODE_SIZE_Y + 180) {

        // Initialize the grid of nodes
        grid.resize(GRID_ROWS, std::vector<Node>(GRID_COLS));

        // Set default tool and algorithm types
        tool_type = ToolType::None;
        alg_type = AlgorithmType::BFS;

        // Loop through rows and columns to initialize each node
        for (int y = 0; y < GRID_ROWS; ++y) {
            for (int x = 0; x < GRID_COLS; ++x) {
                Node& node = grid[y][x];
                node.shape.setSize(sf::Vector2f(NODE_SIZE_X, NODE_SIZE_Y));
                node.shape.setPosition(x * NODE_SIZE_X, y * NODE_SIZE_Y);

                // Default node type is Empty
                node.type = Node::NodeType::Empty;
                node.shape.setOutlineThickness(1.f);
                node.shape.setOutlineColor(GRID_COLOR);
            }
        }
    }

    TextureManager txtManager;

    // 2D vector to hold grid nodes
    std::vector<std::vector<Node>> grid;
    sf::RectangleShape menu;

    sf::ConvexShape button1;
    sf::ConvexShape button2;

    void drawMenu(sf::RenderWindow &window);
    void drawNodes(sf::RenderWindow &window, std::vector<std::vector<Node>> &grid);
    void drawGrid(sf::RenderWindow &window);
    void updateNodes(sf::RenderWindow &window);
    bool hasStartNode();
    bool hasEndNode();
    void updateTools(sf::RenderWindow &window);
    void emptyMap(std::vector<std::vector<Node>> &grid);

    void dungeonMap(sf::RenderWindow &window, std::vector<std::vector<Node>> &grid);
    void moveCharacter(std::vector<std::vector<Node>> &grid);

    int getWindowWidth(){
        return WINDOW_WIDTH;
    };

    int getWindowHeight(){
        return WINDOW_HEIGHT;
    };

    int getGridRows(){
        return GRID_ROWS;
    };

    int getNodeSizeY(){
        return NODE_SIZE_Y;
    }

    int getNodeSizeX(){
        return NODE_SIZE_X;
    }

    bool getStartStatus(){
        return startSearch;
    }

    void setStartDungeon(bool start){
        startMiniDungeon = start;
    }

    bool getStartDungeon(){
        return startMiniDungeon;
    }

    enum class AlgorithmType
    {
        BFS,
        DFS,
        Dijkstra,
        Astar
    };

    AlgorithmType alg_type;

    sf::Sprite cursor_sprite;

private:
    const int GRID_ROWS;
    const int GRID_COLS;
    const sf::Color GRID_COLOR = sf::Color::Black;

    const int NODE_SIZE_X;
    const int NODE_SIZE_Y;

    const int WINDOW_WIDTH = GRID_COLS * NODE_SIZE_X;
    const int WINDOW_HEIGHT = GRID_ROWS * NODE_SIZE_Y + 180;

    const sf::Color MENU_BACKGROUND_COLOR = sf::Color::Black;

    // Sprites for the UI Menu
    sf::Sprite pencil_sprite;
    sf::Sprite erase_sprite;
    sf::Sprite start_flag_sprite;
    sf::Sprite end_flag_sprite;
    sf::Sprite dungeon_sprite;

    // Text for the UI Menu
    sf::Font font;
    sf::Text start_text;
    sf::Text reset_text;
    sf::Text indication_text;
    sf::Text algorithm_text;

    bool startSearch = false;

    bool startMiniDungeon = false;

    enum class ToolType
    {
        Pencil,
        Eraser,
        StartFlag,
        EndFlag,
        None
    };

    ToolType tool_type;
};