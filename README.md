# HIPO

O HIPO é um computador hipotético criado para ensinar computação básica à leigos em tecnologia. O sistema funciona emulando a maneira como um computador real funciona, com memória virtual de 100 bytes, e usando uma linguagem semelhante ao Assembler.

## Biblioteca

O arquivo HIPO.h é uma biblioteca C para usar o HIPO em um código fonte. Para usar-lá, basta baixar o repositório e incluir o diretório raiz no IncludePath do compilador:

```
$ gcc [INPUT FILES] -o [OUTPUT FILE] -I"[IncludePath]"
```

## Interpretador

A versão mais útil do projeto é o interpretador, este pode ser usado para interpretar o código HIPO contido em arquivos .hip. Para usar-lo, basta compilar o arquivo hipoc.c

```
$ gcc hipoc.c -o hipoc -I"./"
```

Logo em seguida, executar o arquivo de saída, onde o primeiro parâmetro é o caminho do arquivo .hip no seu computador a partir do diretório onde o executável está.

```
$ ./hipoc [.HIP FILE]
```

## Começando

### Estrutura

O interpetrador inicia um array de inteiros com 100 posições para emular a memória de um computador real. Cada endereço de memória armazena um número de -9999 a +9999 podendo este conteúdo ser uma instrução ou um dado armazenado. Em cada endereço temos a estrutura de
```
+IIEE
```
Onde II representa o código de uma instrução e EE representa o endereço de memória como parâmetro para a instrução II.
O interpretador tem um cache de processamento de um byte. 
A estrutura da memória pode ser representada por:
```
ENDEREÇO    CONTEÚDO    COMANDO
00          +3180       LER 80
01          +4180       IMP 80
02          +7000       PAR
03          +0000
...
97          +0000
98          +0000
99          +0000
```
O interpretador possui um API - Apontador de instrções - que executa o program de maneira linear.

### Sintaxe

O HIPO usa uma sintaxe parecida com o Assembler, porém menos complexa e mais intuitiva para o usuário. Todos os comandos são abreviações da língua portuguesa.
A tabela abaixo fornece uma relação dos comandos mais usados do interpretador:

```
NOME    CÓDIGO  DESCRIÇÃO
CEA     11      Copia o conteúdo do endereço de memória especificado para o acumulador.
CAE     12      Copia o conteúdo do acumulador para o endereço de memória especificado.
SOM     21      Soma o conteúdo do acumulador com o do endereço de memória especificado.
SUB     22      Subtrae o conteúdo do acumulador com o do endereço de memória especificado.
MUL     23      Multiplica o conteúdo do acumulador com o do endereço de memória especificado.
DIV     24      Divide o conteúdo do acumulador com o do endereço de memória especificado.
```

O código deve ser redigido em letras maiúsculas com um codinome de três caracteres e um número de 0 a 99 que especificam o parâmetro para a instrução. Abaixo temos o exemplo de um programa que armazena o número lido do teclado em um endereço de memória e mostra que número o usuário digitou:

```
LER 80
IMP 80
PAR
```

Todo código .hip deve terminar com o comando PAR para finalizar a execução do programa.

### Informações

Mais informações podem ser encontradas em: <a href="https://www.ime.usp.br/~jstern/software/hipo/Hipo.pdf">HIPO IME</a>