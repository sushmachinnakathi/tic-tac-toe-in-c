                   #include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];
char currentPlayer;
int xWins = 0, oWins = 0, draws = 0;
char playerXName[50], playerOName[50];

void initializeBoard() {
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            board[i][j] = ' ';
}

void printBoard() {
    printf("\n");
    printf("     0   1   2\n");
    for(int i=0; i<3; i++) {
        printf("  %d  ", i);
        for(int j=0; j<3; j++) {
            printf(" %c ", board[i][j]);
            if(j < 2) printf("|");
        }
        if(i < 2) printf("\n    -----------\n");
    }
    printf("\n");
}

int checkWin() {
    for(int i=0; i<3; i++) {
        if(board[i][0]==currentPlayer && board[i][1]==currentPlayer && board[i][2]==currentPlayer) return 1;
        if(board[0][i]==currentPlayer && board[1][i]==currentPlayer && board[2][i]==currentPlayer) return 1;
    }
    if(board[0][0]==currentPlayer && board[1][1]==currentPlayer && board[2][2]==currentPlayer) return 1;
    if(board[0][2]==currentPlayer && board[1][1]==currentPlayer && board[2][0]==currentPlayer) return 1;
    return 0;
}

int checkDraw() {
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(board[i][j] == ' ') return 0;
    return 1;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void displayScore() {
    printf("\n?? Scoreboard:\n");
    printf("   %s (X): %d\n", playerXName, xWins);
    printf("   %s (O): %d\n", playerOName, oWins);
    printf("   Draws: %d\n", draws);
}

void playGame() {
    int row, col;
    while(1) {
        printBoard();
        printf("?? %s (Player %c), enter row and column (0-2): ", currentPlayer == 'X' ? playerXName : playerOName, currentPlayer);
        scanf("%d %d", &row, &col);

        if(row<0 || row>2 || col<0 || col>2 || board[row][col] != ' ') {
            printf("? Invalid move! Try again.\n");
            continue;
        }

        board[row][col] = currentPlayer;

        if(checkWin()) {
            printBoard();
            printf("?? %s (Player %c) wins!\n", currentPlayer == 'X' ? playerXName : playerOName, currentPlayer);
            if(currentPlayer == 'X') xWins++; else oWins++;
            break;
        } else if(checkDraw()) {
            printBoard();
            printf("?? It's a draw!\n");
            draws++;
            break;
        }

        switchPlayer();
    }
}

int main() {
    char playAgain;

    printf("?? Welcome to Enhanced Tic Tac Toe!\n");
    printf("Enter name for Player X: ");
    scanf("%s", playerXName);
    printf("Enter name for Player O: ");
    scanf("%s", playerOName);

    srand(time(0));

    do {
        initializeBoard();
        currentPlayer = (rand() % 2 == 0) ? 'X' : 'O';
        printf("\n? %s (Player %c) will start the game!\n", currentPlayer == 'X' ? playerXName : playerOName, currentPlayer);

        playGame();
        displayScore();

        printf("\n?? Play again? (y/n): ");
        scanf(" %c", &playAgain);

    } while(playAgain == 'y' || playAgain == 'Y');

    printf("?? Thanks for playing!\n");
    return 0;
}
