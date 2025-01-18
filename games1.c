#include <stdio.h>//stadnard input output
#include <stdlib.h>//used for genrating random tiles
#include<time.h>//uesd for s random
#include <conio.h> // For _kbhit() and _getch()
#include <windows.h> // For Sleep()

#define SIZE 4//defining the size of an array to be used for respective games
#define TARGET 2048//the end goal for 2048 game

// Function prototypes
void play2048();
void memoryGame();
void ticTacToe();
void dinoGame(); // Placeholder
void Exit();
void initialize_game(int board[SIZE][SIZE], int *score);
void print_board(int board[SIZE][SIZE], int score);
int can_move(int board[SIZE][SIZE]);
void add_random_tile(int board[SIZE][SIZE]);
int handle_input(int board[SIZE][SIZE], int *score);
void move_left(int board[SIZE][SIZE], int *score, int *moved);
void move_right(int board[SIZE][SIZE], int *score, int *moved);
void move_up(int board[SIZE][SIZE], int *score, int *moved);
void move_down(int board[SIZE][SIZE], int *score, int *moved);
int check_win(int board[SIZE][SIZE]);

int main() {
    int choice;//declaring the variable for switch case 

    while (1) {
        printf("\nMenu:\n");
        printf("1. Play 2048\n");
        printf("2. Play Memory Game\n");
        printf("3. Play Tic Tac Toe\n");
        printf("4. Clear Console\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);//taking the user's choice

        switch (choice) {
                //Calling the function as switch case does not allow defining functions
            case 1:
                play2048();
                break;
            case 2:
                memoryGame();
                break;
            case 3:
                ticTacToe();
                break;
            case 4:
                system("cls");
                break;
            case 5:
                Exit();
                return 0;
            default:
                printf("Invalid choice! Please select a valid option (1-5).\n");//error handling 
        }
    }

    return 0;
}

// Initialize the 2048 board
void play2048() {
    int board[SIZE][SIZE];//declare the board
    int score = 0;//initalize and declare the score
    int moved;//flag value

    srand(time(0));//genrates true random number by seeding(gives a starting point to random arguesment).
    initialize_game(board, &score);

    printf("Welcome to 2048!\n");
    printf("Instructions:\n");
    printf("- Use W (up), A (left), S (down), D (right) to move tiles.\n");
    printf("- Combine tiles with the same number to add them together.\n");
    printf("- Reach 2048 to win! Press Q to quit anytime.\n\n");
    system("pause");

    while (1) {
        print_board(board, score);

        if (check_win(board)) {
            printf("Congratulations! You've reached 2048!\n");
            printf("Press Q to quit or any other key to keep playing.\n");
            char choice = _getch();//used to get the key pressed by user 
            if (choice == 'q' || choice == 'Q') return;
        }

        if (!can_move(board)) {//checking if there are any spaces left if not then game over.
            printf("Game Over! No more moves.\n");
            printf("Your final score: %d\n", score);
            break;
        }

        moved = handle_input(board, &score);//this function is defined below in code
        if (moved) add_random_tile(board);
    }
}

// Initialize the 2048 board
void initialize_game(int board[SIZE][SIZE], int *score) {
    *score = 0;//using a pointer 
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;//using the for loop to 
        }
    }
    add_random_tile(board);
    add_random_tile(board);
}

// Print the 2048 board and the score
void print_board(int board[SIZE][SIZE], int score) {
    system("cls");
    printf("2048 Game\n");
    printf("Score: %d\n", score);
    printf("-----------------------------\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                printf("|   ");
            else
                printf("|%4d", board[i][j]);
        }
        printf("|\n-----------------------------\n");
    }
    printf("Controls: W (up), A (left), S (down), D (right), Q (quit)\n");
}

// Add a random tile to the board
void add_random_tile(int board[SIZE][SIZE]) {
    int empty[SIZE * SIZE][2];
    int empty_count = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                empty[empty_count][0] = i;
                empty[empty_count][1] = j;
                empty_count++;
            }
        }
    }

    if (empty_count > 0) {
        int rand_idx = rand() % empty_count;
        int i = empty[rand_idx][0];
        int j = empty[rand_idx][1];
        board[i][j] = (rand() % 2 + 1) * 2;
    }
}

// Handle user input for 2048
int handle_input(int board[SIZE][SIZE], int *score) {
    int moved = 0;
    char input = _getch();
    switch (input) {
        case 'w': move_up(board, score, &moved); break;
        case 's': move_down(board, score, &moved); break;
        case 'a': move_left(board, score, &moved); break;
        case 'd': move_right(board, score, &moved); break;
        case 'q': 
            printf("You quit the game. Final Score: %d\n", *score);
            exit(0);
        default: 
            printf("Invalid input. Use W, A, S, D, or Q to quit.\n");
            break;
    }
    return moved;
}

// Move tiles and update score
void move_left(int board[SIZE][SIZE], int *score, int *moved) {
    for (int i = 0; i < SIZE; i++) {
        int pos = 0; 
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 0) {
                if (pos > 0 && board[i][pos - 1] == board[i][j]) {
                    board[i][pos - 1] *= 2;
                    *score += board[i][pos - 1];
                    board[i][j] = 0;
                    *moved = 1;
                } else if (pos != j) {
                    board[i][pos++] = board[i][j];
                    board[i][j] = 0;
                    *moved = 1;
                } else {
                    pos++;
                }
            }
        }
    }
}

void move_right(int board[SIZE][SIZE], int *score, int *moved) {
    for (int i = 0; i < SIZE; i++) {
        int pos = SIZE - 1;
        for (int j = SIZE - 1; j >= 0; j--) {
            if (board[i][j] != 0) {
                if (pos < SIZE - 1 && board[i][pos + 1] == board[i][j]) {
                    board[i][pos + 1] *= 2;
                    *score += board[i][pos + 1];
                    board[i][j] = 0;
                    *moved = 1;
                } else if (pos != j) {
                    board[i][pos--] = board[i][j];
                    board[i][j] = 0;
                    *moved = 1;
                } else {
                    pos--;
                }
            }
        }
    }
}

void move_up(int board[SIZE][SIZE], int *score, int *moved) {
    for (int j = 0; j < SIZE; j++) {
        int pos = 0;
        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] != 0) {
                if (pos > 0 && board[pos - 1][j] == board[i][j]) {
                    board[pos - 1][j] *= 2;
                    *score += board[pos - 1][j];
                    board[i][j] = 0;
                    *moved = 1;
                } else if (pos != i) {
                    board[pos++][j] = board[i][j];
                    board[i][j] = 0;
                    *moved = 1;
                } else {
                    pos++;
                }
            }
        }
    }
}

void move_down(int board[SIZE][SIZE], int *score, int *moved) {
    for (int j = 0; j < SIZE; j++) {
        int pos = SIZE - 1;
        for (int i = SIZE - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                if (pos < SIZE - 1 && board[pos + 1][j] == board[i][j]) {
                    board[pos + 1][j] *= 2;
                    *score += board[pos + 1][j];
                    board[i][j] = 0;
                    *moved = 1;
                } else if (pos != i) {
                    board[pos--][j] = board[i][j];
                    board[i][j] = 0;
                    *moved = 1;
                } else {
                    pos--;
                }
            }
        }
    }
}

// Check if the player has won
int check_win(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == TARGET) {
                return 1;
            }
        }
    }
    return 0;
}

// Check if any moves are possible
int can_move(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) return 1;
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) return 1;
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) return 1;
        }
    }
    return 0;
}

// Placeholder for Memory Game
void memoryGame() {
    printf("Memory Game under development!\n");
    system("pause");
}

// Placeholder for Tic Tac Toe
void ticTacToe() {
    printf("Tic Tac Toe under development!\n");
    system("pause");
}

// Exit function
void Exit() {
    printf("Exiting the game. Goodbye!\n");
    exit(0);
}
