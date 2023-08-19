#include "Map.h"

void Map::updateNodes(sf::RenderWindow &window)
{
    // Bresenham's Line Algorithm is used to efficiently calculate the coordinates of a line between two points.
    // The basic idea behind the algorithm is to determine which pixels should be filled in along the
    // line between two points on a grid

    sf::Vector2i currentPosition = sf::Mouse::getPosition(window);
    static sf::Vector2i previousPosition = currentPosition;

    // Calculate grid coordinates for the previous and current mouse positions
    int x1 = previousPosition.x / NODE_SIZE_X;
    int y1 = previousPosition.y / NODE_SIZE_Y;
    int x2 = currentPosition.x / NODE_SIZE_X;
    int y2 = currentPosition.y / NODE_SIZE_Y;

    // Calculate the differences between the target and current positions
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    
    // Determine the directional increments for x and y
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    // Error term for linear interpolation
    int error = dx - dy;
    
    // Initialize starting positions
    int x = x1;
    int y = y1;

    while (true)
    {
        // Check if the current position is within the grid bounds
        if (x >= 0 && x < GRID_COLS && y >= 0 && y < GRID_ROWS)
        {
            Node &node = grid[y][x];
            
            // Update the node based on the tool type and mouse button
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !startSearch)
            {
                if (tool_type == ToolType::Pencil)
                {
                    if (node.type == Node::NodeType::Empty)
                    {
                        node.type = Node::NodeType::Wall;
                    }
                }
                else if (tool_type == ToolType::Eraser)
                {
                    if (node.type == Node::NodeType::Wall || node.type == Node::NodeType::Start || node.type == Node::NodeType::End)
                    {
                        node.type = Node::NodeType::Empty;
                    }
                }
                else if (tool_type == ToolType::StartFlag)
                {
                    if (node.type == Node::NodeType::Empty && !hasStartNode())
                    {
                        node.type = Node::NodeType::Start;
                    }
                }
                else if (tool_type == ToolType::EndFlag)
                {
                    if (node.type == Node::NodeType::Empty && !hasEndNode())
                    {
                        node.type = Node::NodeType::End;
                    }
                }
            }
        }

        // Exit loop if the current position matches the target
        if (x == x2 && y == y2)
        {
            break;
        }

        // Apply linear interpolation
        int e2 = 2 * error;
        if (e2 > -dy)
        {
            error -= dy;
            x += sx;
        }
        if (e2 < dx)
        {
            error += dx;
            y += sy;
        }
    }

    // Update the previous mouse position for the next iteration
    previousPosition = currentPosition;
}

bool Map::hasStartNode()
{
    for (const auto &row : grid)
    {
        for (const auto &node : row)
        {
            if (node.type == Node::NodeType::Start)
            {
                return true;
            }
        }
    }
    return false;
}

bool Map::hasEndNode()
{
    for (const auto &row : grid)
    {
        for (const auto &node : row)
        {
            if (node.type == Node::NodeType::End)
            {
                return true;
            }
        }
    }
    return false;
}

void Map::updateTools(sf::RenderWindow &window)
{
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
    cursor_sprite.setPosition(mousePosition);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (pencil_sprite.getGlobalBounds().contains(cursor_sprite.getPosition()) && !startSearch)
        {
            tool_type = ToolType::Pencil;
            window.setMouseCursorVisible(false);
            cursor_sprite.setTexture(txtManager.cursor_texture);
            cursor_sprite.setTextureRect(sf::IntRect(0, 1, 20, 25));
        }
        else if (erase_sprite.getGlobalBounds().contains(cursor_sprite.getPosition()) && !startSearch)
        {
            tool_type = ToolType::Eraser;
            window.setMouseCursorVisible(false);
            cursor_sprite.setTexture(txtManager.cursor_texture);
            cursor_sprite.setTextureRect(sf::IntRect(22, 2, 16, 24));
        }
        else if (start_flag_sprite.getGlobalBounds().contains(cursor_sprite.getPosition()) && !startSearch)
        {
            tool_type = ToolType::StartFlag;
            window.setMouseCursorVisible(false);
            cursor_sprite.setTexture(txtManager.cursor_texture);
            cursor_sprite.setTextureRect(sf::IntRect(4, 28, 16, 26));
        }
        else if (end_flag_sprite.getGlobalBounds().contains(cursor_sprite.getPosition()) && !startSearch)
        {
            tool_type = ToolType::EndFlag;
            window.setMouseCursorVisible(false);
            cursor_sprite.setTexture(txtManager.cursor_texture);
            cursor_sprite.setTextureRect(sf::IntRect(22, 28, 16, 26));
        }
        else if (start_text.getGlobalBounds().contains(cursor_sprite.getPosition()))
        {
            startSearch = true;
            window.setMouseCursorVisible(true);
        }
        else if (reset_text.getGlobalBounds().contains(cursor_sprite.getPosition()))
        {
            window.setMouseCursorVisible(false);
            emptyMap(grid);
        }
        else if (dungeon_sprite.getGlobalBounds().contains(cursor_sprite.getPosition()) && startSearch)
        {
            startMiniDungeon = true;
        }
    }
}

void Map::emptyMap(std::vector<std::vector<Node>> &grid)
{
    for (auto &row : grid)
    {
        for (auto &node : row)
        {
            node.type = Node::NodeType::Empty;
        }
    }

    startSearch = false;
    startMiniDungeon = false;
    tool_type = ToolType::None;
}

void Map::drawNodes(sf::RenderWindow &window, std::vector<std::vector<Node>> &grid)
{
    for (auto &row : grid)
    {
        for (auto &node : row)
        {
            switch (node.type)
            {
            case Node::NodeType::Empty:
                node.shape.setFillColor(sf::Color::White);
                break;
            case Node::NodeType::Wall:
                node.shape.setFillColor(sf::Color::Black);
                break;
            case Node::NodeType::Start:
                node.shape.setFillColor(sf::Color::Green);
                break;
            case Node::NodeType::End:
                node.shape.setFillColor(sf::Color::Red);
                break;
            case Node::NodeType::Visited:
                node.shape.setFillColor(sf::Color::Blue);
                break;
            case Node::NodeType::Path:
                node.shape.setFillColor(sf::Color::Yellow);
            }

            window.draw(node.shape);
        }
    }
}

void Map::drawGrid(sf::RenderWindow &window)
{
    for (int y = 0; y <= GRID_ROWS; ++y)
    {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, y * NODE_SIZE_Y)),
            sf::Vertex(sf::Vector2f(WINDOW_WIDTH, y * NODE_SIZE_Y))};
        window.draw(line, 2, sf::Lines);
    }

    for (int x = 0; x <= GRID_COLS; ++x)
    {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x * NODE_SIZE_X, 0)),
            sf::Vertex(sf::Vector2f(x * NODE_SIZE_X, WINDOW_HEIGHT - 180))};
        window.draw(line, 2, sf::Lines);
    }
}

void Map::drawMenu(sf::RenderWindow &window)
{
    menu.setSize(sf::Vector2f(WINDOW_WIDTH, 180));
    menu.setFillColor(MENU_BACKGROUND_COLOR);
    menu.setPosition(0, GRID_ROWS * NODE_SIZE_Y);

    if (!startSearch)
    {
        pencil_sprite.setTexture(txtManager.icons_texture);
        erase_sprite.setTexture(txtManager.icons_texture);
        end_flag_sprite.setTexture(txtManager.icons_texture);
        start_flag_sprite.setTexture(txtManager.icons_texture);
        dungeon_sprite.setTexture(txtManager.no_icons_texture);
    }
    else
    {
        pencil_sprite.setTexture(txtManager.no_icons_texture);
        erase_sprite.setTexture(txtManager.no_icons_texture);
        end_flag_sprite.setTexture(txtManager.no_icons_texture);
        start_flag_sprite.setTexture(txtManager.no_icons_texture);
        dungeon_sprite.setTexture(txtManager.icons_texture);
    }

    pencil_sprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
    pencil_sprite.setScale(3.0f, 3.0f);
    pencil_sprite.setPosition(700, GRID_ROWS * NODE_SIZE_Y + 20);

    erase_sprite.setTextureRect(sf::IntRect(26, 0, 24, 24));
    erase_sprite.setScale(3.0f, 3.0f);
    erase_sprite.setPosition(800, GRID_ROWS * NODE_SIZE_Y + 20);

    end_flag_sprite.setTextureRect(sf::IntRect(0, 26, 24, 24));
    end_flag_sprite.setScale(3.0f, 3.0f);
    end_flag_sprite.setPosition(900, GRID_ROWS * NODE_SIZE_Y + 20);

    start_flag_sprite.setTextureRect(sf::IntRect(26, 26, 24, 24));
    start_flag_sprite.setScale(3.0f, 3.0f);
    start_flag_sprite.setPosition(1000, GRID_ROWS * NODE_SIZE_Y + 20);

    dungeon_sprite.setTextureRect(sf::IntRect(0, 52, 24, 24));
    dungeon_sprite.setScale(3.0f, 3.0f);
    dungeon_sprite.setPosition(1100, GRID_ROWS * NODE_SIZE_Y + 20);

    font.loadFromFile("Assets/PressStart2P.ttf");
    start_text.setFont(font);
    start_text.setString("Start");
    start_text.setCharacterSize(24);
    start_text.setFillColor(sf::Color(0x31, 0xA8, 0x54));
    start_text.setPosition(700, GRID_ROWS * NODE_SIZE_Y + 125);

    reset_text.setFont(font);
    reset_text.setString("Reset");
    reset_text.setCharacterSize(24);
    reset_text.setFillColor(sf::Color(0xF62944FF));
    reset_text.setPosition(900, GRID_ROWS * NODE_SIZE_Y + 125);

    indication_text.setFont(font);
    indication_text.setString("Algorithm used:");
    indication_text.setCharacterSize(26);
    indication_text.setFillColor(sf::Color::White);
    indication_text.setPosition(100, GRID_ROWS * NODE_SIZE_Y + 30);

    algorithm_text.setFont(font);
    algorithm_text.setCharacterSize(28);
    algorithm_text.setFillColor(sf::Color::White);

    if (alg_type == AlgorithmType::BFS)
    {
        algorithm_text.setString("BFS");
        algorithm_text.setPosition(200, GRID_ROWS * NODE_SIZE_Y + 110);
    }
    else if (alg_type == AlgorithmType::DFS)
    {
        algorithm_text.setString("DFS");
        algorithm_text.setPosition(200, GRID_ROWS * NODE_SIZE_Y + 110);
    }
    else if (alg_type == AlgorithmType::Dijkstra)
    {
        algorithm_text.setString("Dijkstra");
        algorithm_text.setPosition(145, GRID_ROWS * NODE_SIZE_Y + 110);
    }
    else if (alg_type == AlgorithmType::Astar)
    {
        algorithm_text.setString("A*");
        algorithm_text.setPosition(220, GRID_ROWS * NODE_SIZE_Y + 110);
    }

    button1.setPointCount(3);
    button1.setPoint(0, sf::Vector2f(108, GRID_ROWS * NODE_SIZE_Y + 100));
    button1.setPoint(1, sf::Vector2f(100, GRID_ROWS * NODE_SIZE_Y + 116));
    button1.setPoint(2, sf::Vector2f(108, GRID_ROWS * NODE_SIZE_Y + 132));
    button1.setFillColor(sf::Color::White);

    button2.setPointCount(3);
    button2.setPoint(0, sf::Vector2f(395, GRID_ROWS * NODE_SIZE_Y + 100));
    button2.setPoint(1, sf::Vector2f(403, GRID_ROWS * NODE_SIZE_Y + 116));
    button2.setPoint(2, sf::Vector2f(395, GRID_ROWS * NODE_SIZE_Y + 132));
    button2.setFillColor(sf::Color::White);

    window.draw(menu);
    window.draw(pencil_sprite);
    window.draw(erase_sprite);
    window.draw(start_flag_sprite);
    window.draw(end_flag_sprite);
    window.draw(dungeon_sprite);
    window.draw(start_text);
    window.draw(reset_text);
    window.draw(indication_text);
    window.draw(algorithm_text);
    window.draw(button1);
    window.draw(button2);

    if (!startSearch)
        window.draw(cursor_sprite);
}

void Map::dungeonMap(sf::RenderWindow &window, std::vector<std::vector<Node>> &grid)
{   
    for (int y = 0; y < GRID_ROWS; ++y)
    {
        for (int x = 0; x < GRID_COLS; ++x)
        {
            Node &node = grid[y][x];

            node.nodeSprite.setTexture(txtManager.dungeon_texture);

            switch (node.type)
            {
            case Node::NodeType::Empty:
                node.nodeSprite.setTextureRect(sf::IntRect(12, 1, 10, 10));
                node.nodeSprite.setScale(2.0f, 2.0f);
                node.nodeSprite.setPosition(x * NODE_SIZE_X, y * NODE_SIZE_Y);
                break;
            case Node::NodeType::Wall:
                node.nodeSprite.setTextureRect(sf::IntRect(1, 1, 10, 10));
                node.nodeSprite.setScale(2.0f, 2.0f);
                node.nodeSprite.setPosition(x * NODE_SIZE_X, y * NODE_SIZE_Y);
                break;
            case Node::NodeType::Start:
                node.nodeSprite.setTextureRect(sf::IntRect(23, 23, 10, 10));
                node.nodeSprite.setScale(2.0f, 2.0f);
                node.nodeSprite.setPosition(x * NODE_SIZE_X, y * NODE_SIZE_Y);
                break;
            case Node::NodeType::End:
                node.nodeSprite.setTextureRect(sf::IntRect(12, 23, 10, 10));
                node.nodeSprite.setScale(2.0f, 2.0f);
                node.nodeSprite.setPosition(x * NODE_SIZE_X, y * NODE_SIZE_Y);
                break;
            case Node::NodeType::Visited:
                node.nodeSprite.setTextureRect(sf::IntRect(12, 1, 10, 10));
                node.nodeSprite.setScale(2.0f, 2.0f);
                node.nodeSprite.setPosition(x * NODE_SIZE_X, y * NODE_SIZE_Y);
                break;
            case Node::NodeType::Path:
                node.nodeSprite.setTextureRect(sf::IntRect(34, 1, 10, 10));
                node.nodeSprite.setScale(2.0f, 2.0f);
                node.nodeSprite.setPosition(x * NODE_SIZE_X, y * NODE_SIZE_Y);
            }

            window.draw(node.nodeSprite);
        }
    }
}

void Map::moveCharacter(std::vector<std::vector<Node>> &grid)
{
    Node *startNode = nullptr;

    // Find the starting node
    for (int y = 0; y < GRID_ROWS; ++y)
    {
        for (int x = 0; x < GRID_COLS; ++x)
        {
            if (grid[y][x].type == Node::NodeType::Start)
            {
                startNode = &grid[y][x];
                break;
            }
        }
        if (startNode)
        {
            break;
        }
    }

    int startRow = startNode->shape.getPosition().y / NODE_SIZE_Y;
    int startCol = startNode->shape.getPosition().x / NODE_SIZE_X;

    // Find the next node of Path type with the same row and column as the starting node
    Node *nextPathNode = nullptr;

    for (int y = 0; y < GRID_ROWS; ++y)
    {
        for (int x = 0; x < GRID_COLS; ++x)
        {
            if (grid[y][x].type == Node::NodeType::Path && grid[y][x].parent == std::make_pair(startRow, startCol))
            {
                nextPathNode = &grid[y][x];
                break;
            }
        }
        if (nextPathNode)
        {
            break;
        }
    }

    if (nextPathNode)
    {
        // Change the starting node to the next Path node
        startNode->type = Node::NodeType::Visited;
        nextPathNode->type = Node::NodeType::Start;
        sf::sleep(sf::milliseconds(200)); // Introduce a delay for visualization
    }
}