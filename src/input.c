//input.C

#include "../include/main.h"

int terminal_size[2];

void enter_raw_mode(context_t *context)
{
    tcgetattr(0, &context->old_termios);
    context->new_termios = context->old_termios;
    context->new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &context->new_termios);
    return;
}

void exit_raw_mode(context_t *context)
{
    tcsetattr(0, TCSANOW, &context->old_termios);
    return;
}

void set_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);

    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    return;
}

int read_key(void)
{
    char c;

    if (read(STDIN_FILENO, &c, 1) == -1) {
        return 0;
    }
    if (c != 27) {
        return c;
    }

    if (read(STDIN_FILENO, &c, 1) == -1 || c != 91) {
        return 0;
    }
    if (read(STDIN_FILENO, &c, 1) == -1) {
        return 0;
    }

    if (c == 68)
        return KEY_LEFT;
    if (c == 67)
        return KEY_RIGHT;
    if (c == 65)
        return KEY_UP;
    if (c == 66)
        return KEY_DOWN;

    return 0;
}

void update_terminal_size(void)
{
    static struct winsize w;

    ioctl(1, TIOCGWINSZ, &w);
    terminal_size[0] = w.ws_row;
    terminal_size[1] = w.ws_col;
    return;
}
