#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>  // For _kbhit() and _getch()

#define SIZE 4

int board[SIZE][SIZE] = {0};

void initialize_game() {
    // Initialize the board with two random tiles
    for (int i = 0; i < 2; i++) {
        add_random_tile();
    }
}

void print_board() {
    system("cls");  // Clear the console
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

int can_move() {
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

void add_random_tile() {
    int empty[SIZE * SIZE][2];  // List of empty cells (coordinates)
    int empty_count = 0;

    // Find empty cells
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
        board[i][j] = (rand() % 2 + 1) * 2;  // Either 2 or 4
    }
}

void move_left() {
    for (int i = 0; i < SIZE; i++) {
        int new_row[SIZE] = {0};  // New row after merging
        int pos = 0;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 0) {
                if (new_row[pos] == board[i][j]) {
                    new_row[pos - 1] *= 2;
                    pos--;
                } else {
                    new_row[pos] = board[i][j];
                }
                pos++;
            }
        }
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = new_row[j];
        }
    }
}

void move_right() {
    for (int i = 0; i < SIZE; i++) {
        int new_row[SIZE] = {0};
        int pos = SIZE - 1;
        for (int j = SIZE - 1; j >= 0; j--) {
            if (board[i][j] != 0) {
                if (new_row[pos] == board[i][j]) {
                    new_row[pos + 1] *= 2;
                    pos++;
                } else {
                    new_row[pos] = board[i][j];
                }
                pos--;
            }
        }
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = new_row[j];
        }
    }
}

void move_up() {
    for (int j = 0; j < SIZE; j++) {
        int new_col[SIZE] = {0};
        int pos = 0;
        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] != 0) {
                if (new_col[pos] == board[i][j]) {
                    new_col[pos - 1] *= 2;
                    pos--;
                } else {
                    new_col[pos] = board[i][j];
                }
                pos++;
            }
        }
        for (int i = 0; i < SIZE; i++) {
            board[i][j] = new_col[i];
        }
    }
}

void move_down() {
    for (int j = 0; j < SIZE; j++) {
        int new_col[SIZE] = {0};
        int pos = SIZE - 1;
        for (int i = SIZE - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                if (new_col[pos] == board[i][j]) {
                    new_col[pos + 1] *= 2;
                    pos++;
                } else {
                    new_col[pos] = board[i][j];
                }
                pos--;
            }
        }
        for (int i = 0; i < SIZE; i++) {
            board[i][j] = new_col[i];
        }
    }
}

void handle_input() {
    char input = _getch();  // Get key press

    switch (input) {
        case 'w':  // Move up
            move_up();
            break;
        case 's':  // Move down
            move_down();
            break;
        case 'a':  // Move left
            move_left();
            break;
        case 'd':  // Move right
            move_right();
            break;
        default:
            break;
    }
}

int main() {
    srand(time(0));
    initialize_game();

    while (1) {
        print_board();

        if (!can_move()) {
            printf("Game Over!\n");
            break;
        }

        handle_input();
        add_random_tile();
    }

    return 0;
}
