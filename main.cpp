#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
#include <iomanip>

int main() {
    // Set up the window
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Blitz");

    // Set up the font for text
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    // Set up the bold font for title
    sf::Font fontBold;
    if (!fontBold.loadFromFile("fontBold.otf")) {
        std::cerr << "Failed to load bold font!" << std::endl;
        return -1;
    }

    // Set up the text for time and score
    sf::Text timeText;
    sf::Text scoreText;
    sf::Text gameTitle;
    sf::Text gameInfo;

    gameTitle.setFont(fontBold);
    gameTitle.setCharacterSize(42);
    gameTitle.setFillColor(sf::Color::Black);

    timeText.setFont(font);
    timeText.setCharacterSize(35);
    timeText.setFillColor(sf::Color::Black);

    scoreText.setFont(font);
    scoreText.setCharacterSize(35);
    scoreText.setFillColor(sf::Color::Black);

    gameInfo.setFont(font);
    gameInfo.setCharacterSize(25);
    gameInfo.setFillColor(sf::Color::Black);

    // Set up the board
    static sf::RectangleShape board[8][8];
    sf::Texture textures[7];
    sf::Sprite sprites[8][8];
    const float cellSize = 62.0f;

    // Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(0)));

    for (int i = 0; i < 6; ++i) {
        std::string filename = "image" + std::to_string(i) + ".png";  // Adjust filenames as needed
        if (!textures[i].loadFromFile(filename)) {
            std::cerr << "Failed to load texture: " << filename << std::endl;
            return -1;
        }
    }

    // Assign random textures to each sprite and set scale
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j].setSize(sf::Vector2f(cellSize, cellSize));
            board[i][j].setPosition((i + 7) * cellSize, (j + 0.2) * cellSize);
            if ((i + j) % 2 == 0) {
                board[i][j].setFillColor(sf::Color(43, 42, 42)); // Grey
            }
            else {
                board[i][j].setFillColor(sf::Color(0, 0, 0)); // Black
            }

            int randomTextureIndex = std::rand() % 6;
            sprites[i][j].setTexture(textures[randomTextureIndex]);

            // Set the scale of the sprites
            float scale = cellSize / static_cast<float>(textures[randomTextureIndex].getSize().x);
            sprites[i][j].setScale(scale, scale);

            sprites[i][j].setPosition(board[i][j].getPosition());
        }
    }

    // Set up the clock
    sf::Clock clock;

    // Initialize the score
    int score = 0;

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Handle mouse click
                    // Add logic to detect the clicked block and perform swapping
                    // For simplicity, let's just change the texture of the clicked block
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    for (int i = 0; i < 8; ++i) {
                        for (int j = 0; j < 8; ++j) {
                            if (board[i][j].getGlobalBounds().contains(static_cast<float>(mouseX), static_cast<float>(mouseY))) {
                                // Assign a new random texture to the clicked block
                                int randomTextureIndex = std::rand() % 7;
                                sprites[i][j].setTexture(textures[randomTextureIndex]);
                            }
                        }
                    }
                }
            }
        }

        // Update time and score
        sf::Time elapsed = clock.getElapsedTime();
        int remainingSeconds = 60 - static_cast<int>(elapsed.asSeconds());
        if (remainingSeconds < 0) {
            remainingSeconds = 0;
        }

        // Update score every second
        score = elapsed.asSeconds();

        // Update text
        gameTitle.setString("Bejeweled Blitz");
        timeText.setString("Time Left: " + std::to_string(remainingSeconds) + " s");
        scoreText.setString("Score: " + std::to_string(score));
        gameInfo.setString("Game developed by M.Mujtaba and Harris Tabassum");

        // Adjust positions for separation
        gameTitle.setPosition(10.0f, 45.0f); //Adjust as needed
        timeText.setPosition(10.0f, 220.0f);  // Adjust as needed
        scoreText.setPosition(10.0f, 320.0f);  // Adjust as needed
        gameInfo.setPosition(50.0f, 550.0f);  // Adjust as needed

        // Clear the window
        window.clear();

        // Set the background color
        window.clear(sf::Color::White);  // Change to your desired background color

        // Draw the time and score text
        window.draw(gameTitle);
        window.draw(timeText);
        window.draw(scoreText);
        window.draw(gameInfo);

        // Draw the board
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                window.draw(board[i][j]);
                window.draw(sprites[i][j]);
            }
        }

        // Display the content
        window.display();

        // Exit the program when time is up
        if (remainingSeconds == 0) {
            window.close();
        }
    }

    return 0;
}
