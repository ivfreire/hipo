#ifndef HIPO_H
#define HIPO_H

#define nullptr NULL

#include <stdio.h>
#include <stdlib.h>

int memory[99];
int cache;
int* api, index;
int running;

/*
    ÍNDICE DAS INSTRUÇÕES
    Nome    ID      Status
    lei     01      fatto
    imp     02      fatto
    cga     03      fatto
    cag     04      fatto
    som     05      fatto
    des     06      fatto
    dez     07      fatto
    fim     08      fatto
*/

// Inicializa a memória do HIPO, o cache do processador e o API.
void HIPO_Init() {
    for (int i = 0; i < 100; i++) memory[i] = 0;
    cache   = 0;
    index   = 0;
    api     = &memory[index];
    printf("HIPO:\tPOWER ON\n");
}

// Passa próxima instrução para o API.
void HIPO_ReadAPI() {
    HIPO_ReadInstruction();
    index++;
    api = &memory[index];
}

// Lê instrução armazenada onde o API aponta.
void HIPO_ReadInstruction() {
    int id      = (int)(*api / 100);
    int operand = *api - id * 100;
    if (id == 1) lei(operand);
    if (id == 2) imp();
    if (id == 3) cga(operand);
    if (id == 4) cag(operand);
    if (id == 5) som(operand);
    if (id == 6) des(operand);
    if (id == 7) dez(operand);
    if (id == 8) fim();
}

// Roda as instruções a partir do endereço especificado.
void HIPO_Run(int addr) {
    index   = addr;
    api     = &memory[index];
    running = 1;
    while (running == 1) HIPO_ReadAPI();
}

// Libera a memória utilizada pela biblioteca.
void HIPO_Quit() {
    printf("HIPO:\tPOWER OFF\n");
}

// INSTRUÇÕES

// Lê input numérico do usuário e armazena no endereço de memória indicado.
void lei(int addr) {
    printf("INPUT: ");
    scanf("%d", &memory[addr]);
}

// Imprime o valor do cache na tela.
void imp() {
    printf("Cache: %d\n", cache);
}

// Carrega dado do endereço de memória especificado para o cache do processador.
void cga(int addr) {
    cache = memory[addr];
}

// Carrega dado do cache do processador para o endereço de memória especificado.
void cag(int addr) {
    memory[addr] = cache;
}

// Soma valor do endereço de memória especificado com o cache do processador e armazena o resultado no cache. 
void som(int addr) {
    cache += memory[addr];
}

// Desvia o API para o endereço de memória especificado.
void des(int addr) {
    index   = addr;
    api     = &memory[index];
}

// Desvia o API para o endereço de memória especificado se 
void dez(int addr) {
    if (cache == 0) {
        index   = addr;
        api     = &memory[index];
    }
}

// Finaliza a execução do programa.
void fim() {
    api     = nullptr;
    running = 0;
}

#endif