//main.c

#include "../include/main.h"

struct termios old_termios, new_termios;

int main(void)
{
    char c;

    set_nonblocking(0);
    enter_raw_mode();
    while (1) {
        if (read(STDIN_FILENO, &c, 1) != -1) {
            printf("%i\n", c);
        }
    }
    exit_raw_mode();
    return 0;
}

