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

int checks(char board[8][8], int rows, int cols){
    bool found = false;
    //Row Check
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (j + 1 < rows && j + 2 < cols && j + 3 < rows){
                if (board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2]){
                    found = true;
                    return 1;
                }
            }
        }
    }
    //Column Check 
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (j + 1 < rows && j + 2  && j + 3 < cols){
                if (board[j][i] == board[j+1][i] && board[j][i] == board[j+2][i]){
                    found = true;
                    return 1;
                }
            }
        }
    }
    return 0;
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
