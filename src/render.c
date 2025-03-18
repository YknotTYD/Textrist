//render.c

#include "../include/main.h"

static char *get_grid_color(int piece)
{
    if (piece == GRID_NONE)
        return COLOR_BLACK;
    if (piece == GRID_T)
        return COLOR_PURPLE;
    if (piece == GRID_I)
        return COLOR_CYAN;
    if (piece == GRID_O)
        return COLOR_YELLOW;
    if (piece == GRID_L)
        return COLOR_ORANGE;
    if (piece == GRID_J)
        return COLOR_BLUE;
    if (piece == GRID_SL)
        return COLOR_GREEN;
    if (piece == GRID_SR)
        return COLOR_RED;
    if (piece == GRID_SHADOW)
        return COLOR_WHITE;
    return COLOR_MAGENTA;
}

static char *get_color(int x, int y)
{
    int old_pos[2];

    for (int i = 0; i < 4; i++) {
        if (x == context.pos[0] + vects[context.current_piece][context.rotation][i][0] &&
            y == context.pos[1] + vects[context.current_piece][context.rotation][i][1]) {
            return get_grid_color(context.current_piece);
        }
    }

    old_pos[0] = context.pos[0];
    old_pos[1] = context.pos[1];

    while (try_to_go(&context, 0, 1) == 0);

    for (int i = 0; i < 4; i++) {
        if (x == context.pos[0] + vects[context.current_piece][context.rotation][i][0] &&
            y == context.pos[1] + vects[context.current_piece][context.rotation][i][1]) {

            context.pos[0] = old_pos[0];
            context.pos[1] = old_pos[1];

            return get_grid_color(GRID_SHADOW);
        }
    }

    context.pos[0] = old_pos[0];
    context.pos[1] = old_pos[1];

    return get_grid_color(context.grid[y][x]);
}

static void print_next_line(int y)
{
    int pos[2];
    int color;
    int is_in;

    if (y == 0 || y % 6 == 0 || y == 19) {
        return;
    }

    printf(COLOR_DEFAULT"  ");

    for (int i = 0; i < 6; i++) {

        pos[0] = i - 2;
        pos[1] = y % 6 - 2;
        color = context.incoming[y / 6];
        is_in = 0;

        for (int j = 0; j < 4; j++) {
            if (pos[0] == vects[color][0][j][0] &&
                pos[1] == vects[color][0][j][1]) {
                is_in = 1;
                break;
            }
        }

        printf("%s  ", is_in ? get_grid_color(color) : COLOR_BLACK);

    }

    return;
}

static void print_previous_line(int y)
{
    int is_in;

    for (int i = 0; i < 8; i++) {
        if (i == 0 || y > 4 || i > 6) {
            printf(COLOR_DEFAULT"  ");
            continue;
        }
        is_in = 0;
        for (int j = 0; j < 4; j++) {
            if (i - 3 == vects[context.held_piece][0][j][0] &&
                y - 1 == vects[context.held_piece][0][j][1]) {
                is_in = 1;
                break;
            }
        }
        if (is_in) {
            printf("%s  ", get_grid_color(context.held_piece));
        } else {
            printf(COLOR_BLACK"  ");
        }
    }
    return;
}

void display_grid(void)
{
    printf("\x1b[0H"COLOR_DEFAULT"\n");
    for (int y = 0; y < 20; y++) {
        print_previous_line(y);
        for (int x = 0; x < 10; x++) {
            printf("%s  ", get_color(x, y));
        }
        print_next_line(y);
        printf("\n");
    }
    return;
}
