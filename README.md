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

O HIPO usa uma sintaxe parecida com o Assembler, porém menos complexa e mais intuitiva para o usuário. Todos os comandos são abreviações da língua portuguesa.


Mais informações podem ser encontradas em: <a href="https://www.ime.usp.br/~jstern/software/hipo/Hipo.pdf">HIPO IME</a>