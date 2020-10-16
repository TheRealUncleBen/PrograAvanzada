
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char * argv[]) {

    pid_t pid;
    int estado;
    int n = 10;
    int * arre =(int*) malloc(n * sizeof(int));
    

    printf("---Indique el intervalo a evaluar---\n");
    printf("Intervalo bajo");
    scanf("%d", interBajo);
    printf("Intervalo alto");
    scanf("%d", interAlto);
    pid = fork();
    
    if(pid == -1){
        printf("Error al crear el proceso hijo \n");
    }
    else if(pid == 0){

    }

    /* De aquí en adelante lo ejecutan los dos procesos */
    if (pid == -1)
    {
        printf("Error al crear el proceso hijo \n");
    }
    else if (pid == 0)
    {
        // Estamos en el hijo
        printf("Estamos en el proceso hijo con PID = %d y su padre es PPID = %d \n", \
               getpid(), getppid());
        exit(3);
    }
    else {
        // Estamos en el padre
        printf("Estamos en el proceso padre con PID = %d y su padre es PPID = %d \n", \
               getpid(), getppid());
        
        // Poner al padre a esperar que el hijo termine
        if (waitpid(pid, &estado, 0) != -1)
        {
            if (WIFEXITED(estado))
                printf("Ya terminó el hijo con PID %d con valor de retorno %d \n", pid, WEXITSTATUS(estado));
        }
        
        printf("Después del wait\n");

    }
    
    /* Lo van a imprimir los dos procesos */
    printf("Estamos en el proceso con PID = %d y su padre es PPID = %d \n", \
                   getpid(), getppid());
    free(arre);
    return 0;
}