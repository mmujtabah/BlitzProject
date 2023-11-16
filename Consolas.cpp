#include <iostream>
#include <ctime>
#include <cstdlib>


void initializeRandomSeed() {
    srand(time(0));
}

char randomValueGen() {
    int num = 1 + (rand() % 7);
    switch (num) {
        case 1:
            return 'W';
        case 2:
            return 'B';
        case 3:
            return 'O';
        case 4:
            return 'R';
        case 5:
            return 'P';
        case 6:
            return 'Y';
        case 7:
            return 'G';
        default:
            return ' ';
    }
}

void InitializeBoard(char board[8][8], int rows, int cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = randomValueGen();
        }
    }
}

int scoreCalculator(char gem, int gemCount){
    int scoreCount = 0;
    switch (gem)
    {
    case 'W':
        scoreCount = 5;
        break;
    case 'B':
        scoreCount = 6;
        break;
    case 'O':
        scoreCount = 7;
        break;
    case 'R':
        scoreCount = 8;
        break;
    case 'P':
        scoreCount = 9;
        break;
    case 'Y':
        scoreCount = 10;
        break;
    case 'G':
        scoreCount = 11;
        break;
    default:
        break;
    }
    scoreCount *= gemCount;
    return scoreCount;
}


void checks(char board[8][8], int rows, int cols){
    bool found = false;
    //Row Check
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int index1 = j + 1;
            int index2 = j + 2;
            int index3 = j + 3;
            if (index1 < rows  && index2 < rows){
                if (index3 < rows){
                    if (board[i][j] == board[i][index1] && board[i][index1] == board[i][index2] && board[i][index3]){
                        
                    }
                }
            }else{

            }
        }
    }
    //Column Check 
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (j + 1 < rows && j + 2  && j + 3 < cols){
                if (board[j][i] == board[j+1][i] && board[j][i] == board[j+2][i]){
                    found = true;
                }
            }
        }
    }
}

void Display(char board[8][8], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << "--";
        }
        std::cout << "-" << std::endl;

        for (int j = 0; j < cols; j++) {
            std::cout << "|" << board[i][j];
        }
        std::cout << "|" << std::endl;
    }

    for (int j = 0; j < cols; j++) {
        std::cout << "--";
    }
    std::cout << "-" << std::endl;
}

int main() {
    initializeRandomSeed();  // Call the seed initialization function

    char board[8][8] = {' '};
    int rows = 8, cols = 8;    
    InitializeBoard(board, rows, cols);
    Display(board, rows, cols);
    std::cout << std::endl << checks(board, rows, cols);
    return 0;
}
