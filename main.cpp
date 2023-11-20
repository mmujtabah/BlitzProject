#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
#include <iomanip>

static sf::RectangleShape board[8][8];
static sf::Texture textures[7];
static sf::Sprite sprites[8][8];

int highlightedRow = 0;
int highlightedCol = 0;

// Initialize random seed
void RandomSeed()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
}

// Stores random images to textures and sets the sprite textures
void randTexScaleSprites(sf::Texture textures[], sf::Sprite sprites[][8], sf::RectangleShape board[][8], float cellSize)
{
    // Stores images in textures array
    for (int i = 0; i <= 6; ++i)
    {
        std::string filename = "image" + std::to_string(i) + ".png"; // Adjust filenames as needed
        if (!textures[i].loadFromFile(filename))
        {
            std::cerr << "Failed to load texture: " << filename << std::endl;
            return;
        }
        else {
            textures[i].setSmooth(true);
        }
    }

    // Assign random textures to each sprite and set scale
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j].setSize(sf::Vector2f(cellSize, cellSize));
            board[i][j].setPosition((i + 7.9) * cellSize, (j + 0.2) * cellSize);
            if ((i + j) % 2 == 0)
            {
                board[i][j].setFillColor(sf::Color(43, 42, 42)); // Grey
            }
            else
            {
                board[i][j].setFillColor(sf::Color(0, 0, 0)); // Black
            }

            int randomTextureIndex = rand() % 7;
            sprites[i][j].setTexture(textures[randomTextureIndex]);

            // Set the scale of the sprites
            float scale = cellSize / static_cast<float>(textures[randomTextureIndex].getSize().x);
            scale -= 0.07f;
            sprites[i][j].setScale(scale, scale);

            // Center the sprite within the board block
            float xOffset = (cellSize - sprites[i][j].getGlobalBounds().width) / 2.0f;
            float yOffset = (cellSize - sprites[i][j].getGlobalBounds().height) / 2.0f;
            sprites[i][j].setPosition(board[i][j].getPosition().x + xOffset, board[i][j].getPosition().y + yOffset);
        }
    }
}

void moveHighlight(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Left:
        highlightedRow = std::max(0, highlightedRow - 1);
        break;
    case sf::Keyboard::Right:
        highlightedRow = std::min(7, highlightedRow + 1);
        break;
    case sf::Keyboard::Up:
        highlightedCol = std::max(0, highlightedCol - 1);
        break;
    case sf::Keyboard::Down:
        highlightedCol = std::min(7, highlightedCol + 1);
        break;
    default:
        break;
    }
}

int main()
{
    // Set up the window
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Blitz", sf::Style::Close);

    // Set up the font for text
    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    // Set up the bold font for title
    sf::Font fontBold;
    if (!fontBold.loadFromFile("fontBold.otf"))
    {
        std::cerr << "Failed to load bold font!" << std::endl;
        return -1;
    }

    // Set up the text for time, score, title and info
    sf::Text timeText;
    sf::Text scoreText;
    sf::Text gameTitle;
    sf::Text gameInfo;

    gameTitle.setFont(fontBold);
    gameTitle.setCharacterSize(36);
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

    RandomSeed();

    // Set up the board
    const float cellSize = 62.0f;
    randTexScaleSprites(textures, sprites, board, cellSize);

    // Set up the clock
    sf::Clock clock;

    // Initialize the score
    int score = 0;

    // Declare a boolean flag to track Enter key status
    bool enterKeyPressed = false;


    // Load the sound buffer from a file
    sf::SoundBuffer soundBuffer;
    if (!soundBuffer.loadFromFile("select.wav"))
    {
        std::cerr << "Failed to load sound file!" << std::endl;
        return -1;
    }

    // Create a sound instance
    sf::Sound sound;
    sound.setBuffer(soundBuffer);

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {   
                
                if (event.key.code == sf::Keyboard::Enter) // To select a block
                {
                    // Set the flag to true when Enter is pressed
                    enterKeyPressed = true;
                    sound.play();
                }
                else if (event.key.code == sf::Keyboard::BackSpace)
                {
                    // Reset transparency when Backspace is pressed
                    enterKeyPressed = false;
                    sound.play();
                    
                }
                else if (!enterKeyPressed)
                {
                    // Move highlight if Enter is not pressed
                    moveHighlight(event.key.code);
                }
                else if (enterKeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left))
                {
                    // If a block is selected perform swap operation
                    
                }
            }
        }

        // Update time and score
        sf::Time elapsed = clock.getElapsedTime();
        int remainingSeconds = 60 - static_cast<int>(elapsed.asSeconds());
        if (remainingSeconds < 0)
        {
            remainingSeconds = 0;
        }

        // Update score every second
        score = elapsed.asSeconds();

        // Update text
        gameTitle.setString("Crytsal Crush Saga");
        timeText.setString("Time Left: 0:" + std::to_string(remainingSeconds) + " s");
        scoreText.setString("Score: " + std::to_string(score));
        gameInfo.setString("Game developed by M.Mujtaba and Harris Tabassum");

        // Adjust positions for separation
        gameTitle.setPosition(10.0f, 45.0f);    // Adjust as needed
        timeText.setPosition(10.0f, 220.0f);     // Adjust as needed
        scoreText.setPosition(10.0f, 320.0f);    // Adjust as needed
        gameInfo.setPosition(50.0f, 550.0f);    // Adjust as needed

        // Clear the window
        window.clear();

        // Set the background color
        window.clear(sf::Color(234, 182, 118)); // Change to your desired background color

        // Draw the time and score text
        window.draw(gameTitle);
        window.draw(timeText);
        window.draw(scoreText);
        window.draw(gameInfo);

        // Draw the board with highlight
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                window.draw(board[i][j]);
                window.draw(sprites[i][j]);
            }
        }

        // Draw the highlight with transparency and borders
        sf::RectangleShape highlight;
        highlight.setSize(sf::Vector2f(cellSize, cellSize));
        highlight.setPosition(board[highlightedRow][highlightedCol].getPosition());

        // Check the highlighted state to determine transparency
        if (enterKeyPressed)
        {
            // Adjust transparency and borders only if Enter was just pressed
            highlight.setFillColor(sf::Color(255, 255, 255, 100)); // Yellow with variable transparency
            highlight.setOutlineThickness(2.0f);                 // Border thickness
            highlight.setOutlineColor(sf::Color::Yellow);        // Border color
        }
        else 
        {
            // Default transparency and borders
            highlight.setFillColor(sf::Color(255, 255, 255, 0)); // Yellow with 100% transparency
            highlight.setOutlineThickness(2.0f);                 // Border thickness
            highlight.setOutlineColor(sf::Color::Yellow);        // Border color
        }

        // Draw the highlight
        window.draw(highlight);

        // Display the content
        window.display();

        // Exit the program after a delay when time is up
        if (remainingSeconds == 0)
        {
            sf::sleep(sf::seconds(2)); // Add a 2-second delay
            window.close();
        }
    }

    return 0;
}
