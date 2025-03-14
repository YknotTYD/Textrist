//main.h

#ifndef TEXTRIS_MAIN_H

    #define TEXTRIS_MAIN_H

    #define KEY_DOWN  -1
    #define KEY_UP    -2
    #define KEY_LEFT  -3
    #define KEY_RIGHT -4

    #define GRID_NONE 0
    #define GRID_PURPLE 1

    #define COLOR_PURPLE "\x1b[48;2;222;0;255m"
    #define COLOR_BLACK "\x1b[48;2;0;0;0m"
    #define COLOR_GREEN "\x1b[48;2;0;255;0m"
    #define COLOR_DEFAULT "\x1b[0m"

    #define NOW (clock() / (double)CLOCKS_PER_SEC)

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/ioctl.h>

void enter_raw_mode(void);
void exit_raw_mode(void);
void set_nonblocking(int fd);
int read_key(void);
void update_grid_fall(char grid[20][10], int pos[2]);
void update_grid_key(char grid[20][10], int pos[2], int key);
void update_terminal_size(void);

extern struct termios old_termios, new_termios;
extern int vects[1][4][2];
extern int terminal_size[2];

#endif
