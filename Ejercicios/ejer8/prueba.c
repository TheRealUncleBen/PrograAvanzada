#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void * gerente(void *);

int main(){
    pthread_t hilo1, hilo2;
    //int *nums = (int*) malloc(8 * sizeof(int));
    /* int *aux = nums;
    for(int i=0; i< 8; i++){
        *aux = i;
        aux++;
    } */
    int * num =(int *)malloc(sizeof(int));
    *num = 7;
    pthread_create(&hilo1, NULL,gerente,(void*)num);
    //int *nums = (int*) malloc(8 * sizeof(int));
    /* aux = nums;
    for(int i=0;i< 8; i++){
        *aux = i;
        aux++;
    }
    pthread_create(&hilo2, NULL,gerente,(void*)nums); */
    pthread_join(hilo1, NULL);
    //pthread_join(hilo2, NULL);
    free(num);
    return 0;
}
void * gerente(void * nums){
    int *valores = (int*) nums;
    printf("%d \n", *valores);
   /*  int *aux = valores;
    for(int i = 0; i< 8; i++){
        printf("%d \n", *aux);
        if(i<7)
            aux++;
    } */
    pthread_exit(NULL);
}