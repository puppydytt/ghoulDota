#include <stdbool.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>

void execReturn(void) {
    INPUT Return[1] = {};
    Return[0].type = INPUT_KEYBOARD;
    Return[0].ki.wVk = 0;
    Return[0].ki.dwFlags = KEYEVENTF_SCANCODE;
    Return[0].ki.wScan = 0x1C;
    SendInput(1, Return, sizeof(Return));
    Return[0].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, Return, sizeof(Return));
    return;
}

void execTab(void) {
    INPUT tabKey[1] = {};
    tabKey[0].type = INPUT_KEYBOARD;
    tabKey[0].ki.wVk = 0;
    tabKey[0].ki.dwFlags = KEYEVENTF_SCANCODE;
    tabKey[0].ki.wScan = 0x0F;
    SendInput(1, tabKey, sizeof(tabKey));
    tabKey[0].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, tabKey, sizeof(tabKey));

    return;
}

//strat: discharge 4 ? -1 | discharge 3 ? - 2 ... discharge 2 ? 3

void execPaste(void) {
    INPUT Ctrl[1] = {};
    Ctrl[0].type = INPUT_KEYBOARD;
    Ctrl[0].ki.wVk = 0;
    Ctrl[0].ki.dwFlags = KEYEVENTF_SCANCODE;
    Ctrl[0].ki.wScan = 0x1D;

    SendInput(1, Ctrl, sizeof(Ctrl));


    Ctrl[0].type = INPUT_KEYBOARD;
    Ctrl[0].ki.wVk = 0;
    Ctrl[0].ki.dwFlags = KEYEVENTF_SCANCODE;
    Ctrl[0].ki.wScan = 0x2F;

    SendInput(1, Ctrl, sizeof(Ctrl));


    Ctrl[0].type = INPUT_KEYBOARD;
    Ctrl[0].ki.wVk = 0;
    Ctrl[0].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    Ctrl[0].ki.wScan = 0x1D;

    SendInput(1, Ctrl, sizeof(Ctrl));

    Ctrl[0].type = INPUT_KEYBOARD;
    Ctrl[0].ki.wVk = 0;
    Ctrl[0].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    Ctrl[0].ki.wScan = 0x2F;

    SendInput(1, Ctrl, sizeof(Ctrl));

}

int dischargeCount(int num) {
    int discharge = 0;
    while (1) {
        printf("%d\n", num);
        num /= 10;
        discharge++;
        if (num < 1) return discharge;
    }
}

void Output(void) {
    static int startPoint = 1000;

    int discharges = dischargeCount(startPoint);

    printf("discharges = %d\n", discharges);

    char * stringedValue;

    stringedValue = malloc((discharges + 3) * sizeof(char));

    if(stringedValue == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }

    sprintf(stringedValue, "%d", startPoint * 1000);

    printf("paresd num buff  = %s\n", stringedValue);
    stringedValue[discharges] = '-';
    stringedValue[discharges + 1] = '7';
    stringedValue[discharges + 2] = '?';

    printf("size of num after = %s\n", stringedValue);

    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, strlen(stringedValue) + 1);
    memcpy(GlobalLock(hMem), stringedValue, strlen(stringedValue) + 1);

    GlobalUnlock(hMem);
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();

    execReturn();
    execTab();
    execPaste();
    Sleep(300);
    execReturn();

    startPoint -= 7;

    free(stringedValue);

    if(startPoint == 6) {
        startPoint = 1000; // reset variable
    }

    return;
}

//done