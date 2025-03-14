//main.c

#include "../include/main.h"

//make squares multiple chars to get like textures and stuff
//make it also wasd

struct termios old_termios, new_termios;
char grid[20][10];
int pos[2];

static char *get_color(int x, int y)
{
    for (int i = 0; i < 4; i++) {
        if (x == pos[0] + vects[0][i][0] &&
            y == pos[1] + vects[0][i][1]) {
            return COLOR_PURPLE;
        }
    }
    if (grid[y][x] == GRID_NONE) {
        return COLOR_BLACK;
    }
    return COLOR_GREEN;
}

static void display_grid(void)
{
    printf("\x1b[0H");
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            printf("%s  ", get_color(x, y));
        }
        printf(COLOR_DEFAULT"\n");
    }
    return;
}

int main(void)
{
    int key;
    double last_fall;

    set_nonblocking(0);
    enter_raw_mode();
    printf("\x1b[?1049h");
    update_terminal_size();

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            grid[y][x] = GRID_NONE;
        }
    }

    pos[0] = 5;
    pos[1] = 5;

    last_fall = NOW;

    while (1) {
        key = read_key();
        if (key == 'q') {
            break;
        }
        if (key) {
            update_grid_key(grid, pos, key);
            display_grid();
        }
        if (NOW - last_fall >= 1 / 3.0) {
            update_grid_fall(grid, pos);
            display_grid();
            last_fall = NOW;
        }
    }

    printf("\x1b[?1049l");
    exit_raw_mode();

    return 0;
}
