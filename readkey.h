#ifndef READKEY_H
#define READKEY_H

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

#if defined __cplusplus
extern "C" {
#endif

/**
 * @brief Reads a key input from the terminal.
 * @return the ASCII value of the key on success, -1 otherwise.
*/
static char read_key();

#ifdef _WIN32
static char read_key() {
    HANDLE hStdin ;
    INPUT_RECORD ir;
    DWORD cNumRead;
    if ((hStdin = GetStdHandle(STD_INPUT_HANDLE)) == INVALID_HANDLE_VALUE) {
        return -1;
    }

    int max_iter = 10000;
    do {
        if(!ReadConsoleInput(
            hStdin,
            &ir,
            1,
            &cNumRead)) {
            return -1;
        }

        if(ir.EventType == KEY_EVENT) {
            if (ir.Event.KeyEvent.bKeyDown && ir.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT) {
                return ir.Event.KeyEvent.uChar.AsciiChar;
            }
        }
    } while(max_iter-- > 0);

    return -1;
}



#else
static char read_key() {
    static struct termios oldt, newt;
    if(tcgetattr(0, &oldt) == -1) {
        return -1;
    }

    newt = oldt;
    newt.c_lflag &= ~(ECHO | ICANON);
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;

    if(tcsetattr(0, TCSANOW, &newt) == -1) {
        return -1;
    }

    char c;
    if(read(0, &c, 1) == -1) {
        return -1;
    }

    if(tcsetattr(0, TCSANOW, &newt) == -1) {
        tcsetattr(1, TCSANOW, &oldt);
    }

    return c;
}

#if defined __cplusplus
}
#endif

#endif

#endif
