#ifndef HIPO_H
#define HIPO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEI(ID) (100 + ID)  // Armazena input do usuário no endereço especificado.
#define IMP 200             // Imprime na tela o valor do endeteço especificado.
#define CGA(ID) (300 + ID)  // Carrega valor do endereço especificado para o cache.
#define CAG(ID) (400 + ID)  // Carrega valor do cache para o endereço especificado.
#define SOM(ID) (500 + ID)  // Soma valor do endereço especificado com o cache.
#define DES(ID) (600 + ID)  // Desvia o API para o endereço especificado.
#define DEZ(ID) (700 + ID)  // Desvia condicionalmente o API para o endereço especificado (se cache for igual a 0).
#define FIM 800             // Finaliza a execução do programa.

#define HIPO_DEFAULT                0   // Carrega a memória virgem (sem instruções).
#define HIPO_APP_BASIC_SUM          1   // Carrega um programa de soma básica de dois números na memória.
#define HIPO_APP_SEQ_SUM            2   // Carrega um programa para soma de uma sequência numérica terminada em 0 na memória.
#define HIPO_APP_BASIC_QUAD_MULT    3   // Carrega um program que multiplica o input do usuário por 4 se este for diferente de 0.

void HIPO_Init(int program);
void HIPO_ReadAPI();
void HIPO_ReadInstruction();
void HIPO_Run();
void HIPO_LoadProgram(int id);
void HIPO_Quit();
void lei(int addr);
void imp();
void cga(int addr);
void cag(int addr);
void som(int addr);
void des(int addr);
void dez(int addr);
void fim();

int memory[99];
int cache;
int* api, index;
int running;

/*
    ÍNDICE DAS INSTRUÇÕES
    NOME    ID      STATUS  DESCRIÇÃO
    LEI     01      fatto   Lê input do teclado.
    IMP     02      fatto   Imprime o valor de uma gaveta na tela.
    CGA     03      fatto   Carrega da gaveta para o cache.
    CAG     04      fatto   Carrega do cache para a gaveta.
    SOM     05      fatto   Soma a gaveta com o cache.
    DES     06      fatto   Desvia o API para outro endereço.
    DEZ     07      fatto   Desvia o API se o cache é 0.
    FIM     08      fatto   Finaliza o código.
*/

// Inicializa a memória do HIPO, o cache do processador e o API.
void HIPO_Init(int program) {
    for (int i = 0; i < 100; i++) memory[i] = 0;
    cache   = 0;
    printf("HIPO: POWER ON\n");
    if (program != 0) HIPO_LoadProgram(program);
}

// Roda as instruções a partir do endereço especificado.
void HIPO_Run(int addr) {
    index   = addr;
    api     = &memory[index];
    running = 1;
    while (running == 1) HIPO_ReadAPI();
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
    if (id == 0) fim();
    if (id == 1) lei(operand);
    if (id == 2) imp(operand);
    if (id == 3) cga(operand);
    if (id == 4) cag(operand);
    if (id == 5) som(operand);
    if (id == 6) des(operand);
    if (id == 7) dez(operand);
    if (id == 8) fim();
}

// Carrega um programa pré-programado na memória do HIPO.
void HIPO_LoadProgram(int id) {
    if (id == HIPO_APP_BASIC_SUM) {
        memory[0] = 180;    // LEI 80
        memory[1] = 181;    // LEI 81
        memory[2] = 380;    // CGA 80
        memory[3] = 581;    // SOM 81
        memory[4] = 481;    // CAG 81
        memory[5] = 281;    // IMP
        memory[6] = 800;    // FIM
        printf("HIPO: BASIC_SUM loaded.\n");
    }
    if (id == HIPO_APP_SEQ_SUM) {
        memory[0] = 180;    // LEI 80
        memory[1] = 380;    // CGA 80
        memory[2] = 707;    // DEZ 07
        memory[3] = 381;    // CGA 81
        memory[4] = 580;    // SOM 80
        memory[5] = 481;    // CAG 81
        memory[6] = 600;    // DES 00
        memory[7] = 281;    // IMP 81
        memory[8] = 800;    // FIM
        printf("HIPO: SEQ_SUM loaded.\n");
    }
    if (id == HIPO_APP_BASIC_QUAD_MULT) {
        memory[0] = 110;    // LEI 10
        memory[1] = 310;    // CGA 10
        memory[2] = 707;    // DEZ 07
        memory[3] = 510;    // SOM 10
        memory[4] = 510;    // SOM 10
        memory[5] = 510;    // SOM 10
        memory[6] = 410;    // CAG 10
        memory[7] = 210;    // IMP 10
        memory[8] = 800;    // FIM
        printf("HIPO: QUAD_MULT loaded.\n");
    }

}

// Libera a memória utilizada pela biblioteca.
void HIPO_Quit() {
    printf("HIPO: POWER OFF\n");
}

// MÉTODOS DO COMPILADOR

int HIPO_Encode(char cmd[10], char op[10]) {
    int _op = atoi(op);
    if (strcmp(cmd, "LEI") == 0) return 100 + _op;
    if (strcmp(cmd, "IMP") == 0) return 200 + _op;
    if (strcmp(cmd, "CGA") == 0) return 300 + _op;
    if (strcmp(cmd, "CAG") == 0) return 400 + _op;
    if (strcmp(cmd, "SOM") == 0) return 500 + _op;
    if (strcmp(cmd, "DES") == 0) return 600 + _op;
    if (strcmp(cmd, "DEZ") == 0) return 700 + _op;
    if (strcmp(cmd, "FIM") == 0) return 800 + _op;
    return 0;
}

void HIPO_LoadFile(const char* path) {
    FILE *source;
    source = fopen(path, "r");
    char string[10], cmd[10], op[10]; int m_index = 0;
    while (strcmp(string, "FIM") != 0) {
        strcpy(cmd, ""); strcpy(op, "");
        fscanf(source, "%s", string);
        strcpy(cmd, string);
        if (strcmp(cmd, "FIM") != 0) {
            fscanf(source, "%s", string);
            strcpy(op, string);
        }
        memory[m_index] = HIPO_Encode(cmd, op);
        m_index++;
    }
    fclose(source);
}

// INSTRUÇÕES DO INTERPRETADOR

// Lê input numérico do usuário e armazena no endereço de memória indicado.
void lei(int addr) {
    printf("INPUT: ");
    scanf("%d", &memory[addr]);
}

// Imprime o valor do cache na tela.
void imp(int addr) {
    printf("M[%d]: %d\n", addr, memory[addr]);
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
    index   = addr - 1;
}

// Desvia o API para o endereço de memória especificado se 
void dez(int addr) {
    if (cache == 0) index   = addr - 1;
}

// Finaliza a execução do programa.
void fim() {
    running = 0;
}

#endif