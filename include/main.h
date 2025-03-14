//main.h

#ifndef TEXTRIS_MAIN_H
    #define TEXTRIS_MAIN_H

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

void enter_raw_mode(void);
void exit_raw_mode(void);
void set_nonblocking(int fd);

extern struct termios old_termios, new_termios;

#endif
