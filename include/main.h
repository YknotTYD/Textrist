//main.h

#ifndef TEXTRIS_MAIN_H

    #define TEXTRIS_MAIN_H

    #define KEY_DOWN  -1
    #define KEY_UP    -2
    #define KEY_LEFT  -3
    #define KEY_RIGHT -4

    #define GRID_PURPLE 1

    #define COLOR_BLACK "\x1b[48;2;0;0;0m"
    #define COLOR_GREEN "\x1b[48;2;0;255;0m"
    #define COLOR_DEFAULT "\x1b[0m"

    #define NOW (clock() / CLOCKS_PER_SEC)

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

void enter_raw_mode(void);
void exit_raw_mode(void);
void set_nonblocking(int fd);
int read_key(void);

extern struct termios old_termios, new_termios;

#endif
