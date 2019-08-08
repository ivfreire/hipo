#include <HIPO.h>

int main(int argc, char* argv[]) {
    HIPO_Init(HIPO_DEFAULT);

    HIPO_LoadFile(argv[1]);

    HIPO_Run(0);
    HIPO_Quit();
    return 0;
}