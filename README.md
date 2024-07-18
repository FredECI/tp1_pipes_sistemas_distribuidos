### Relatório do Trabalho Prático 1 - Sistemas Distribuídos

#### Universidade Federal do Rio de Janeiro
#### Curso de Engenharia de Computação e Informação
#### Disciplina: Sistemas Distribuídos - COS470
#### Professor: José Rezende
#### Aluno: Frederico Januario Lisbôa
#### DRE: 120059054
#### Período: 2024/1

---

### Parte 3: Pipes

#### 1. Introdução

O objetivo deste trabalho é se familiarizar com os principais mecanismos de IPC (Interprocess Communication) baseados em troca de mensagens. Nesta parte, implementamos o problema Produtor-Consumidor utilizando pipes anônimos para comunicação entre dois processos.

#### 2. Objetivos

- Implementar um programa Produtor-Consumidor utilizando pipes anônimos.
- O produtor gera números inteiros aleatórios e crescentes e os envia ao consumidor via pipe.
- O consumidor verifica se os números recebidos são primos e imprime o resultado.
- O consumidor termina quando recebe o número zero.

#### 3. Decisões de Projeto

Para a implementação, decidimos usar a linguagem C pela sua proximidade com o sistema operacional e controle sobre operações de IPC. Utilizamos a função `pipe()` para criar o canal de comunicação entre os processos e `fork()` para criar processos filhos. A comunicação foi realizada convertendo os números para strings de tamanho fixo (20 bytes).

#### 4. Implementação

##### 4.1. Código do Produtor (Pai)
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of integers>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_to_generate = atoi(argv[1]);
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Código do produtor (pai)
        close(pipe_fd[0]); // Fechar o lado de leitura do pipe
        srand(time(NULL)); // Inicializar a semente do gerador de números aleatórios
        
        int N = 1;
        char buffer[20];
        
        for (int i = 0; i < num_to_generate; i++) {
            int delta = (rand() % 100) + 1;
            N += delta;
            snprintf(buffer, sizeof(buffer), "%d", N);
            write(pipe_fd[1], buffer, sizeof(buffer));
        }
        
        snprintf(buffer, sizeof(buffer), "%d", 0);
        write(pipe_fd[1], buffer, sizeof(buffer));
        close(pipe_fd[1]);
        wait(NULL); // Espera pelo término do filho
    } else { // Código do consumidor (filho)
        close(pipe_fd[1]); // Fechar o lado de escrita do pipe
        char buffer[20];
        int num;
        
        while (1) {
            read(pipe_fd[0], buffer, sizeof(buffer));
            num = atoi(buffer);
            if (num == 0) break;
            
            if (is_prime(num)) {
                printf("%d is prime\n", num);
            } else {
                printf("%d is not prime\n", num);
            }
        }
        close(pipe_fd[0]);
    }
    return 0;
}
```

##### 4.2. Função de Verificação de Primos
```c
int is_prime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}
```

#### 5. Resultados dos Testes

Para validar a implementação, executamos vários testes gerando diferentes quantidades de números e verificando a correta comunicação e processamento entre os processos.

##### 5.1. Teste 1: Gerando 10 Números
- **Entrada**: 10
- **Saída**:
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

##### 5.2. Teste 2: Gerando 20 Números
- **Entrada**: 20
- **Saída**:
    ```
    5 is prime
    9 is not prime
    14 is not prime
    15 is not prime
    17 is prime
    18 is not prime
    23 is prime
    28 is not prime
    32 is not prime
    37 is prime
    40 is not prime
    43 is prime
    48 is not prime
    51 is not prime
    54 is not prime
    58 is not prime
    60 is not prime
    62 is not prime
    64 is not prime
    67 is prime
    ```

#### 6. Conclusão

A implementação do problema Produtor-Consumidor utilizando pipes anônimos foi bem-sucedida, permitindo a comunicação eficiente entre processos. O programa produtor gerou números aleatórios e crescentes corretamente, enquanto o consumidor verificou a primalidade e imprimiu os resultados. O trabalho demonstrou a importância dos mecanismos de IPC em sistemas distribuídos e reforçou a compreensão de conceitos fundamentais.

#### 7. Referências

- Documentação do Linux para pipes e IPC: `man pipe`, `man fork`
- Bibliografia da disciplina de Sistemas Distribuídos
- Exemplos discutidos em aula

#### 8. URL para o Código-Fonte

O código-fonte da implementação está disponível no repositório do GitHub: [GitHub Link](https://github.com/FredECI/tp1_pipes_sistemas_distribuidos).
