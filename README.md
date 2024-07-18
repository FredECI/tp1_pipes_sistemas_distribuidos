# Produtor-Consumidor com Pipes

Este repositório contém a implementação do problema Produtor-Consumidor utilizando pipes anônimos para comunicação entre processos em C. Esta implementação faz parte do Trabalho Prático 1 da disciplina de Sistemas Distribuídos da UFRJ.

## Descrição

O programa é dividido em dois processos: o produtor e o consumidor. O produtor gera números inteiros aleatórios e crescentes e os envia para o consumidor via pipe. O consumidor recebe os números, verifica se são primos, e imprime o resultado. A comunicação entre os processos é feita utilizando pipes anônimos.

## Estrutura do Projeto

- `produtor_consumidor.c`: Código-fonte do programa Produtor-Consumidor.

## Compilação e Execução

### Pré-requisitos

- Compilador GCC

### Compilação

Para compilar o código, execute o seguinte comando no terminal:

```bash
gcc -o produtor_consumidor produtor_consumidor.c
```

### Execução

Para executar o programa, use o comando abaixo, substituindo `<número_de_inteiros>` pelo número de inteiros que deseja gerar:

```bash
./produtor_consumidor <número_de_inteiros>
```

Exemplo:

```bash
./produtor_consumidor 10
```

## Funcionamento

1. O produtor gera números inteiros aleatórios e crescentes. A fórmula utilizada é \(N_i = N_{i-1} + \Delta\), onde \(N_0 = 1\) e \(\Delta\) é um valor aleatório entre 1 e 100.
2. Os números gerados são enviados ao consumidor via pipe.
3. O consumidor recebe os números, verifica se são primos, e imprime o resultado no terminal.
4. O programa termina quando o consumidor recebe o número `0`.

## Estrutura do Código

- O código cria um pipe e utiliza `fork()` para criar dois processos.
- O processo pai atua como produtor e o processo filho atua como consumidor.
- A comunicação entre os processos é feita através do pipe.
- Os números são convertidos para strings de tamanho fixo (20 bytes) para a comunicação.

## Exemplo de Saída

Para a entrada `./produtor_consumidor 10`, a saída pode ser:

```
5 is prime
8 is not prime
12 is not prime
15 is not prime
19 is prime
23 is prime
25 is not prime
28 is not prime
32 is not prime
35 is not prime
```

## Autor

Este projeto foi desenvolvido por Frederico Januario Lisbôa como parte do Trabalho Prático 1 da disciplina de Sistemas Distribuídos na UFRJ.
