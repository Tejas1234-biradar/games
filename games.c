#include <stdio.h> // Standard input-output
#include <stdlib.h> // Used for generating random numbers
#include <time.h> // Used for random seed initialization
#include <conio.h> // For _kbhit() and _getch()
#include <windows.h> // For Sleep()

#define SIZE 4 // Define size of the board for 2048
#define TARGET 2048 // Target score to win in 2048
#define MAX_SEQUENCE_LENGTH 10//Maximum lenght of sequence in memory game.

// Function prototypes
void play2048();
void memoryGame();
void ticTacToe();
void dinoGame(); // Placeholder for Dino game
void Exit();
void initialize_game(int board[SIZE][SIZE], int *score);
void print_board(int board[SIZE][SIZE], int score);
int can_move(int board[SIZE][SIZE]);
void add_random_tile(int board[SIZE][SIZE]);
int handle_input(int board[SIZE][SIZE], int *score);
void move_left(int board[SIZE][SIZE], int *score, int *moved);
void move_right(int board[SIZE][SIZE], int *score, int *moved);
void move_up(int board[SIZE][SIZE], int *score, int *moved); // Move tiles up
void move_down(int board[SIZE][SIZE], int *score, int *moved); // Move tiles down
int check_win(int board[SIZE][SIZE]);

int main() {
    int choice; // Variable for user's menu choice

    while (1) {
        // Display menu
        printf("\nMenu:\n");
        printf("1. Play 2048\n");
        printf("2. Play Memory Game\n");
        printf("3. Play Tic Tac Toe\n");
        printf("4. Clear Console\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice); // User's menu choice

        switch (choice) {
            case 1:
                play2048(); // Play 2048 game
                break;
            case 2:
                memoryGame(); // Play Memory Game
                break;
            case 3:
                ticTacToe(); // Play Tic Tac Toe
                break;
            case 4:
                system("cls"); // Clear the console
                break;
            case 5:
                Exit(); // Exit the program
                return 0;
            default:
                printf("Invalid choice! Please select a valid option (1-5).\n");
        }
    }

    return 0;
}

// 2048 Game
void play2048() {
    int board[SIZE][SIZE]; // The game board
    int score = 0; // Player's score
    int moved; // Flag indicating if a move has been made
    char input; // Variable for user input

    srand(time(0)); // Seed the random number generator

    start_game: // Label to restart the game if the player chooses to retry
    initialize_game(board, &score);

    printf("Welcome to 2048!\n");
    printf("Instructions:\n");
    printf("- Use W (up), A (left), S (down), D (right) to move tiles.\n");
    printf("- Combine tiles with the same number to add them together.\n");
    printf("- Reach 2048 to win! Press Q to quit anytime.\n");
    printf("- Press R to restart at any time.\n\n");
    system("pause");

    while (1) {
        print_board(board, score);

        if (check_win(board)) {
            printf("Congratulations! You've reached 2048!\n");
            break;
        }

        if (!can_move(board)) {
            printf("Game Over! No more moves.\n");
            printf("Your final score: %d\n", score);
            break;
        }

        // Handle user input for movement or to retry the game
        input = _getch();
        if (input == 'r' || input == 'R') {
            printf("Restarting the game...\n");
            goto start_game; // Restart the game
        }
        
        if (input == 'q' || input == 'Q') {
            printf("You quit the game. Final Score: %d\n", score);
            break;
        }

        moved = handle_input(board, &score); // Handle user input for movement
        if (moved) add_random_tile(board); // Add a new random tile if a move was made
    }

    // Ask if the player wants to play again after the game ends
    printf("Would you like to retry the game? (Y/N): ");
    input = _getch();
    if (input == 'Y' || input == 'y') {
        goto start_game; // Restart the game if player chooses 'Y'
    } else {
        printf("Exiting to menu...\n");
    }
}

// Initialize the 2048 board
void initialize_game(int board[SIZE][SIZE], int *score) {
    *score = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0; // Initialize all tiles to 0
        }
    }
    add_random_tile(board); // Add first random tile
    add_random_tile(board); // Add second random tile
}

// Print the 2048 board and the current score
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
    printf("Controls: W (up), A (left), S (down), D (right), Q (quit), R (restart)\n");
}

// Add a random tile (2 or 4) to the board
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
        board[i][j] = (rand() % 2 + 1) * 2; // Randomly place a 2 or 4
    }
}

// Handle user input (WASD for movement)
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
            break;
        default: 
            printf("Invalid input. Use W, A, S, D, or Q to quit.\n");
            break;
    }
    return moved;
}

// Move tiles to the left
void move_left(int board[SIZE][SIZE], int *score, int *moved) {
    for (int i = 0; i < SIZE; i++) { // Loop through each row
        int pos = 0; // Position to place the next non-zero tile
        for (int j = 0; j < SIZE; j++) { // Loop through each tile in the row
            if (board[i][j] != 0) { // If the tile is not empty
                if (pos > 0 && board[i][pos - 1] == board[i][j]) { // If the tile can combine with the previous one
                    board[i][pos - 1] *= 2; // Double the tile value
                    *score += board[i][pos - 1]; // Add the value to the score
                    board[i][j] = 0; // Set the current tile to 0 as it's merged
                    *moved = 1; // Mark that a move was made
                } else if (pos != j) { // If the tile isn't already in the correct position
                    board[i][pos++] = board[i][j]; // Move the tile to the new position
                    board[i][j] = 0; // Set the original position to 0
                    *moved = 1; // Mark that a move was made
                } else {
                    pos++; // Increment the position if no merging happened
                }
            }
        }
    }
}

// Move tiles to the right
void move_right(int board[SIZE][SIZE], int *score, int *moved) {
    for (int i = 0; i < SIZE; i++) { // Loop through each row
        int pos = SIZE - 1; // Position to place the next non-zero tile from the right
        for (int j = SIZE - 1; j >= 0; j--) { // Loop through each tile in reverse
            if (board[i][j] != 0) { // If the tile is not empty
                if (pos < SIZE - 1 && board[i][pos + 1] == board[i][j]) { // If the tile can combine with the next one
                    board[i][pos + 1] *= 2; // Double the tile value
                    *score += board[i][pos + 1]; // Add the value to the score
                    board[i][j] = 0; // Set the current tile to 0 as it's merged
                    *moved = 1; // Mark that a move was made
                } else if (pos != j) { // If the tile isn't already in the correct position
                    board[i][pos--] = board[i][j]; // Move the tile to the new position
                    board[i][j] = 0; // Set the original position to 0
                    *moved = 1; // Mark that a move was made
                } else {
                    pos--; // Increment the position if no merging happened
                }
            }
        }
    }
}

// Move tiles up
void move_up(int board[SIZE][SIZE], int *score, int *moved) {
    for (int j = 0; j < SIZE; j++) { // Loop through each column
        int pos = 0; // Position to place the next non-zero tile
        for (int i = 0; i < SIZE; i++) { // Loop through each tile in the column
            if (board[i][j] != 0) { // If the tile is not empty
                if (pos > 0 && board[pos - 1][j] == board[i][j]) { // If the tile can combine with the previous one
                    board[pos - 1][j] *= 2; // Double the tile value
                    *score += board[pos - 1][j]; // Add the value to the score
                    board[i][j] = 0; // Set the current tile to 0 as it's merged
                    *moved = 1; // Mark that a move was made
                } else if (pos != i) { // If the tile isn't already in the correct position
                    board[pos++][j] = board[i][j]; // Move the tile to the new position
                    board[i][j] = 0; // Set the original position to 0
                    *moved = 1; // Mark that a move was made
                } else {
                    pos++; // Increment the position if no merging happened
                }
            }
        }
    }
}

// Move tiles down
void move_down(int board[SIZE][SIZE], int *score, int *moved) {
    for (int j = 0; j < SIZE; j++) { // Loop through each column
        int pos = SIZE - 1; // Position to place the next non-zero tile from the bottom
        for (int i = SIZE - 1; i >= 0; i--) { // Loop through each tile in reverse order
            if (board[i][j] != 0) { // If the tile is not empty
                if (pos < SIZE - 1 && board[pos + 1][j] == board[i][j]) { // If the tile can combine with the next one
                    board[pos + 1][j] *= 2; // Double the tile value
                    *score += board[pos + 1][j]; // Add the value to the score
                    board[i][j] = 0; // Set the current tile to 0 as it's merged
                    *moved = 1; // Mark that a move was made
                } else if (pos != i) { // If the tile isn't already in the correct position
                    board[pos--][j] = board[i][j]; // Move the tile to the new position
                    board[i][j] = 0; // Set the original position to 0
                    *moved = 1; // Mark that a move was made
                } else {
                    pos--; // Increment the position if no merging happened
                }
            }
        }
    }
}

// Check if there are any possible moves left
int can_move(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) return 1; // If there's an empty space, a move is possible
            if (i + 1 < SIZE && board[i][j] == board[i + 1][j]) return 1; // Check if adjacent tiles can combine vertically
            if (j + 1 < SIZE && board[i][j] == board[i][j + 1]) return 1; // Check if adjacent tiles can combine horizontally
        }
    }
    return 0; // No more moves possible
}

// Check if the player has won the game (2048 tile)
int check_win(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == TARGET) return 1; // If any tile is 2048, the player wins
        }
    }
    return 0; // No winning tile
}


// Placeholder function for Memory Game
void memoryGame() {
    int sequence[MAX_SEQUENCE_LENGTH]; // Array to hold the sequence of numbers
    int user_input[MAX_SEQUENCE_LENGTH]; // Array to hold the user's input
    int round = 1; // Current round number
    int i, j; // Loop counters
    int correct; // Flag to check if the user's input is correct

    srand(time(0)); // Seed the random number generator

    printf("\nMemory Game - Memorize the sequence of numbers!\n");

    while (round <= MAX_SEQUENCE_LENGTH) {
        printf("\nRound %d: Memorize the sequence!\n", round);

        // Generate a random sequence of numbers for the current round
        for (i = 0; i < round; i++) {
            sequence[i] = rand() % 10 + 1; // Random number between 1 and 10
        }

        // Display the sequence to the user
        printf("Sequence: ");
        for (i = 0; i < round; i++) {
            printf("%d ", sequence[i]);
        }
        printf("\n");

        // Wait for 3 seconds to allow the user to memorize the sequence
        Sleep(3000);

        // Clear the console screen
        system("cls");

        // Ask the user to enter the sequence
        printf("Enter the sequence of numbers (one by one):\n");
        correct = 1; // Assume the user's input is correct initially

        for (i = 0; i < round; i++) {
            printf("Enter number %d: ", i + 1);
            scanf("%d", &user_input[i]);

            // Check if the input is correct
            if (user_input[i] != sequence[i]) {
                correct = 0; // Incorrect input
                break; // Exit the loop if the user makes a mistake
            }
        }

        // Check if the user's input matches the sequence
        if (correct) {
            printf("Correct! Moving to the next round...\n");
            round++; // Move to the next round if the sequence was correct
        } else {
            printf("Wrong sequence! Game Over.\n");
            break; // Exit the game if the sequence is incorrect
        }

        // Optional: Pause before the next round
        printf("Press any key to continue to the next round...\n");
        _getch();
    }

    if (round > MAX_SEQUENCE_LENGTH) {
        printf("Congratulations! You've completed all rounds!\n");
    } else {
        printf("Better luck next time!\n");
    }
}

// Tic Tac Toe Implementation
void ticTacToe() {
    char board[3][3]; // 3x3 Tic Tac Toe board
    int i, j, move, moves = 0; // i, j for loops, move for player input, moves to track the number of moves made
    char player = 'X'; // Start with player 'X'
    int positions[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}; // The board positions (1-9) for user to choose

    // Initialize the board with empty spaces (' ')
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            board[i][j] = ' '; // Fill each cell with empty space
        }
    }

    // Game loop - continue until all 9 moves are made
    while (moves < 9) {
        system("cls"); // Clear the console screen
        printf("Tic Tac Toe\n");

        // Display the current board state
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                // If the cell is empty, print the position number, else print 'X' or 'O'
                if (board[i][j] == ' ')
                    printf(" %d ", positions[i][j]); // Show the number for empty spots
                else
                    printf(" %c ", board[i][j]); // Show 'X' or 'O' for filled spots

                // Print vertical divider between columns except the last column
                if (j < 2) printf("|");
            }
            // Print horizontal divider between rows except the last row
            if (i < 2) printf("\n---|---|---\n");
        }

        // Prompt the current player to enter their move
        printf("\nPlayer %c, enter your move (1-9): ", player);
        scanf("%d", &move); // Read the player's move (1-9)

        // Convert the move (1-9) into row and column indexes (0-2)
        int row = (move - 1) / 3; // Determine the row based on the move number
        int col = (move - 1) % 3; // Determine the column based on the move number

        // Validate the move - check if it's within range and the chosen cell is empty
        if (move < 1 || move > 9 || board[row][col] != ' ') {
            printf("Invalid move! Press any key to try again...\n");
            _getch(); // Wait for key press to proceed
            continue; // If the move is invalid, restart the loop and ask again
        }

        // Update the board with the current player's symbol ('X' or 'O') and increment move counter
        board[row][col] = player;
        moves++;

        // Check if the current player has won after their move
        for (i = 0; i < 3; i++) {
            // Check rows for a win
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
                system("cls"); // Clear screen
                printf("Player %c wins!\n", player); // Declare the winner
                return; // End the game if someone wins
            }
            // Check columns for a win
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
                system("cls");
                printf("Player %c wins!\n", player);
                return;
            }
        }

        // Check diagonals for a win
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

        // Switch to the next player (alternating between 'X' and 'O')
        player = (player == 'X') ? 'O' : 'X';
    }

    // If no winner and all moves are made, it's a draw
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
