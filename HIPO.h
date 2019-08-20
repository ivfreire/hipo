#ifndef HIPO_H
#define HIPO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HIPO_DEFAULT                0   // Carrega a memória virgem (sem instruções).
#define HIPO_APP_BASIC_SUM          1   // Carrega um programa de soma básica de dois números na memória.
#define HIPO_APP_SEQ_SUM            2   // Carrega um programa para soma de uma sequência numérica terminada em 0 na memória.
#define HIPO_APP_BASIC_QUAD_MULT    3   // Carrega um program que multiplica o input do usuário por 4 se este for diferente de 0.

void HIPO_Init();
void HIPO_Run();
void HIPO_LoadFile(char* path);
void HIPO_ReadAPI();
void HIPO_ReadInstruction();
void HIPO_Quit();

void cea(int addr);
void cae(int addr);
void som(int addr);
void sub(int addr);
void mul(int addr);
void _div(int addr);
void mod(int addr);
void ler(int addr);
void imp(int addr);
void nop();
void des(int addr);
void dpo(int addr);
void dpz(int addr);
void dne(int addr);
void dnz(int addr);
void ddz(int addr);
void dzz(int addr);
void ade();
void add();
void par();

int memory[99];
int cache;
int* api, _index;
int running;

/*  
    NOME    CÓDIGO  DESCRIÇÃO
    CEA     11
    CAE     12
    SOM     21
    SUB     22
    MUL     23
    DIV     24
    MOD     25
    LER     31
    IMP     41
    NOP     50
    DES     51
    DPO     52
    DPZ     53
    DNE     54
    DNZ     55
    DDZ     56
    DZZ     57
    ADE     61
    ADD     62
    PAR     70
*/

// Inicializa a memória do HIPO, o cache do processador e o API.
void HIPO_Init() {
    for (int i = 0; i < 100; i++) memory[i] = 0;
    cache   = 0; _index  = 0;
    printf("HIPO: POWER ON\n");
}

// Roda as instruções a partir do endereço especificado.
void HIPO_Run(int addr) {
    _index   = addr;
    api     = &memory[_index];
    running = 1;
    while (running == 1) HIPO_ReadAPI();
}

// Passa próxima instrução para o API.
void HIPO_ReadAPI() {
    HIPO_ReadInstruction();
    _index++;
    api = &memory[_index];
}

// Lê instrução armazenada onde o API aponta.
void HIPO_ReadInstruction() {
    int id      = (int)(*api / 100);
    int operand = *api - id * 100;
    if (id ==  0) par();
    if (id == 11) cea(operand);
    if (id == 12) cae(operand);
    if (id == 21) som(operand);
    if (id == 22) sub(operand);
    if (id == 23) mul(operand);
    if (id == 24) _div(operand);
    if (id == 25) mod(operand);
    if (id == 31) ler(operand);
    if (id == 41) imp(operand);
    if (id == 50) nop();
    if (id == 51) des(operand);
    if (id == 52) dpo(operand);
    if (id == 53) dpz(operand);
    if (id == 54) dne(operand);
    if (id == 55) dnz(operand);
    if (id == 56) ddz(operand);
    if (id == 57) dzz(operand);
    if (id == 61) ade(operand);
    if (id == 62) add(operand);
    if (id == 70) par();
}

// Libera a memória utilizada pela biblioteca.
void HIPO_Quit() {
    printf("HIPO: POWER OFF\n");
}

// MÉTODOS DO COMPILADOR

// Transforma os comandos de alto nível para instruções numéricas.
int HIPO_Encode(char cmd[10], char op[10]) {
    int _op = atoi(op);
    if (strcmp(cmd, "CEA") == 0) return 1100 + _op;
    if (strcmp(cmd, "CAE") == 0) return 1200 + _op;
    if (strcmp(cmd, "SOM") == 0) return 2100 + _op;
    if (strcmp(cmd, "SUB") == 0) return 2200 + _op;
    if (strcmp(cmd, "MUL") == 0) return 2300 + _op;
    if (strcmp(cmd, "DIV") == 0) return 2400 + _op;
    if (strcmp(cmd, "MOD") == 0) return 2500 + _op;
    if (strcmp(cmd, "LER") == 0) return 3100 + _op;
    if (strcmp(cmd, "IMP") == 0) return 4100 + _op;
    if (strcmp(cmd, "NOP") == 0) return 5000 + _op;
    if (strcmp(cmd, "DES") == 0) return 5100 + _op;
    if (strcmp(cmd, "DPO") == 0) return 5200 + _op;
    if (strcmp(cmd, "DPZ") == 0) return 5300 + _op;
    if (strcmp(cmd, "DNE") == 0) return 5400 + _op;
    if (strcmp(cmd, "DNZ") == 0) return 5500 + _op;
    if (strcmp(cmd, "DDZ") == 0) return 5600 + _op;
    if (strcmp(cmd, "DZZ") == 0) return 5700 + _op;
    if (strcmp(cmd, "ADE") == 0) return 6100 + _op;
    if (strcmp(cmd, "ADD") == 0) return 6200 + _op;
    if (strcmp(cmd, "PAR") == 0) return 7000 + _op;
    return 0;
}

// Carrega um arquivo .hip para interpretar.
void HIPO_LoadFile(char* path) {
    FILE *source;
    source = fopen(path, "r");
    if (source != NULL) {
        char string[10], cmd[10], op[10]; int m__index = 0;
        while (strcmp(string, "PAR") != 0) {
            strcpy(cmd, ""); strcpy(op, "");
            fscanf(source, "%s", string);
            strcpy(cmd, string);
            if (strcmp(cmd, "FIM") != 0) {
                fscanf(source, "%s", string);
                strcpy(op, string);
            }
            memory[m__index] = HIPO_Encode(cmd, op);
            m__index++;
        }
    }
    fclose(source);
}

// INSTRUÇÕES DO INTERPRETADOR

// Carrega valor do endereço de memória especificado para o acumulador.
void cea(int addr) {
    cache = memory[addr];
}

// Carrega valor do acumulador para o endereço de memória especificado.
void cae(int addr) {
    memory[addr] = cache;
}

// Soma valor do endereço de memória especificado com o cache do processador e armazena o resultado no cache. 
void som(int addr) {
    cache += memory[addr];
}

// Subtrai o conteúdo do endereço de memória especificado do acumulador e armazena o resultado no acumulador.
void sub(int addr) {
    cache -= memory[addr];
}

// Multiplica o conteúdo do endereço de memória especificado com o conteúdo do acumulador e armazena o resultado no acumulador.
void mul(int addr) {
    cache = cache * memory[addr];
}

// Divide o conteúdo do acumulador pelo conteúdo do endereço de memória especificado e armazena o resultado no acumulador.
void _div(int addr) {
    cache = (int)(cache / memory[addr]);
}

// O acumulador recebe o resto da divisão do valor do acumulador pelo valor do endereço de memória especificado.
void mod(int addr) {
    cache = cache % memory[addr];
}

// Lê o teclado e armazena o valor lido no endereço de memória especificado.
void ler(int addr) {
    printf("INPUT: ");
    scanf("%d", &memory[addr]);
}

// Escreve valor do endereço de memória especificado na tela.
void imp(int addr) {
    printf("[M%d]: %d\n", addr, memory[addr]);
}

// Faz nada.
void nop() {

}

// Desvia o API para o endereço de memória especificado.
void des(int addr) {
    _index   = addr - 1;
}

// Se o conteúdo do acumulador for maior que 0, desloca o API para o endereço de memória espeficado.
void dpo(int addr) {
    if (cache > 0) _index = addr - 1;
}

// Se o conteúdo do acumulador for igual ou maior que 0, desloca o API para o endereço de memória espeficado.
void dpz(int addr) {
    if (cache >= 0) _index = addr - 1;
}

// Se o conteúdo do acumulador for menor que 0, desloca o API para o endereço de memória espeficado.
void dne(int addr) {
    if (cache < 0) _index = addr - 1;
}

// Se o conteúdo do acumulador for igual ou menor que 0, desloca o API para o endereço de memória espeficado.
void dnz(int addr) {
    if (cache <= 0) _index = addr - 1;
}

// Se o conteúdo do acumulador for diferente de 0, desloca o API para o endereço de memória espeficado.
void ddz(int addr) {
    if (cache != 0) _index = addr - 1;
}

// Se o conteúdo do acumulador for 0, desloca o API para o endereço de memória espeficado.
void dzz(int addr) {
    if (cache == 0) _index = addr - 1;
}

// Desloca o conteúdo do acumulador uma posição para a esquerda, desprezando o dígito mais significativo.
void ade() {
    cache = cache * 10;
}

// Desloca o conteúdo do acumulador uma posição para a direita, desprezando o dígito menos significativo.
void add() {
    cache = (int)(cache / 10);
}

void par() {
    _index  = -1;
    running = 0;
}

#endif