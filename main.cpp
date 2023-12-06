#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>


bool firstPlay = true;
// Game menu for exit and and play
bool showMenu(sf::RenderWindow& window)
{
	firstPlay = false;
	// Set up the font for text
	sf::Font font;
	if (!font.loadFromFile("fonts/menu.ttf"))
	{
		std::cerr << "Failed to load font!" << std::endl;
		return false;
	}
	// Load the image into a texture
	sf::Texture backgroundImage;
	if (!backgroundImage.loadFromFile("images/bg1.jpg"))
	{
		// Handle the case where the image cannot be loaded
		return false;
	}
	// Create a sprite and set its texture to the loaded image
	sf::Sprite backgroundSprite(backgroundImage);

	// Set the desired size for the background image
	float desiredWidth = 1000.0f;  // Adjust to your desired width
	float desiredHeight = 600.0f;  // Adjust to your desired height

	// Calculate the scaling factors for width and height
	float scaleX = desiredWidth / backgroundSprite.getLocalBounds().width;
	float scaleY = desiredHeight / backgroundSprite.getLocalBounds().height;

	// Load the sound buffer from a file
	sf::SoundBuffer soundBuff;
	if (!soundBuff.loadFromFile("sounds/slam.wav"))
	{
		std::cerr << "Failed to load sound file!" << std::endl;
		return false;
	}
	sf::Sound sound;
	sound.setBuffer(soundBuff);
	sound.play();

	// Set the scale of the background sprite
	backgroundSprite.setScale(scaleX, scaleY);
	// Set up the text for menu options
	sf::Text playText;
	sf::Text exitText;

	playText.setFont(font);
	playText.setCharacterSize(50);
	playText.setString("Play");
	playText.setPosition(380.0f, 240.0f);
	playText.setFillColor(sf::Color::Green);
	playText.setOutlineThickness(2.0f); // Border thickness

	exitText.setFont(font);
	exitText.setCharacterSize(50);
	exitText.setString("Exit");
	exitText.setPosition(380.0f, 340.0f);
	exitText.setFillColor(sf::Color::Red);
	exitText.setOutlineThickness(2.0f); // Border thickness

	// Game loop for the menu
	bool playSelected = true; // Indicates which option is currently selected
	playText.setOutlineColor(sf::Color::White);
	exitText.setOutlineColor(sf::Color::Red);

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
				if (event.key.code == sf::Keyboard::Up)
				{
					playSelected = true;
					playText.setOutlineColor(sf::Color::White);
					exitText.setOutlineColor(sf::Color::Red);
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					playSelected = false;
					playText.setOutlineColor(sf::Color::Green);
					exitText.setOutlineColor(sf::Color::White);
				}
				else if (event.key.code == sf::Keyboard::Return)
				{
					window.close();
					return playSelected;
				}
			}
		}

		// Clear the window
		window.clear();
		// Set the background image
		window.draw(backgroundSprite);
		// Draw menu options
		window.draw(playText);
		window.draw(exitText);

		// Display the content
		window.display();
	}

	return false; // Default to false in case of unexpected closure
}

// Stores images to textures
void loadImages(sf::Texture textures[])
{

	for (int i = 0; i <= 20; i++)
	{
		if (!textures[i].loadFromFile("images/image" + std::to_string(i) + ".png"))
		{
			std::cout << "Failed to load texture: " << "images/image" + std::to_string(i) + ".png" << std::endl;
			return;
		}
		textures[i].setSmooth(true);// Set the smooth property for the texture
	}
}

// Return index of blue fire gem
int destroyerGem(int index)
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

// Return index of blue fire gem
int flameGem(int index)
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

// If no match is found then reverse the swap to get to original position
void reverseSwapData(int boardData[][8], int& highlightedRow, int& highlightedCol, sf::Keyboard::Key key)
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
			targetCol = std::min(7, highlightedCol + 1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			targetCol = std::max(0, highlightedCol - 1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			targetRow = std::min(7, highlightedRow + 1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			targetRow = std::max(0, highlightedRow - 1);
		}

		// Check if the target position is valid
		if (targetRow >= 0 && targetRow < 8 && targetCol >= 0 && targetCol < 8)
		{
			std::swap(boardData[highlightedRow][highlightedCol], boardData[targetRow][targetCol]);
			highlightedRow = targetRow;
			highlightedCol = targetCol;
		}
	}
}
// Shift gems down after s swap to fill empty space
void shiftGemsDown(int board[][8]) {
	for (int j = 0; j < 8; j++) {
		int count = 0;
		for (int i = 8 - 1; i >= 0; i--) {
			if (board[i][j] != -1) {
				std::swap(board[i][j], board[8 - 1 - count][j]);
				count++;
			}
		}
	}
}

// Fills new gems at the top after the shiftGemsDown function has been performed
void fillNewGems(int board[][8]) {
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			if (board[i][j] == -1) {
				board[i][j] = rand() % 7;
			}
		}
	}
}

// Destroyer gem check
bool checkElbowGems(int boardData[][8], int row, int col, int highlightedRow, int highlightedCol)
{
	int tempValue = boardData[highlightedRow][highlightedCol];
	srand(time(0));
	if (col + 2 < 8 && row + 2 < 8 &&
		boardData[row][col] == boardData[row][col + 1] &&
		boardData[row][col] == boardData[row][col + 2] &&
		boardData[row][col] == boardData[row + 1][col + 2] &&
		boardData[row][col] == boardData[row + 2][col + 2])
	{
		boardData[row + 2][col + 2] = -1;
		boardData[row][col] = -1;
		boardData[row][col + 1] = -1;
		boardData[row][col + 2] = -1;
		boardData[row + 1][col + 2] = -1;
		if ((highlightedRow == row || highlightedRow == row + 1 || highlightedRow == row + 2) && (highlightedCol == col || highlightedCol == col + 1 || highlightedCol == col + 2))
		{
			boardData[highlightedRow][highlightedCol] = destroyerGem(tempValue);
		}
		else
		{
			boardData[row][col] = destroyerGem(boardData[row][col]);
		}
		return true;
	}

	if (row + 2 < 8 && col + 2 < 8 &&
		boardData[row][col] == boardData[row + 1][col] &&
		boardData[row][col] == boardData[row + 2][col] &&
		boardData[row][col] == boardData[row][col + 1] &&
		boardData[row][col] == boardData[row][col + 2])
	{
		boardData[row][col + 2] = -1;
		boardData[row][col] = -1;
		boardData[row][col + 1] = -1;
		boardData[row + 1][col] = -1;
		boardData[row + 2][col] = -1;
		if ((highlightedRow == row || highlightedRow == row + 1 || highlightedRow == row + 2) && (highlightedCol == col || highlightedCol == col + 1 || highlightedCol == col + 2))
		{
			boardData[highlightedRow][highlightedCol] = destroyerGem(tempValue);
		}
		else
		{
			boardData[row][col] = destroyerGem(boardData[row][col]);
		}

		return true;
	}

	if (row - 2 >= 0 && col + 2 < 8 &&
		boardData[row][col] == boardData[row - 1][col] &&
		boardData[row][col] == boardData[row - 2][col] &&
		boardData[row][col] == boardData[row][col + 1] &&
		boardData[row][col] == boardData[row][col + 2])
	{
		boardData[row][col + 2] = -1;
		boardData[row][col] = -1;
		boardData[row][col + 1] = -1;
		boardData[row - 1][col] = -1;
		boardData[row - 2][col] = -1;
		if ((highlightedRow == row || highlightedRow == row - 1 || highlightedRow == row - 2) && (highlightedCol == col || highlightedCol == col + 1 || highlightedCol == col + 2))
		{
			boardData[highlightedRow][highlightedCol] = destroyerGem(tempValue);
		}
		else
		{
			boardData[row][col] = destroyerGem(boardData[row][col]);
		}
		return true;
	}

	if (row - 2 >= 0 && col - 2 >= 0 &&
		boardData[row][col] == boardData[row - 1][col] &&
		boardData[row][col] == boardData[row - 2][col] &&
		boardData[row][col] == boardData[row][col - 1] &&
		boardData[row][col] == boardData[row][col - 2])
	{
		boardData[row][col] = -1;
		boardData[row - 1][col] = -1;
		boardData[row - 2][col] = -1;
		boardData[row][col - 1] = -1;
		boardData[row][col - 2] = -1;
		if ((highlightedRow == row || highlightedRow == row - 1 || highlightedRow == row - 2) && (highlightedCol == col || highlightedCol == col - 1 || highlightedCol == col - 2))
		{
			boardData[highlightedRow][highlightedCol] = destroyerGem(tempValue);
		}
		else
		{
			boardData[row][col] = destroyerGem(boardData[row][col]);
		}
		return true;

	}
	return false;
}
// Destroyer gem explosion
bool specialGemDestroyer(int boardData[][8])
{
	bool sound = false;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int temp = boardData[i][j];
			if (temp >= 14)
			{
				// Check if it's a destroyer gem
				int color = temp % 7; // Get the color of the destroyer gem

				// Check in the row for consecutive gems of the same color
				bool consecutiveRow = false;
				if (j + 1 < 8 && j + 2 < 8) {
					if ((boardData[i][j + 1]) % 7 == color && (boardData[i][j + 2]) % 7 == color) {
						consecutiveRow = true;
					}
					if (j - 1 >= 0) {
						if ((boardData[i][j - 1]) % 7 == color && (boardData[i][j + 1]) % 7 == color) {
							consecutiveRow = true;
						}
					}
				}
				if (j - 1 >= 0 && j - 2 >= 0) {
					if ((boardData[i][j - 1]) % 7 == color && (boardData[i][j - 2]) % 7 == color) {
						consecutiveRow = true;
					}
					if (j + 1 < 8) {
						if ((boardData[i][j - 1]) % 7 == color && (boardData[i][j + 1]) % 7 == color) {
							consecutiveRow = true;
						}
					}
				}
				// Check in the column for consecutive gems of the same color
				bool consecutiveCol = false;
				if (i + 1 < 8 && i + 2 < 8) {
					if ((boardData[i + 1][j]) % 7 == color && (boardData[i + 2][j]) % 7 == color) {
						consecutiveRow = true;
					}
					if (i - 1 >= 0) {
						if ((boardData[i - 1][j]) % 7 == color && (boardData[i + 1][j]) % 7 == color) {
							consecutiveRow = true;
						}
					}
				}
				if (i - 1 >= 0 && i - 2 >= 0) {
					if ((boardData[i - 1][j]) % 7 == color && (boardData[i - 2][j]) % 7 == color) {
						consecutiveRow = true;
					}
					else if (i + 1 < 8) {
						if ((boardData[i - 1][j]) % 7 == color && (boardData[i + 1][j]) % 7 == color) {
							consecutiveRow = true;
						}
					}
				}
				// If consecutive gems found in row or column, update to -1
				if (consecutiveRow || consecutiveCol)
				{
					for (int k = 0; k < 8; k++)
					{
						boardData[i][k] = -1;
					}

					for (int k = 0; k < 8; k++)
					{
						boardData[k][j] = -1;
					}
					sound = true;
				}
			}
		}
	}
	shiftGemsDown(boardData);
	fillNewGems(boardData);
	return sound;
}
// Flame gem explosion
bool specialGemFlame(int boardData[][8])
{
	bool sound = false;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int temp = boardData[i][j];
			if (temp >= 7 && temp < 14)
			{
				// Check if it's a flame gem
				int color = temp % 7; // Get the color of the flame gem

				// Check in the row for consecutive gems of the same color
				bool consecutiveRow = false;
				if (j + 1 < 8 && j + 2 < 8) {
					if ((boardData[i][j + 1]) % 7 == color && (boardData[i][j + 2]) % 7 == color) {
						consecutiveRow = true;
					}
					if (j - 1 >= 0) {
						if ((boardData[i][j - 1]) % 7 == color && (boardData[i][j + 1]) % 7 == color) {
							consecutiveRow = true;
						}
					}
				}
				if (j - 1 >= 0 && j - 2 >= 0) {
					if ((boardData[i][j - 1]) % 7 == color && (boardData[i][j - 2]) % 7 == color) {
						consecutiveRow = true;
					}
					else if (j + 1 < 8) {
						if ((boardData[i][j - 1]) % 7 == color && (boardData[i][j + 1]) % 7 == color) {
							consecutiveRow = true;
						}
					}
				}
				// Check in the column for consecutive gems of the same color
				bool consecutiveCol = false;
				if (i + 1 < 8 && i + 2 < 8) {
					if ((boardData[i + 1][j]) % 7 == color && (boardData[i + 2][j]) % 7 == color) {
						consecutiveCol = true;
					}
					if (i - 1 >= 0) {
						if ((boardData[i - 1][j]) % 7 == color && (boardData[i + 1][j]) % 7 == color) {
							consecutiveCol = true;
						}
					}
				}
				if (i - 1 >= 0 && i - 2 >= 0) {
					if ((boardData[i - 1][j]) % 7 == color && (boardData[i - 2][j]) % 7 == color) {
						consecutiveCol = true;
					}
					if (i + 1 < 8) {
						if ((boardData[i - 1][j]) % 7 == color && (boardData[i + 1][j]) % 7 == color) {
							consecutiveCol = true;
						}
					}
				}
				// If consecutive gems found in row or column, update to -1
				if (consecutiveRow || consecutiveCol)
				{
					if (i - 1 >= 0 && j - 1 >= 0) {
						boardData[i - 1][j - 1] = -1;
					}
					if (j - 1 >= 0) {
						boardData[i][j - 1] = -1;
					}
					if (i + 1 < 8 && j - 1 >= 0) {
						boardData[i + 1][j - 1] = -1;
					}
					if (i - 1 >= 0) {
						boardData[i - 1][j] = -1;
					}
					boardData[i][j] = -1;
					if (i + 1 < 8) {
						boardData[i + 1][j] = -1;
					}
					if (i - 1 >= 0 && j + 1 < 8) {
						boardData[i - 1][j + 1] = -1;
					}
					if (j + 1 < 8) {
						boardData[i][j + 1] = -1;
					}
					if (i + 1 < 8 && j + 1 < 8) {
						boardData[i + 1][j + 1] = -1;
					}
					sound = true;
				}
			}
		}
	}
	shiftGemsDown(boardData);
	fillNewGems(boardData);
	return sound;
}

// Checks Elbow gem and plays the sound
bool elbowGems(int boardData[][8], int& score, int highlightedRow, int highlightedCol)
{
	bool soundPlay = false;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			bool flag = checkElbowGems(boardData, i, j, highlightedRow, highlightedCol);
			if (flag)
			{
				soundPlay = true;
				score += 50;
			}
		}
	}
	if (soundPlay)
	{
		shiftGemsDown(boardData);
		fillNewGems(boardData);
	}

	return soundPlay;
}
// Checks for matches on the game board and updates data
bool checkBoard(int boardData[][8], int& score, int highlightedRow, int highlightedCol, bool& flameFound)
{
	srand(time(0));
	bool flag = false;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (boardData[i][j] == boardData[i + 1][j] && boardData[i][j] == boardData[i + 2][j]) // Row Check
			{
				flag = true;
				score += 15;
				int count = 3;
				int tempValue = boardData[highlightedRow][highlightedCol];
				//Check if there are 3 or more same elements in a column
				for (int k = i + 3; k < 8; k++)
				{
					if (boardData[i][j] == boardData[k][j])
					{
						boardData[k][j] = -1;
						score += 5;
						count++;
					}
					else
					{
						break;
					}
				}
				boardData[i][j] = -1;
				boardData[i + 1][j] = -1;
				boardData[i + 2][j] = -1;
				if (count > 3)
				{
					if ((highlightedRow == i || highlightedRow == i + 1 || highlightedRow == i + 2) && highlightedCol == j)
					{
						boardData[highlightedRow][highlightedCol] = flameGem(tempValue);
						flameFound = true;
					}
					else
					{
						boardData[i][j] = flameGem(boardData[i][j]);
						flameFound = true;
					}

				}
			}
			if (boardData[i][j] == boardData[i][j + 1] && boardData[i][j] == boardData[i][j + 2]) // Column Check
			{
				flag = true;
				//Check if there are 3 or more same elements in a row
				score += 15;
				int count = 3;
				int tempValue = boardData[highlightedRow][highlightedCol];
				for (int k = j + 3; k < 8; k++)
				{
					if (boardData[i][j] == boardData[i][k])
					{
						boardData[i][k] = -1;
						score += 5;
						count++;
					}
					else
					{
						break;
					}
				}
				boardData[i][j] = -1;
				boardData[i][j + 1] = -1;
				boardData[i][j + 2] = -1;
				if (count > 3)
				{
					if ((highlightedCol == j || highlightedCol == j + 1 || highlightedCol == j + 2) && highlightedRow == i)
					{
						boardData[highlightedRow][highlightedCol] = flameGem(tempValue);
						flameFound = true;
					}
					else
					{
						boardData[i][j] = flameGem(boardData[i][j]);
						flameFound = true;
					}
				}
			}
		}
	}
	if (flag)
	{
		shiftGemsDown(boardData);
		fillNewGems(boardData);
	}
	if (flameFound)
	{
		score += 20;
	}
	return flag;
}
// Game over menu to exit or restart game
bool showGameOverMenu(sf::RenderWindow& window, int score) {
	int filescore = 0;
	std::ifstream file("file.txt");
	file >> filescore;
	file.close();
	std::ofstream readFile("file.txt");
	if (score > filescore) { filescore = score; }
	readFile << filescore;
	readFile.close();
	sf::Font font;
	if (!font.loadFromFile("fonts/menu.ttf")) {
		std::cerr << "Failed to load font!" << std::endl;
		return false;
	}

	// Load the image into a texture
	sf::Texture backgroundImage;
	if (!backgroundImage.loadFromFile("images/bg2.jpg"))
	{
		// Handle the case where the image cannot be loaded
		return false;
	}
	// Create a sprite and set its texture to the loaded image
	sf::Sprite backgroundSprite(backgroundImage);

	// Set the desired size for the background image
	float desiredWidth = 1000.0f;  // Adjust to your desired width
	float desiredHeight = 600.0f;  // Adjust to your desired height

	// Calculate the scaling factors for width and height
	float scaleX = desiredWidth / backgroundSprite.getLocalBounds().width;
	float scaleY = desiredHeight / backgroundSprite.getLocalBounds().height;
	backgroundSprite.setScale(scaleX, scaleY);

	sf::Text highscore;
	highscore.setFont(font);
	highscore.setCharacterSize(40);
	highscore.setFillColor(sf::Color::White);
	highscore.setString("Highscore: " + std::to_string(filescore));
	highscore.setPosition(200.0f, 120.0f);

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setPosition(300.0f, 220.0f);

	sf::Text restartText;
	restartText.setFont(font);
	restartText.setCharacterSize(40);
	restartText.setFillColor(sf::Color::Green);
	restartText.setString("Restart Game");
	restartText.setPosition(250.0f, 320.0f);
	restartText.setOutlineThickness(2.0f);

	sf::Text exitText;
	exitText.setFont(font);
	exitText.setCharacterSize(40);
	exitText.setFillColor(sf::Color::Red);
	exitText.setString("Exit");
	exitText.setPosition(400.0f, 420.0f);
	exitText.setOutlineThickness(2.0f);
	bool selected = true;
	restartText.setOutlineColor(sf::Color::White);
	exitText.setOutlineColor(sf::Color::Red);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return false;
			}
			else if (event.type == sf::Event::KeyPressed) {
				// Move selector with arrow keys
				if (event.key.code == sf::Keyboard::Up) {
					restartText.setOutlineColor(sf::Color::White);
					exitText.setOutlineColor(sf::Color::Red);
					selected = true;
				}
				else if (event.key.code == sf::Keyboard::Down) {
					restartText.setOutlineColor(sf::Color::Green);
					exitText.setOutlineColor(sf::Color::White);
					selected = false;
				}
				else if (event.key.code == sf::Keyboard::Return) {
					// Check if the cursor is over "Restart Game" or "Exit"
					window.close();
					return selected;
				}
			}
		}

		// Clear the window
		window.clear();

		// Draw menu options
		window.draw(backgroundSprite);
		window.draw(highscore);
		window.draw(scoreText);
		window.draw(restartText);
		window.draw(exitText);


		// Display the content
		window.display();
	}

	return false; // Default to false in case of unexpected closure
}

int main()
{
	
	// Load the icon image
	sf::Image icon;
	if (!icon.loadFromFile("images/icon.jpg"))
	{
		std::cout << "Failed to load icon.png";
		return -1;
	}
	if (firstPlay) {
		sf::RenderWindow menuWindow(sf::VideoMode(1000, 600), "Bejeweled Blitz", sf::Style::Close);
		menuWindow.setFramerateLimit(60);
		menuWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		bool play = showMenu(menuWindow);
		if (!play)
		{
			return 0;
		}
	}

	static sf::RectangleShape board[8][8];
	static sf::Texture textures[21];
	int highlightedRow = 0;
	int highlightedCol = 0;
	int boardData[8][8]{ 0 };  // Create a 2D array to store the board data
	randboardData(boardData); // Randomize the board data

	// Set up the window
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Bejeweled Blitz", sf::Style::Close);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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
	sf::Text shuffleText;
	sf::Text gameTitle;
	sf::Text gameInfo;

	gameTitle.setFont(fontBold);
	gameTitle.setCharacterSize(36);
	gameTitle.setFillColor(sf::Color::White);

	timeText.setFont(font);
	timeText.setCharacterSize(35);
	timeText.setFillColor(sf::Color::White);

	shuffleText.setFont(font);
	shuffleText.setCharacterSize(25);
	shuffleText.setFillColor(sf::Color::White);

	scoreText.setFont(font);
	scoreText.setCharacterSize(35);
	scoreText.setFillColor(sf::Color::White);

	gameInfo.setFont(font);
	gameInfo.setCharacterSize(25);
	gameInfo.setFillColor(sf::Color::White);

	// Set up the board
	const float cellSize = 62.0f;
	loadImages(textures);

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
	if (!soundEffect3.loadFromFile("sounds/flame.wav"))
	{
		std::cerr << "Failed to load sound file!" << std::endl;
		return -1;
	}
	sf::SoundBuffer soundEffect4;
	if (!soundEffect4.loadFromFile("sounds/destroyer.wav"))
	{
		std::cerr << "Failed to load sound file!" << std::endl;
		return -1;
	}
	sf::SoundBuffer destroyer;
	if (!destroyer.loadFromFile("sounds/destroyerExplodes.wav"))
	{
		std::cerr << "Failed to load sound file!" << std::endl;
		return -1;
	}
	sf::SoundBuffer flameSound;
	if (!flameSound.loadFromFile("sounds/flameExplodes.wav"))
	{
		std::cerr << "Failed to load sound file!" << std::endl;
		return -1;
	}
	// Create a sound instance
	sf::Sound sound, sound1, sound2, sound3, sound4, sound5;
	sound.setBuffer(soundEffect1);
	sound1.setBuffer(soundEffect2);
	sound2.setBuffer(soundEffect3);
	sound3.setBuffer(soundEffect4);
	sound4.setBuffer(destroyer);
	sound5.setBuffer(flameSound);
	sf::Music music;
	if (!music.openFromFile("sounds/moogcity.wav"))
		return -1; // error
	music.play();
	music.setLoop(true);
	// Load the image into a texture
	sf::Texture backgroundImage;
	if (!backgroundImage.loadFromFile("images/bg.png")) {
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
		bool swapped = false;
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
					swapped = true;

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

		// Update text
		gameTitle.setString("Crytsal Crush Saga");
		timeText.setString("Time Left: " + std::to_string(minutes) + ":" + std::to_string(remainingSeconds) + " s");
		shuffleText.setString("Press R to shuffle gems");
		scoreText.setString("Score: " + std::to_string(score));
		gameInfo.setString("Game developed by M.Mujtaba and Harris Tabassum");

		// Adjust positions for separation
		gameTitle.setPosition(10.0f, 45.0f);  // Adjust as needed
		timeText.setPosition(10.0f, 220.0f);  // Adjust as needed
		scoreText.setPosition(10.0f, 320.0f); // Adjust as needed
		shuffleText.setPosition(10.0f, 420.0f);  // Adjust as needed
		gameInfo.setPosition(50.0f, 550.0f);  // Adjust as needed

		// Clear the window
		window.clear();

		// Set the background image
		window.draw(backgroundSprite);

		// Draw the time and score text
		window.draw(gameTitle);
		window.draw(timeText);
		window.draw(scoreText);
		window.draw(shuffleText);
		window.draw(gameInfo);
		bool destroyer = specialGemDestroyer(boardData);
		bool flame = specialGemFlame(boardData);
		bool flameFound = false;
		bool destroyerGem = elbowGems(boardData, score, highlightedRow, highlightedCol);
		bool matchGems = checkBoard(boardData, score, highlightedRow, highlightedCol, flameFound);

		if (destroyerGem || matchGems || destroyer || flame)
		{
			if (destroyer) {
				score += 50;
				sound4.play();
			}
			if (flame) {
				score += 20;
				sound5.play();
			}
			if (destroyerGem)
			{
				sound3.play();
			}
			if (flameFound)
			{
				sound2.play();
			}
			if (matchGems)
			{
				sound1.play();
			}
		}
		else
		{
			if (swapped)
			{
				reverseSwapData(boardData, highlightedRow, highlightedCol, event.key.code);
			}
		}
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
		if (remainingSeconds == 58 && minutes == 1)
		{
			sf::sleep(sf::seconds(2)); // Add a 2-second delay
			window.close();
			sf::RenderWindow gameOver(sf::VideoMode(1000, 600), "Bejeweled Blitz", sf::Style::Close);
			gameOver.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
			gameOver.setFramerateLimit(60);
			if (showGameOverMenu(gameOver, score))
			{
				music.stop();
				main();
			}
		}
	}
	return 0;
}
