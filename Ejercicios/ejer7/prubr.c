#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>

//*Tipos de funciones
void buscarDatos();
void gestor(int);

//* Variables Globales
int grabar;
//!---------------Main---------------
int fsize(FILE*);
int main(int argc, char const *argv[]){
    if (argc != 3) {
            printf("El orden para ejecutarlo es pasando los argumentos:\n");
            printf("-n : Numero de archivos a crear\n");
            printf("-t : Segundos del temporizador\n");
            exit(-1);
        }
    int n = atoi(argv[1]);
    int t = atoi(argv[2]);

    sigset_t lasDos;
    sigemptyset(&lasDos);
    sigaddset(&lasDos, SIGALRM);

//?-------------------------------------------------------------------------------
//?-------------------------Control de señales Para el padre----------------------
//?-------------------------------------------------------------------------------
    if (signal(SIGALRM, gestor) == SIG_ERR){
        printf("ERROR: No se pudo llamar al manejador\n");
    }
//?-------------------------------------------------------------------------------
//?---------------------------FIN CONTROL DE SEÑALES------------------------------
//?-------------------------------------------------------------------------------

    printf("Numero de archivos a crear: %d\n", n);
    printf("Tiempo de temporizador t: %d\n", t);
    buscarDatos();

    FILE *fp;
    int len = 10;
    char* buffer = (char*) malloc(len * sizeof(char));
    for(int i=0; i<n; i++){
        grabar=1;
        
        snprintf(buffer, len, "datos/a%d", i); // Nombre del archivo
		fp = fopen(buffer, "w+");
        
        int a=0;
        int r=0;
        alarm(t);
        while(grabar==1){
            fputc('x', fp);
            a++;
            r=a;
        }
        r=fsize(fp)/1000;//-De esta manera lo escribimos en KB por que cada X es un byte
        printf("Tamaño de a%d: r: %d Kb \n",i,r); //-Para el tamaño lo que estoy haciendo es contar cuantos x se escribieron en este caso a++

    }
    free(buffer);
    return 0;
}

void gestor(int s){
	if (s == SIGALRM){
        grabar=0;
    }
}

void buscarDatos(){
	DIR* dir = opendir("datos");
	if (dir){
		system("rm -R datos");
        system("mkdir datos");
		closedir(dir);
	}
    else if (ENOENT == errno){
	    system("mkdir datos");
    }
}

int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}