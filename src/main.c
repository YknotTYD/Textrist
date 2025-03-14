//main.c

#include "../include/main.h"

//make squares multiple chars to get like textures and stuff
//make it also wasd
//add shadows
//add a held piece
//add score
//adde rotation
//add next piece display
//put everythong in a context_t
//add menus
//add a multiplayer mode

context_t context;

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
    return COLOR_MAGENTA;
}

static char *get_color(int x, int y)
{
    for (int i = 0; i < 4; i++) {
        if (x == context.pos[0] + vects[context.current_piece][0][i][0] &&
            y == context.pos[1] + vects[context.current_piece][0][i][1]) {
            return get_grid_color(context.current_piece);
        }
    }
    return get_grid_color(context.grid[y][x]);
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
    enter_raw_mode(&context);
    printf("\x1b[?1049h");
    update_terminal_size();

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            context.grid[y][x] = GRID_NONE;
        }
    }

    context.pos[0] = 5;
    context.pos[1] = 5;
    context.current_piece = GRID_RAND;

    last_fall = NOW;

    while (1) {
        key = read_key();
        if (key == 'q') {
            break;
        }
        if (key) {
            update_grid_key(&context, key);
            display_grid();
        }
        if (NOW - last_fall >= 1 / 3.0) {
            update_grid_fall(&context);
            display_grid();
            last_fall = NOW;
        }
    }

    printf("\x1b[?1049l");
    exit_raw_mode(&context);

    return 0;
}
