#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include "output.c"
#include "configReader/core.c"



int main(void) {
    ReadConfig();
    do {
        int keyStart = GetAsyncKeyState(0x75); //<- binded from cfg;
        int keyExit = GetAsyncKeyState(0x76); //<- binded from cfg;

        if (keyStart) {
            //stream timeout exec
            Output();
        } else if (keyExit) {
            return 0;
        }
    } while (1);
}