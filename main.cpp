#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
#include <iomanip>

// Initialize random seed
void RandomSeed()
{
    std::srand(std::time(0));
}
// Center the sprite within the board block
void spriteScaleCenter(sf::RectangleShape board[][8], sf::Sprite sprites[][8], float cellSize, int row, int col, float scale)
{
    sprites[row][col].setScale(scale, scale);
    float xOffset = (cellSize - sprites[row][col].getGlobalBounds().width) / 2.0f;
    float yOffset = (cellSize - sprites[row][col].getGlobalBounds().height) / 2.0f;
    sprites[row][col].setPosition(board[row][col].getPosition().x + xOffset, board[row][col].getPosition().y + yOffset);
}

// Stores random images to textures and sets the sprite textures
void randTexturesSprites(sf::Texture textures[], sf::Sprite sprites[][8], sf::RectangleShape board[][8], float cellSize, float scales[])
{
    // Stores images in textures array
    if (!textures[0].loadFromFile("image0.png"))
    {
        std::cout << "Failed to load texture: " << "image0.png" << std::endl;
        return;
    }
    if (!textures[1].loadFromFile("image1.png"))
    {
        std::cout << "Failed to load texture: " << "image1.png" << std::endl;
        return;
    }
    if (!textures[2].loadFromFile("image2.png"))
    {
        std::cout << "Failed to load texture: " << "image2.png" << std::endl;
        return;
    }
    if (!textures[3].loadFromFile("image3.png"))
    {
        std::cout << "Failed to load texture: " << "image3.png" << std::endl;
        return;
    }
    if (!textures[4].loadFromFile("image4.png"))
    {
        std::cout << "Failed to load texture: " << "image4.png" << std::endl;
        return;
    }
    if (!textures[5].loadFromFile("image5.png"))
    {
        std::cout << "Failed to load texture: " << "image5.png" << std::endl;
        return;
    }
    if (!textures[6].loadFromFile("image6.png"))
    {
        std::cout << "Failed to load texture: " << "image6.png" << std::endl;
        return;
    }
    // Set the smooth property for the texture
    for (int i = 0; i <= 6; i++)
    {
        textures[i].setSmooth(true);
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

            // Store the scale value in the array
            scales[randomTextureIndex] = scale;

            spriteScaleCenter(board, sprites, cellSize, i, j, scale);
        }
    }
}

void moveHighlight(sf::Keyboard::Key key, int& highlightedRow, int& highlightedCol)
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

void swap(sf::RectangleShape board[][8], sf::Sprite sprites[][8], sf::Texture textures[], float scales[], sf::Keyboard::Key key, bool& enterKeyPressed, float cellSize, int& highlightedRow, int& highlightedCol)
{
    // Check if the highlighted position is valid
    if (highlightedRow >= 0 && highlightedRow < 8 && highlightedCol >= 0 && highlightedCol < 8)
    {
        // Determine the target position based on the arrow key pressed
        int targetRow = highlightedRow;
        int targetCol = highlightedCol;

        // Check the arrow key pressed and update the target position accordingly
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            targetCol = std::max(0, highlightedCol - 1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            targetCol = std::min(7, highlightedCol + 1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            targetRow = std::max(0, highlightedRow - 1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            targetRow = std::min(7, highlightedRow + 1);
        }

        // Check if the target position is valid
        if (targetRow >= 0 && targetRow < 8 && targetCol >= 0 && targetCol < 8)
        {
            // Swap the sprites (visual representation)
            std::swap(sprites[highlightedRow][highlightedCol], sprites[targetRow][targetCol]);

            // Update the positions of the swapped sprites
            float xOffset, yOffset;

            // Get the texture index of the highlighted sprite
            int highlightedTextureIndex = 0;
            for (int i = 0; i < 7; ++i)
            {
                if (sprites[highlightedRow][highlightedCol].getTexture() == &textures[i])
                {
                    highlightedTextureIndex = i;
                    break;
                }
            }
            spriteScaleCenter(board, sprites, cellSize, highlightedRow, highlightedCol, scales[highlightedTextureIndex]);

            // Get the texture index of the target sprite
            int targetTextureIndex = 0;
            for (int i = 0; i < 7; i++)
            {
                if (sprites[targetRow][targetCol].getTexture() == &textures[i])
                {
                    targetTextureIndex = i;
                    break;
                }
            }

            spriteScaleCenter(board, sprites, cellSize, targetRow, targetCol, scales[targetTextureIndex]);

            // Reset the enter key pressed flag
            enterKeyPressed = false;
        }
        highlightedRow = targetRow;
        highlightedCol = targetCol;
    }
}

// Function to initialize the board
void initializeBoard(sf::RectangleShape board[][8], sf::Sprite sprites[][8], sf::Texture textures[], float scales[], int& highlightedRow, int& highlightedCol, float cellSize)
{
    highlightedRow = 0;
    highlightedCol = 0;

    // Reset textures, board, and sprites arrays
    for (int i = 0; i < 7; i++)
    {
        textures[i] = sf::Texture();
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = sf::RectangleShape();
            sprites[i][j] = sf::Sprite();
        }
    }

    randTexturesSprites(textures, sprites, board, cellSize, scales);
}


int main()
{
    static sf::RectangleShape board[8][8];
    static sf::Texture textures[7];
    static sf::Sprite sprites[8][8];
    static float scales[7]; // Array to store scales for each texture index
    int highlightedRow = 0;
    int highlightedCol = 0;

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
    randTexturesSprites(textures, sprites, board, cellSize, scales);

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
                if (event.key.code == sf::Keyboard::R)
                {
                    initializeBoard(board, sprites, textures, scales, highlightedRow, highlightedCol, cellSize); // Shuffle the board when R key is pressed
                }
                else if (event.key.code == sf::Keyboard::Enter) // To select a block
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
                    moveHighlight(event.key.code, highlightedRow, highlightedCol);
                }
                else if (enterKeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left))
                {
                    // If a block is selected perform swap operation
                    swap(board, sprites, textures, scales, event.key.code, enterKeyPressed, cellSize, highlightedRow, highlightedCol);

                }
            }
        }

        // Update time and score
        sf::Time elapsed = clock.getElapsedTime();
        int remainingSeconds = 120 - static_cast<int>(elapsed.asSeconds());
        int minutes = remainingSeconds / 60;
        remainingSeconds %= 60;
        if (remainingSeconds < 0)
        {
            remainingSeconds = 0;
        }

        // Update score every second
        score = elapsed.asSeconds();

        // Update text
        gameTitle.setString("Crytsal Crush Saga");
        timeText.setString("Time Left: " + std::to_string(minutes) + ":" + std::to_string(remainingSeconds) + " s");
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
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
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
        if (remainingSeconds == 0 && minutes == 0)
        {
            sf::sleep(sf::seconds(2)); // Add a 2-second delay
            window.close();
        }
    }

    return 0;
}
