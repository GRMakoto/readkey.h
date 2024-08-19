#include <unistd.h>
#include <termios.h>

static char read_key();

static char read_key() {
    static struct termios oldt, newt;
    tcgetattr(0, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ECHO | ICANON);
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &newt);

    char c;
    if(read(0, &c, 1) == -1){
        return -1;
    }

    tcsetattr(1, TCSANOW, &oldt);
    return c;
}
