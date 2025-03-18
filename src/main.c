//main.c

#include "../include/main.h"

//make squares multiple chars to get like textures and stuff
//make it also wasd
//add a held piece
//add score
//add next piece display
//add menus
//add a multiplayer mode
//add an AI to play against
//add the actual rotations
//add achievements
//add death
//print everything with a single call to write
//put everythin in more files
//refactor the rendering functions

context_t context;

int main(void)
{
    int key;
    double last_fall;

    srand(time(0));
    set_nonblocking(0);
    enter_raw_mode(&context);
    printf("\x1b[?1049h\x1b[?25l");
    update_terminal_size();

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            context.grid[y][x] = GRID_NONE;
        }
    }

    context.pos[0] = 5;
    context.pos[1] = 5;
    for (int i = 0; i < INCOMING_SIZE; i++) {
        context.incoming[i] = GRID_RAND;
    }
    context.current_piece = GRID_RAND;
    context.held_piece = GRID_NONE;
    context.rotation = 0;
    context.can_switch_held = 1;

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

    printf("\x1b[?1049l\x1b[?25h");
    exit_raw_mode(&context);

    return 0;
}
