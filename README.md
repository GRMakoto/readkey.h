# readkey.h
Simple single header crossplatform library for reading a key from a terminal.
# Usage 
Just include `readkey.h` in your project and call the `read_key()` function
# Example
```c
#include <stdio.h>
#include "readkey.h"

int main() {
    char c;
    while ((c = read_key()) != 'e') {
        printf("%c\n", c);
    }
    return 0;
}
```
