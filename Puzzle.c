#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
    int board[9];
    int empty_idx;
    int moves;
} PuzzleState;

bool is_solved(PuzzleState *state) {
    for (int i = 0; i < 8; i++) {
        if (state->board[i] != i + 1) return false;
    }
    return state->board[8] == 0;
}

bool is_solvable(int board[]) {
    int inversions = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (board[i] && board[j] && board[i] > board[j]) {
                inversions++;
            }
        }
    }
    return (inversions % 2 == 0);
}

void shuffle_board(PuzzleState *state) {
    do {
        for (int i = 0; i < 9; i++) {
            state->board[i] = i;
        }
        
        for (int i = 8; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = state->board[i];
            state->board[i] = state->board[j];
            state->board[j] = temp;
        }
    } while (!is_solvable(state->board) || is_solved(state));

    for (int i = 0; i < 9; i++) {
        if (state->board[i] == 0) {
            state->empty_idx = i;
            break;
        }
    }
}

void draw_board(WINDOW *win, PuzzleState *state) {
    wclear(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, " 8-Puzzle ");
    
    for (int i = 0; i < 9; i++) {
        int y = (i / 3) * 2 + 2;
        int x = (i % 3) * 4 + 4;
        
        if (state->board[i] == 0) {
            mvwprintw(win, y, x, "   ");
        } else {
            mvwprintw(win, y, x, "[%d]", state->board[i]);
        }
    }
    mvwprintw(win, 8, 2, "Hamle: %d", state->moves);
    mvwprintw(win, 9, 2, "Cikis icin 'q'");
    wrefresh(win);
}

void move_tile(PuzzleState *state, int new_idx) {
    int temp = state->board[state->empty_idx];
    state->board[state->empty_idx] = state->board[new_idx];
    state->board[new_idx] = temp;
    state->empty_idx = new_idx;
    state->moves++;
}

int main() {
    srand(time(NULL));
    
    PuzzleState state;
    state.moves = 0;
    shuffle_board(&state);

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int starty = (LINES - 11) / 2;
    int startx = (COLS - 20) / 2;
    WINDOW *game_win = newwin(11, 20, starty, startx);

    int ch;
    bool playing = true;

    while (playing) {
        draw_board(game_win, &state);

        if (is_solved(&state)) {
            mvwprintw(game_win, 10, 2, "KAZANDINIZ!   ");
            wrefresh(game_win);
            getch();
            break;
        }

        ch = getch();
        int ex = state.empty_idx % 3;
        int ey = state.empty_idx / 3;

        switch (ch) {
            case KEY_UP: 
            case 'w': 
                if (ey < 2) move_tile(&state, state.empty_idx + 3); 
                break;
            case KEY_DOWN: 
            case 's': 
                if (ey > 0) move_tile(&state, state.empty_idx - 3); 
                break;
            case KEY_LEFT: 
            case 'a': 
                if (ex < 2) move_tile(&state, state.empty_idx + 1); 
                break;
            case KEY_RIGHT: 
            case 'd': 
                if (ex > 0) move_tile(&state, state.empty_idx - 1); 
                break;
            case 'q':
                playing = false; 
                break;
        }
    }

    delwin(game_win);
    endwin();
    return 0;
}
