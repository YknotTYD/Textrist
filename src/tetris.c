//tetris.c

#include "../include/main.h"

const int vects[7][1][4][2] = {
    {{{-1, 1}, {1, 1},  {0, 1},   {0, 0}}},  //T
    {{{0, -1}, {0, 0},  {0, 1},   {0, 2}}},  //I
    {{{1, 1},  {0, 0},  {0, 1},   {1, 0}}},  //O
    {{{0, -1}, {0, 0},  {0, 1},   {1, 1}}},  //L
    {{{0, -1}, {0, 0},  {0, 1},   {-1, 1}}}, //J
    {{{0, 0},  {-1, 0}, {-1, -1}, {0, 1}}},  //SL
    {{{0, 0},  {1, 0},  {1, 1},   {0, -1}}}  //SR
};

static int current_piece_is_free(context_t *context)
{
    int x;
    int y;

    for (int i = 0; i < 4; i++) {
        x = context->pos[0] + vects[context->current_piece][0][i][0];
        y = context->pos[1] + vects[context->current_piece][0][i][1];
        if (x < 0 || x >= 10)
            return 0;
        if (y < 0 || y >= 20)
            return 0;
        if (context->grid[y][x] != GRID_NONE)
            return 0;
    }
    return 1;
}

static int try_to_go(context_t *context, int x, int y)
{
    context->pos[0] += x;
    context->pos[1] += y;
    if (!current_piece_is_free(context)) {
        context->pos[0] -= x;
        context->pos[1] -= y;
        return 1;
    }
    return 0;
}

static void ascend_line(char grid[20][10], int y)
{
    for (int i = y; i >= 1; i--) {
        for (int x = 0; x < 10; x++) {
            grid[i][x] = grid[i - 1][x] ^ grid[i][x];
            grid[i - 1][x] = grid[i - 1][x] ^ grid[i][x];
            grid[i][x] = grid[i - 1][x] ^ grid[i][x];
        }
    }
    return;
}

static void update_lines(context_t *context)
{
    int has_empty;

    for (int y = 19; y >= 0; y--) {

        has_empty = 0;

        for (int x = 0; x < 10; x++) {
            if (context->grid[y][x] == GRID_NONE) {
                has_empty = 1;
                break;
            }
        }

        if (!has_empty) {
            for (int x = 0; x < 10; x++) {
                context->grid[y][x] = GRID_NONE;
            }
            ascend_line(context->grid, y);
            y++;
        }
    }
    return;
}

static void drop_piece(context_t *context)
{
    int x;
    int y;

    for (int i = 0; i < 4; i++) {

        x = context->pos[0] + vects[context->current_piece][0][i][0];
        y = context->pos[1] + vects[context->current_piece][0][i][1];
        if (x < 0 || x >= 10)
            continue;
        if (y < 0 || y >= 20)
            continue;
        context->grid[y][x] = context->current_piece;

    }

    update_lines(context);

    context->pos[0] = 4;
    context->pos[1] = 0;

    context->current_piece = GRID_RAND;

    return;
}

void update_grid_fall(context_t *context)
{
    if (try_to_go(context, 0, 1)) {
        drop_piece(context);
    }
    return;
}

void update_grid_key(context_t *context, int key)
{
    if (key == KEY_DOWN) {
        if (try_to_go(context, 0, 1)) {
            drop_piece(context);
        }
    }
    if (key == KEY_LEFT) {
        try_to_go(context, -1, 0);
    }
    if (key == KEY_RIGHT) {
        try_to_go(context, 1, 0);
    }
    if (key == KEY_UP) {
        while (try_to_go(context, 0, 1) == 0);
        drop_piece(context);
    }
    return;
}
