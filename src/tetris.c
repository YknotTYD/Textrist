//tetris.c

#include "../include/main.h"

int vects[1][4][2] = {
    {{-1, 1}, {1, 1}, {0, 1}, {0, 0}}
};
int terminal_size[2];

static int current_piece_is_free(char grid[20][10], int pos[2])
{
    int x;
    int y;

    for (int i = 0; i < 4; i++) {
        x = pos[0] + vects[0][i][0];
        y = pos[1] + vects[0][i][1];
        if (x < 0 || x >= 10)
            return 0;
        if (y < 0 || y >= 20)
            return 0;
        if (grid[y][x] != GRID_NONE)
            return 0;
    }
    return 1;
}

int try_to_go(char grid[20][10], int pos[2], int x, int y)
{
    pos[0] += x;
    pos[1] += y;
    if (!current_piece_is_free(grid, pos)) {
        pos[0] -= x;
        pos[1] -= y;
        return 1;
    }
    return 0;
}

void update_grid_fall(char grid[20][10], int pos[2])
{
    try_to_go(grid, pos, 0, 1);
    return;
}

void update_grid_key(char grid[20][10], int pos[2], int key)
{
    if (key == KEY_DOWN) {
        try_to_go(grid, pos, 0, 1);
    }
    if (key == KEY_LEFT) {
        try_to_go(grid, pos, -1, 0);
    }
    if (key == KEY_RIGHT) {
        try_to_go(grid, pos, 1, 0);
    }
    if (key == KEY_UP) {
        while (try_to_go(grid, pos, 0, 1) == 0);
    }
    return;
}
