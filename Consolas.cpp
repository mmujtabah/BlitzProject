#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

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

void InitializeBoard(char board[8][8], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = randomValueGen();
        }
    }
}

int scoreCalculator(char gem, int gemCount) {
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


void checks(char board[8][8], int rows, int cols, int& totalscore) {

    //Row Check
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int index1 = j + 1;
            int index2 = j + 2;
            int index3 = j + 3;
            if (index1 < rows && index2 < rows) {
                if (index3 < rows) {
                    if (board[i][j] == board[i][index1] && board[i][j] == board[i][j] && board[i][index3]) {
                        totalscore += scoreCalculator(board[i][j], 4);
                    }
                }
                else {
                    if (board[i][j] == board[i][index1] && board[i][index2]) {
                        totalscore += scoreCalculator(board[i][j], 3);
                    }
                }
            }
        }
    }
    //Column Check 
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            int index1 = j + 1;
            int index2 = j + 2;
            int index3 = j + 3;
            if (index1 < cols && index2 < cols) {
                if (index3 < cols) {
                    if (board[j][i] == board[index1][i] && board[j][i] == board[index2][i] && board[j][i] == board[index3][i]) {
                        totalscore += scoreCalculator(board[i][j], 4);
                    }
                }
                else {
                    if (board[j][i] == board[index1][i] && board[j][i] == board[index2][i]) {
                        totalscore += scoreCalculator(board[i][j], 3);
                    }
                }
            }
        }
    }
}

void Display(char board[8][8], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "--";
        }
        cout << "-" << endl;

        for (int j = 0; j < cols; j++) {
            cout << "|" << board[i][j];
        }
        cout << "|" << endl;
    }

    for (int j = 0; j < cols; j++) {
        cout << "--";
    }
    cout << "-" << endl;
}

int main() {
    initializeRandomSeed();  // Call the seed initialization function
    int totalscore = 0;
    char board[8][8] = { ' ' };
    int rows = 8, cols = 8;
    InitializeBoard(board, rows, cols);
    Display(board, rows, cols);
    cout << endl << endl;
    checks(board, rows, cols, totalscore);
    cout << endl << "         Score  ===     " << totalscore << endl;
    return 0;
}
