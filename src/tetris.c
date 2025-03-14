//tetris.c

#include "../include/main.h"

int vects[1][4][2] = {
    {{-1, 1}, {1, 1}, {0, 1}, {0, 0}}
};

void update_grid(char grid[20][10], int pos[2])
{
    (void)grid;
    (void)pos;
    pos[1] += 1;
    return;
}
