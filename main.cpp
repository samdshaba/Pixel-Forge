#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include <ctime>
#include <sstream>
#include <iostream>

// Window and grid settings
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int GRID_SIZE = 40;
const int GRID_WIDTH = WINDOW_WIDTH / GRID_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / GRID_SIZE;

// Player settings
const float PLAYER_SPEED = 200.0f;

// Resource settings
const int MAX_RESOURCES = 20;

// Item types
enum class ItemType { None, Wood, Stone, Axe, Pickaxe, House };

class PixelForge {
private:
    sf::RenderWindow window;
    sf::RectangleShape player;
    std::vector<std::vector<ItemType>> grid;
    std::vector<sf::RectangleShape> resourceShapes;
    sf::Vector2i playerGridPos;
    int woodCount, stoneCount, score;
    ItemType selectedItem;
    sf::Font font;
    sf::Text hudText;
    sf::Sound collectSound, craftSound, buildSound;
    sf::SoundBuffer collectBuffer, craftBuffer, buildBuffer;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

public:
    PixelForge() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pixel Forge"),
                   gen(rd()), dist(1, 3) {
        window.setFramerateLimit(60);

        // Initialize player
        player.setSize(sf::Vector2f(GRID_SIZE - 2, GRID_SIZE - 2));
        player.setFillColor(sf::Color::Cyan);
        playerGridPos = sf::Vector2i(GRID_WIDTH / 2, GRID_HEIGHT / 2);
        player.setPosition(playerGridPos.x * GRID_SIZE, playerGridPos.y * GRID_SIZE);

        // Initialize grid
        grid.resize(GRID_HEIGHT, std::vector<ItemType>(GRID_WIDTH, ItemType::None));
        resourceShapes.resize(MAX_RESOURCES);
        for (int i = 0; i < MAX_RESOURCES; ++i) {
            int x = dist(gen) * 2, y = dist(gen) * 2;
            while (grid[y][x] != ItemType::None || (x == playerGridPos.x && y == playerGridPos.y)) {
                x = dist(gen) * 2;
                y = dist(gen) * 2;
            }
            grid[y][x] = (dist(gen) % 2 == 0) ? ItemType::Wood : ItemType::Stone;
            sf::RectangleShape resource(sf::Vector2f(GRID_SIZE - 4, GRID_SIZE - 4));
            resource.setPosition(x * GRID_SIZE + 2, y * GRID_SIZE + 2);
            resource.setFillColor((grid[y][x] == ItemType::Wood) ? sf::Color(139, 69, 19) : sf::Color::Gray);
            resourceShapes[i] = resource;
        }

        // Initialize HUD
        woodCount = 0;
        stoneCount = 0;
        score = 0;
        selectedItem = ItemType::None;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font\n";
        }
        hudText.setFont(font);
        hudText.setCharacterSize(20);
        hudText.setFillColor(sf::Color::White);
        hudText.setPosition(10.0f, 10.0f);

        // Initialize sounds
        if (!collectBuffer.loadFromFile("collect.wav")) {
            std::cerr << "Error loading collect sound\n";
        }
        if (!craftBuffer.loadFromFile("craft.wav")) {
            std::cerr << "Error loading craft sound\n";
        }
        if (!buildBuffer.loadFromFile("build.wav")) {
            std::cerr << "Error loading build sound\n";
        }
        collectSound.setBuffer(collectBuffer);
        craftSound.setBuffer(craftBuffer);
        buildSound.setBuffer(buildBuffer);
    }

    void handleInput() {
        // Movement
        sf::Vector2i newPos = playerGridPos;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && playerGridPos.x > 0) newPos.x--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playerGridPos.x < GRID_WIDTH - 1) newPos.x++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && playerGridPos.y > 0) newPos.y--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && playerGridPos.y < GRID_HEIGHT - 1) newPos.y++;

        // Collect resources
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && grid[playerGridPos.y][playerGridPos.x] != ItemType::None) {
            if (grid[playerGridPos.y][playerGridPos.x] == ItemType::Wood) woodCount++;
            else if (grid[playerGridPos.y][playerGridPos.x] == ItemType::Stone) stoneCount++;
            grid[playerGridPos.y][playerGridPos.x] = ItemType::None;
            collectSound.play();
            score += 5;
        }

        // Craft items
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && woodCount >= 3) {
            woodCount -= 3;
            selectedItem = ItemType::Axe;
            craftSound.play();
            score += 10;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && stoneCount >= 3) {
            stoneCount -= 3;
            selectedItem = ItemType::Pickaxe;
            craftSound.play();
            score += 10;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && woodCount >= 5 && stoneCount >= 5) {
            woodCount -= 5;
            stoneCount -= 5;
            selectedItem = ItemType::House;
            craftSound.play();
            score += 20;
        }

        // Build
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && selectedItem != ItemType::None &&
            grid[newPos.y][newPos.x] == ItemType::None) {
            grid[newPos.y][newPos.x] = selectedItem;
            buildSound.play();
            score += (selectedItem == ItemType::House) ? 50 : 20;
            selectedItem = ItemType::None;
        }

        // Update player position
        if (grid[newPos.y][newPos.x] == ItemType::None || grid[newPos.y][newPos.x] == ItemType::Wood || grid[newPos.y][newPos.x] == ItemType::Stone) {
            playerGridPos = newPos;
            player.setPosition(playerGridPos.x * GRID_SIZE, playerGridPos.y * GRID_SIZE);
        }
    }

    void update(float dt) {
        // Update HUD
        std::stringstream ss;
        ss << "Wood: " << woodCount << " | Stone: " << stoneCount << " | Score: " << score << "\n"
           << "Selected: " << (selectedItem == ItemType::Axe ? "Axe" : selectedItem == ItemType::Pickaxe ? "Pickaxe" : selectedItem == ItemType::House ? "House" : "None");
        hudText.setString(ss.str());
    }

    void render() {
        window.clear(sf::Color::Black);

        // Draw grid
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            for (int x = 0; x < GRID_WIDTH; ++x) {
                sf::RectangleShape tile(sf::Vector2f(GRID_SIZE - 1, GRID_SIZE - 1));
                tile.setPosition(x * GRID_SIZE, y * GRID_SIZE);
                if (grid[y][x] == ItemType::Wood) tile.setFillColor(sf::Color(139, 69, 19));
                else if (grid[y][x] == ItemType::Stone) tile.setFillColor(sf::Color::Gray);
                else if (grid[y][x] == ItemType::Axe) tile.setFillColor(sf::Color::Yellow);
                else if (grid[y][x] == ItemType::Pickaxe) tile.setFillColor(sf::Color::Magenta);
                else if (grid[y][x] == ItemType::House) tile.setFillColor(sf::Color::Green);
                else tile.setFillColor(sf::Color(50, 50, 50));
                window.draw(tile);
            }
        }

        window.draw(player);
        window.draw(hudText);
        window.display();
    }

    void run() {
        sf::Clock clock;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            float dt = clock.restart().asSeconds();
            handleInput();
            update(dt);
            render();
        }
    }
};

int main() {
    PixelForge game;
    game.run();
    return 0;
}
