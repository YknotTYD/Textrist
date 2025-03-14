//main.c

#include "../include/main.h"

struct termios old_termios, new_termios;
char grid[20][10];

static void display_grid(void)
{
    printf("\x1b[0H");
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            if (grid[y][x])
                printf(COLOR_GREEN"  "COLOR_DEFAULT);
            if (grid[y][x] == 0)
                printf(COLOR_BLACK"  "COLOR_DEFAULT);
        }
        printf(COLOR_DEFAULT"\n");
    }
    usleep(5e+4);
    grid[0][0] = !grid[0][0];
    return;
}

int main(void)
{
    int key;

    set_nonblocking(0);
    enter_raw_mode();
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            grid[y][x] = (x + y) % 2;
        }
    }
    while (1) {
        key = read_key();
        if (key) {
            //printf("%i\n", key);
        }
        display_grid();
    }
    exit_raw_mode();
    return 0;
}

