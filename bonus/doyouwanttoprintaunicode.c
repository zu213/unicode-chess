// windows printing unicode characters, bonus skeleton file
#include <stdio.h>
#include <fcntl.h>
#include <io.h>

int main() {
    _setmode(_fileno(stdout), 0x00020000);

    // Print the wide character
    wprintf(L"print with hex \x263a \n");
    wchar_t wc = L'☃';
    wprintf(L"Wide character: %lc\n", wc);

    // Print a wide character string
    wchar_t wstr[] = L"Hello, 世界!";
    wprintf(L"Wide string: %ls\n", wstr);

    return 0;
}