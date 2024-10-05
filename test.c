#include <unistd.h>
#include <time.h>

//"\x1b[31m"

char board[20][10];

void display_board(char board[20][10]) {

    int size=20*(10*(6)+1)+3;
    char chars[size];

    chars[0]='\033';
    chars[1]='[';
    chars[2]='H';

    int i=3;

    for (int y=0; y<20; y++) {
        for (int x=0; x<10; x++) {
        
            chars[i++]='\x1b';
            chars[i++]='[';
            chars[i++]=board[y][x];
            chars[i++]='m';
            chars[i++]='#';
            chars[i++]=' ';

        }
        chars[i++]='\n';
    }

    write(1,&chars,size);
    
}

int main (void) {

    for (int y=0; y<20; y++) {
        for (int x=0; x<10; x++) {
            board[y][x]='6';
        }
    }

    display_board(board);

    return 0;
}
