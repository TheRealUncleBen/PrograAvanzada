#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int tam;
    int prioridad;
    int usado;
    int finalizado;
}tarea;

int terminado(tarea *procesos, int np){
    tarea * aux = procesos;
    for(int i = 0; i< np; i++){
        if(aux->finalizado == 0){
            return 0;
        }
        aux++;
    }
    return 1;
}
int main(){
    printf("Tamaño tarea = %ld\n", sizeof(tarea));
    int np = 3;
    tarea * A = (tarea*) malloc(sizeof(tarea) * 3);
    tarea * aux = A;
    for(int i = 0; i<np; i++){
        aux->finalizado = 1;
        printf("tam de tarea %d: ",i+1);
        scanf("%d", &aux->tam);
        aux ++;
    }
    aux = A;
    aux->finalizado = 0;
    printf("todos acabaron?: %d \n", terminado(A,3));
    for(int i = 0; i<np; i++){
        printf("Valor: %d \n",aux->tam);
        printf("Valor: %d \n",aux->prioridad);
        printf("Valor: %d \n",aux->usado);
        printf("Valor: %d \n",aux->finalizado);
        aux++;
    }
/* 
    for(int i = 0; i<ncpu; i++){
            aux->tam = aux->tam - quantum;
            if(aux->tam < 1){
                aux->finalizado = 1;
            }
            aux ++;
    }
 */
    free(A);
    return 0;
}