#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // For _kbhit() and _getch()

#define SIZE 4

// Function prototypes
void play2048();
void memoryGame();
void ticTacToe();
void dinoGame();
void Exit();
void initialize_game(int board[SIZE][SIZE]);
void print_board(int board[SIZE][SIZE]);
int can_move(int board[SIZE][SIZE]);
void add_random_tile(int board[SIZE][SIZE]);
void handle_input(int board[SIZE][SIZE]);

int main() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Play 2048\n");
        printf("2. Play Memory Game\n");
        printf("3. Play Tic Tac Toe\n");
        printf("4. Clear Console\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");

        scanf("%d", &choice);

        switch (choice) {
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
                dinoGame();
                break;
            case 5:
                Exit();
                return 0;
            default:
                printf("Invalid choice! Please select a valid option (1-5).\n");
        }
    }

    return 0;
}

// Initialize the 2048 board
void initialize_game(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
    add_random_tile(board);
    add_random_tile(board);
}

// Print the 2048 board
void print_board(int board[SIZE][SIZE]) {
    system("cls");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                printf(".\t");
            else
                printf("%d\t", board[i][j]);
        }
        printf("\n");
    }
}

// Check if any moves are possible
int can_move(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                return 1;
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j])
                return 1;
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1])
                return 1;
        }
    }
    return 0;
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
void handle_input(int board[SIZE][SIZE]) {
    char input = _getch();
    switch (input) {
        case 'w': /* move_up(board); */ break;
        case 's': /* move_down(board); */ break;
        case 'a': /* move_left(board); */ break;
        case 'd': /* move_right(board); */ break;
        default: break;
    }
}

// 2048 Game Implementation
void play2048() {
    int board[SIZE][SIZE];
    srand(time(0));
    initialize_game(board);

    while (1) {
        print_board(board);
        if (!can_move(board)) {
            printf("Game Over!\n");
            break;
        }
        handle_input(board);
        add_random_tile(board);
    }
}

// Memory Game Implementation
void memoryGame() {
    // Same implementation as before.
    printf("Memory Game is under construction.\n");
}

// Tic Tac Toe Implementation
void ticTacToe() {
    char board[3][3];
    int i, j, move, moves = 0;
    char player = 'X';
    int positions[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // Initialize the board
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }

    while (moves < 9) {
        // Display the board
        system("cls");
        printf("Tic Tac Toe\n");
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (board[i][j] == ' ')
                    printf(" %d ", positions[i][j]);
                else
                    printf(" %c ", board[i][j]);
                if (j < 2) printf("|");
            }
            if (i < 2) printf("\n---|---|---\n");
        }

        // Player input
        printf("\nPlayer %c, enter your move (1-9): ", player);
        scanf("%d", &move);

        // Map move to row and column
        int row = (move - 1) / 3;
        int col = (move - 1) % 3;

        // Validate the move
        if (move < 1 || move > 9 || board[row][col] != ' ') {
            printf("Invalid move! Press any key to try again...\n");
            _getch(); // Pause to let the player read the message
            continue;
        }

        // Update board and increment moves
        board[row][col] = player;
        moves++;

        // Check for a win
        for (i = 0; i < 3; i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
                system("cls");
                printf("Player %c wins!\n", player);
                return;
            }
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
                system("cls");
                printf("Player %c wins!\n", player);
                return;
            }
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
            system("cls");
            printf("Player %c wins!\n", player);
            return;
        }
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
            system("cls");
            printf("Player %c wins!\n", player);
            return;
        }

        // Switch player
        player = (player == 'X') ? 'O' : 'X';
    }

    system("cls");
    printf("It's a draw!\n");
}



void dinoGame() {
    //harshali cha dino game ;)
}

// Exit Program
void Exit() {
    printf("Exiting the program. Goodbye!\n");
}
