//input.C

#include "../include/main.h"

void enter_raw_mode(void)
{
    tcgetattr(0, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &new_termios);
    return;
}

void exit_raw_mode(void)
{
    tcsetattr(0, TCSANOW, &old_termios);
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
