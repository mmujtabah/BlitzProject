# BlitzProject

## Overview

This is a simple Match-3 puzzle game implemented in C++ using the SFML library. The game involves swapping adjacent gems to create matches of three or more gems of the same color in a row or column.

## Features

- **Gem Matching:** Swap adjacent gems to create matches of three or more of the same color.
- **Special Gems:**
  - **Flame Gems:** Created by making four or more gems of the same color consecutively. Triggered by including them in a match to clear surrounding gems.
  - **Destroyer Gems:** Gems with a value of 14 or greater can explode and clear their entire row and column. Created when making five gems in an elbow shape.
- **Shuffling Gems:** Press 'R' to shuffle gems when no match is being made.
- **Sound Effects:** Enjoy interactive sound effects when making matches or triggering special gems.
- **Scoring System:** Earn points for each match, and score bonus points for special gem actions.

## Getting Started

### Prerequisites

- C++ compiler
- SFML library (version X.X.X)

### Installation

1. Clone the repository: `git clone https://github.com/mmujtabah/BlitzProject.git`
2. Compile the source code: `g++ -o match3 main.cpp -lsfml-graphics -lsfml-window -lsfml-system`

### Usage

Run the compiled executable: `./match3`

## Gameplay

- **Controls:**
  - Use arrow keys to move the highlighter and press enter to select the gem, then use arrow keys to swap adjacent gems.
  - Press backspace key to deselect the selected gem.
  - Press 'R' to shuffle gems when no match is being made.

- **Objective:**
  - Match gems to score points.
  - Trigger special gems for additional effects.

## Code Structure

- `main.cpp`: Main game logic and entry point.
- `board.cpp` and `board.h`: Implementation of the game board and gem-related functions.
- `sound.cpp` and `sound.h`: Handling sound effects.

## Acknowledgments

- [SFML Library](https://www.sfml-dev.org/) - Simple and Fast Multimedia Library.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
