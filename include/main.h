//main.h

#ifndef TEXTRIS_MAIN_H

    #define TEXTRIS_MAIN_H

    #define KEY_DOWN  -1
    #define KEY_UP    -2
    #define KEY_LEFT  -3
    #define KEY_RIGHT -4

    #define GRID_T 0
    #define GRID_I 1
    #define GRID_O 2
    #define GRID_L 3
    #define GRID_J 4
    #define GRID_SL 5
    #define GRID_SR 6
    #define GRID_NONE 7
    #define GRID_RAND (rand() % 7)

    #define COLOR_DEFAULT "\x1b[0m"
    #define COLOR_BLACK "\x1b[48;2;0;0;0m"
    #define COLOR_PURPLE "\x1b[48;2;222;0;255m"
    #define COLOR_CYAN "\x1b[48;2;0;255;255m"
    #define COLOR_YELLOW "\x1b[48;2;255;255;0m"
    #define COLOR_ORANGE "\x1b[48;2;255;177;0m"
    #define COLOR_BLUE "\x1b[48;2;0;0;255m"
    #define COLOR_GREEN "\x1b[48;2;0;255;0m"
    #define COLOR_RED "\x1b[48;2;255;0;0m"
    #define COLOR_MAGENTA "\x1b[48;2;255;0;255m"

    #define NOW (clock() / (double)CLOCKS_PER_SEC)

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/ioctl.h>
#include <stdlib.h>

typedef struct {
    struct termios old_termios, new_termios;
    int terminal_size[2];
    int current_piece;
    int pos[2];
    char grid[20][10];
} context_t;

void enter_raw_mode(context_t *context);
void exit_raw_mode(context_t *context);
void set_nonblocking(int fd);
int read_key(void);
void update_grid_fall(context_t *context);
void update_grid_key(context_t *context, int key);
void update_terminal_size(void);

extern const int vects[7][1][4][2];
extern context_t context;

#endif
