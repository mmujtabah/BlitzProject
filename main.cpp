#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
#include <iomanip>

// Stores images to textures
void imagesBlocks(sf::Texture textures[])
{
    // Stores images in textures array
    if (!textures[0].loadFromFile("images/image0.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/image0.png" << std::endl;
        return;
    }
    if (!textures[1].loadFromFile("images/image1.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/image1.png" << std::endl;
        return;
    }
    if (!textures[2].loadFromFile("images/image2.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/image2.png" << std::endl;
        return;
    }
    if (!textures[3].loadFromFile("images/image3.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/image3.png" << std::endl;
        return;
    }
    if (!textures[4].loadFromFile("images/image4.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/image4.png" << std::endl;
        return;
    }
    if (!textures[5].loadFromFile("images/image5.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/image5.png" << std::endl;
        return;
    }
    if (!textures[6].loadFromFile("images/image6.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/image6.png" << std::endl;
        return;
    }
    if (!textures[7].loadFromFile("images/imagefire0.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/imagefire0.png" << std::endl;
        return;
    }
    if (!textures[8].loadFromFile("images/imagefire1.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/imagefire1.png" << std::endl;
        return;
    }
    if (!textures[9].loadFromFile("images/imagefire2.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/imagefire2.png" << std::endl;
        return;
    }
    if (!textures[10].loadFromFile("images/imagefire3.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/imagefire3.png" << std::endl;
        return;
    }
    if (!textures[11].loadFromFile("images/imagefire4.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/imagefire4.png" << std::endl;
        return;
    }
    if (!textures[12].loadFromFile("images/imagefire5.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/imagefire5.png" << std::endl;
        return;
    }
    if (!textures[13].loadFromFile("images/imagefire6.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/imagefire6.png" << std::endl;
        return;
    }

    if (!textures[14].loadFromFile("images/imageeffect0.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/imageeffect0.png" << std::endl;
        return;
    }
    if (!textures[15].loadFromFile("images/imageeffect1.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/imageeffect1.png" << std::endl;
        return;
    }
    if (!textures[16].loadFromFile("images/imageeffect2.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/imageeffect.png" << std::endl;
        return;
    }
    if (!textures[17].loadFromFile("images/imageeffect3.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/imageeffect3.png" << std::endl;
        return;
    }
    if (!textures[18].loadFromFile("images/imageeffect4.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/imageeffect4.png" << std::endl;
        return;
    }
    if (!textures[19].loadFromFile("images/imageeffect5.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/imageeffect5.png" << std::endl;
        return;
    }
    if (!textures[20].loadFromFile("images/imageeffect6.png"))
    {
        std::cout << "Failed to load texture: "
            << "images/imageeffect6.png" << std::endl;
        return;
    }
    // Set the smooth property for the texture
    for (int i = 0; i <= 20; i++)
    {
        textures[i].setSmooth(true);
    }
}

// Return index of yellow fire gem
int yellowFireGem(int index)
{
    int returnIndex = 0;
    switch (index)
    {
    case 0:
        returnIndex = 7;
        break;
    case 1:
        returnIndex = 8;
        break;
    case 2:
        returnIndex = 9;
        break;
    case 3:
        returnIndex = 10;
        break;
    case 4:
        returnIndex = 11;
        break;
    case 5:
        returnIndex = 12;
        break;
    case 6:
        returnIndex = 13;
        break;
    default:
        break;
    }
    return returnIndex;
}

// Return index of blue fire gem
int blueFireGem(int index)
{
    int returnIndex = 0;
    switch (index)
    {
    case 0:
        returnIndex = 14;
        break;
    case 1:
        returnIndex = 15;
        break;
    case 2:
        returnIndex = 16;
        break;
    case 3:
        returnIndex = 17;
        break;
    case 4:
        returnIndex = 18;
        break;
    case 5:
        returnIndex = 19;
        break;
    case 6:
        returnIndex = 20;
        break;
    default:
        break;
    }
    return returnIndex;
}

// Moves highlight based on the cursor key press
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

// Randomizes the initial data for the game board
void randboardData(int boardData[][8])
{
    srand(time(0));
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            boardData[i][j] = rand() % 7;
        }
    }
}
// Draws the game board
void drawBoard(sf::RenderWindow& window, int boardData[][8], sf::Texture textures[], sf::RectangleShape board[][8])
{
    static const float cellSize = 62.0f;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            sf::Sprite sprite;
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
            sprite.setTexture(textures[boardData[i][j]]); // Set the texture
            sprite.setPosition((i + 7.9) * cellSize, (j + 0.2) * cellSize); // Set the position
            // Set the scale of the sprites
            float scale = cellSize / static_cast<float>(textures[boardData[i][j]].getSize().x);
            scale -= 0.07f;
            sprite.setScale(scale, scale);
            float xOffset = (cellSize - sprite.getGlobalBounds().width) / 2.0f;
            float yOffset = (cellSize - sprite.getGlobalBounds().height) / 2.0f;
            sprite.setPosition(sprite.getPosition().x + xOffset, sprite.getPosition().y + yOffset);
            window.draw(board[i][j]);
            window.draw(sprite);

        }
    }
}
// Handles swapping of data based on keyboard input
void swapData(int boardData[][8], int& highlightedRow, int& highlightedCol, sf::Keyboard::Key key, bool& enterKeyPressed)
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
            std::swap(boardData[highlightedRow][highlightedCol], boardData[targetRow][targetCol]);
            highlightedRow = targetRow;
            highlightedCol = targetCol;
            enterKeyPressed = false;
        }
    }
}

bool checkElbowGems(int boardData[][8], int row, int col)
{
    srand(time(0));
    if (col + 2 < 8 && row + 2 < 8 &&
        boardData[row][col] == boardData[row][col + 1] &&
        boardData[row][col] == boardData[row][col + 2] &&
        boardData[row][col] == boardData[row + 1][col + 2] &&
        boardData[row][col] == boardData[row + 2][col + 2])
    {
        boardData[row + 2][col + 2] = blueFireGem(boardData[row][col]);
        boardData[row][col] = rand() % 7;
        boardData[row][col + 1] = rand() % 7;
        boardData[row][col + 2] = rand() % 7;
        boardData[row + 1][col + 2] = rand() % 7;
        return true;
    }

    if (row + 2 < 8 && col + 2 < 8 &&
        boardData[row][col] == boardData[row + 1][col] &&
        boardData[row][col] == boardData[row + 2][col] &&
        boardData[row][col] == boardData[row][col + 1] &&
        boardData[row][col] == boardData[row][col + 2])
    {
        boardData[row][col + 2] = blueFireGem(boardData[row][col]);
        boardData[row][col] = rand() % 7;
        boardData[row][col + 1] = rand() % 7;
        boardData[row + 1][col] = rand() % 7;
        boardData[row + 2][col] = rand() % 7;
        return true;
    }

    if (row - 2 >= 0 && col + 2 < 8 &&
        boardData[row][col] == boardData[row - 1][col] &&
        boardData[row][col] == boardData[row - 2][col] &&
        boardData[row][col] == boardData[row][col + 1] &&
        boardData[row][col] == boardData[row][col + 2])
    {
        boardData[row][col + 2] = blueFireGem(boardData[row][col]);
        boardData[row][col] = rand() % 7;
        boardData[row][col + 1] = rand() % 7;
        boardData[row - 1][col] = rand() % 7;
        boardData[row - 2][col] = rand() % 7;
        return true;
    }

    if (row - 2 >= 0 && col - 2 >= 0 &&
        boardData[row][col] == boardData[row - 1][col] &&
        boardData[row][col] == boardData[row - 2][col] &&
        boardData[row][col] == boardData[row][col - 1] &&
        boardData[row][col] == boardData[row][col - 2])
    {
        boardData[row][col] = blueFireGem(boardData[row][col]);
        boardData[row - 1][col] = rand() % 7;
        boardData[row - 2][col] = rand() % 7;
        boardData[row][col - 1] = rand() % 7;
        boardData[row][col - 2] = rand() % 7;
        return true;

    }
    return false;
}

bool elbowGems(int boardData[][8])
{
    bool soundPlay = false;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            bool flag = checkElbowGems(boardData, i, j);
            if (flag)
            {
                soundPlay = true;
            }
        }
    }
    return soundPlay;
}
// Checks for matches on the game board and updates data
void checkBoard(int boardData[][8])
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (boardData[i][j] == boardData[i + 1][j] && boardData[i][j] == boardData[i + 2][j])
            {
                //Check if there are 3 or more same elements in a row
                for (int k = i; k < 8; k++)
                {
                    if (boardData[i][j] == boardData[k][j])
                    {
                        boardData[k][j] = rand() % 7;
                    }
                    else
                    {
                        break;
                    }
                }

                boardData[i][j] = rand() % 7;
                boardData[i + 1][j] = rand() % 7;
                boardData[i + 2][j] = rand() % 7;
            }
            if (boardData[i][j] == boardData[i][j + 1] && boardData[i][j] == boardData[i][j + 2])
            {
                //Check if there are 3 or more same elements in a column
                for (int k = j + 3; k < 8; k++)
                {
                    if (boardData[i][j] == boardData[i][k])
                    {
                        boardData[i][k] = rand() % 7;
                    }
                    else
                    {
                        break;
                    }
                }
                boardData[i][j] = rand() % 7;
                boardData[i][j + 1] = rand() % 7;
                boardData[i][j + 2] = rand() % 7;
            }
        }
    }
}
int main()
{
    static sf::RectangleShape board[8][8];
    static sf::Texture textures[21];
    static sf::Sprite sprites[8][8];
    int highlightedRow = 0;
    int highlightedCol = 0;
    int boardData[8][8]{ 0 };   // Create a 2D array to store the board data
    randboardData(boardData); // Randomize the board data

    // Set up the window
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Bejeweled Blitz", sf::Style::Close);
    window.setFramerateLimit(60);


    // Set up the font for text
    sf::Font font;
    if (!font.loadFromFile("fonts/font.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    // Set up the bold font for title
    sf::Font fontBold;
    if (!fontBold.loadFromFile("fonts/fontBold.otf"))
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
    gameTitle.setFillColor(sf::Color::White);

    timeText.setFont(font);
    timeText.setCharacterSize(35);
    timeText.setFillColor(sf::Color::White);

    scoreText.setFont(font);
    scoreText.setCharacterSize(35);
    scoreText.setFillColor(sf::Color::White);

    gameInfo.setFont(font);
    gameInfo.setCharacterSize(25);
    gameInfo.setFillColor(sf::Color::White);

    // Set up the board
    const float cellSize = 62.0f;
    imagesBlocks(textures);

    // Set up the clock
    sf::Clock clock;

    // Initialize the score
    int score = 0;

    // Declare a boolean flag to track Enter key status
    bool enterKeyPressed = false;

    // Load the sound buffer from a file
    sf::SoundBuffer soundEffect1;
    if (!soundEffect1.loadFromFile("sounds/select.wav"))
    {
        std::cerr << "Failed to load sound file!" << std::endl;
        return -1;
    }
    sf::SoundBuffer soundEffect2;
    if (!soundEffect2.loadFromFile("sounds/sequence1.wav"))
    {
        std::cerr << "Failed to load sound file!" << std::endl;
        return -1;
    }
    sf::SoundBuffer soundEffect3;
    if (!soundEffect3.loadFromFile("sounds/sequence2.wav"))
    {
        std::cerr << "Failed to load sound file!" << std::endl;
        return -1;
    }
    sf::SoundBuffer soundEffect4;
    if (!soundEffect4.loadFromFile("sounds/sequence3.wav"))
    {
        std::cerr << "Failed to load sound file!" << std::endl;
        return -1;
    }
    // Create a sound instance
    sf::Sound sound, sound1, sound2, sound3;
    sound.setBuffer(soundEffect1);
    sound1.setBuffer(soundEffect2);
    sound2.setBuffer(soundEffect3);
    sound3.setBuffer(soundEffect4);
    sf::Music music;
    if (!music.openFromFile("sounds/music.wav"))
        return -1; // error
    music.play();

    // Load the image into a texture
    sf::Texture backgroundImage;
    if (!backgroundImage.loadFromFile("images/background.png")) {
        // Handle the case where the image cannot be loaded
        return -1;
    }
    // Create a sprite and set its texture to the loaded image
    sf::Sprite backgroundSprite(backgroundImage);

    // Set the desired size for the background image
    float desiredWidth = 1000.0f;  // Adjust to your desired width
    float desiredHeight = 600.0f;  // Adjust to your desired height

    // Calculate the scaling factors for width and height
    float scaleX = desiredWidth / backgroundSprite.getLocalBounds().width;
    float scaleY = desiredHeight / backgroundSprite.getLocalBounds().height;

    // Set the scale of the background sprite
    backgroundSprite.setScale(scaleX, scaleY);

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
                    randboardData(boardData);
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
                    swapData(boardData, highlightedRow, highlightedCol, event.key.code, enterKeyPressed);

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
        gameTitle.setPosition(10.0f, 45.0f);  // Adjust as needed
        timeText.setPosition(10.0f, 220.0f);  // Adjust as needed
        scoreText.setPosition(10.0f, 320.0f); // Adjust as needed
        gameInfo.setPosition(50.0f, 550.0f);  // Adjust as needed

        // Clear the window
        window.clear();

        // Set the background image
        window.draw(backgroundSprite);

        // Draw the time and score text
        window.draw(gameTitle);
        window.draw(timeText);
        window.draw(scoreText);
        window.draw(gameInfo);

        if (elbowGems(boardData))
        {
            sound3.play();
        }
        checkBoard(boardData);
        drawBoard(window, boardData, textures, board);

        // Draw the highlight with transparency and borders
        sf::RectangleShape highlight;
        highlight.setSize(sf::Vector2f(cellSize, cellSize));
        highlight.setPosition(board[highlightedRow][highlightedCol].getPosition());

        // Check the highlighted state to determine transparency
        if (enterKeyPressed)
        {
            // Adjust transparency and borders only if Enter was just pressed
            highlight.setFillColor(sf::Color(255, 255, 255, 100)); // Yellow with variable transparency
            highlight.setOutlineThickness(2.0f);                   // Border thickness
            highlight.setOutlineColor(sf::Color::Yellow);          // Border color
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
