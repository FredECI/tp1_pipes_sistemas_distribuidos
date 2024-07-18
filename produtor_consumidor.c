#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

// Função para verificar se um número é primo
int is_prime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}

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
