#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int global;

void gestor1(int sid)
{
    printf("Holaaaa\n");
    global = 0;
}
void manejoDir(){
    struct stat buffer;
    int existe = stat("datos",&buffer);
    if(existe == 0)
        system("rm -r datos");
    system("mkdir datos");
}

int main(int argc, const char * argv[])
{
    sigset_t conjunto, pendientes;
    int i;
    int n = 3;
    int t = 5;
    char * buffer = (char *) malloc(sizeof(int) * 9);
    FILE *archivo;
    //se borran los contenidos de directorio datos o se crea
    manejoDir();
    sigemptyset(&conjunto);

    sigaddset(&conjunto, SIGINT);

    sigaddset(&conjunto, SIGTSTP);

    sigprocmask(SIG_BLOCK, &conjunto, NULL);

    signal(SIGALRM, gestor1);

    for(int i =0; i<n; i++){
        global=1;
        sprintf(buffer,"datos/a%d",i);
        archivo = fopen(buffer,"w");
        alarm(t);
        while(global){
            fputc('x',archivo);
        }
        sigpending(&pendientes);   
        if (sigismember(&pendientes, SIGINT))
            printf("He recibido un Ctrl+C y no lo procesé por estar bloqueada. \n");
        if (sigismember(&pendientes, SIGTSTP))
            printf("He recibido un Ctrl+Z y no lo procesé por estar bloqueada. \n");
        fclose(archivo);
    }

/* 
    while(global == 0)
    {
        printf("Las señales SIGINT y SIGTSTP están bloqueadas ... \n");
        sleep(1);

        if (sigismember(&pendientes, SIGINT))
            printf("He recibido un Ctrl+C y no lo procesé por estar bloqueada. \n");
        if (sigismember(&pendientes, SIGTSTP))
            printf("He recibido un Ctrl+Z y no lo procesé por estar bloqueada. \n");

    } */

    sigprocmask(SIG_UNBLOCK, &conjunto, NULL);

    printf("Se desbloquearon las señales y se procesaron");

    free(buffer);
    while(1);

    return 0;
}