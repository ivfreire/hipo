#include "HIPO.h"

int main() {
    HIPO_Init();

    memory[0] = 180;    // lei 80
    memory[1] = 380;    // cga 80
    memory[2] = 707;    // dez 07
    memory[3] = 381;    // cga 81
    memory[4] = 580;    // som 80
    memory[5] = 481;    // cag 81
    memory[6] = 600;    // des 00
    memory[7] = 200;    // imp
    memory[8] = 800;    // fim

    HIPO_Run(0);
    
    HIPO_Quit();
    return 0;
}