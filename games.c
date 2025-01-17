#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // For _kbhit() and _getch()

#define SIZE 4
#define BOARD_SIZE 4

// Function prototypes
void play2048();
void memoryGame();
void option3();
void option4();
void initialize_game(int board[SIZE][SIZE]);
void print_board(int board[SIZE][SIZE]);
int can_move(int board[SIZE][SIZE]);
void add_random_tile(int board[SIZE][SIZE]);
void handle_input(int board[SIZE][SIZE]);

int main() {
    int choice;

    while (1) {
        // Display the menu
        printf("\nMenu:\n");
        printf("1. Play 2048\n");
        printf("2. Play Memory Game\n");
        printf("3. Option 3\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");

        // Read the user's choice
        scanf("%d", &choice);

        // Handle the choice using a switch statement
        switch (choice) {
            case 1:
                play2048();
                break;
            case 2:
                memoryGame();
                break;
            case 3:
                option3();
                break;
            case 4:
                option4();
                return 0; // Exit the program
            default:
                printf("Invalid choice! Please select a valid option (1-4).\n");
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
    system("cls"); // Clear the console
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

// Memory Game Implementation (unchanged)
void memoryGame() {
    // Implementation here...
}

void option3() {
    printf("You selected Option 3: Doing something else.\n");
}

void option4() {
    printf("Exiting the program.\n");
}
