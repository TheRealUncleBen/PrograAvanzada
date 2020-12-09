#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t * prro;

void * prub(void * arg){
    pthread_mutex_t * auxprro = prro;
    int id = (intptr_t) arg;
    for(int i = 0; i< 5; i++){
        pthread_mutex_lock(&auxprro);
        printf("Yo meroles paso %d al %d\n", id, i);
        pthread_mutex_unlock(&auxprro);
        auxprro ++;
    }
}

int main(){
    prro = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * 5);
    pthread_mutex_t * fin = prro + 5;
    pthread_t threadsmama[5];
    int id = 0;
    for(pthread_mutex_t * aux = prro; prro < fin; prro++){
        pthread_create(&(threadsmama[id]), NULL, prub, (void *) (intptr_t) id);
        id++;
    }
    id= 0;
    for(pthread_mutex_t * aux = prro; prro < fin; prro++){
        pthread_join(threadsmama[id], NULL);
        id++;
    }
    /* int cond = 0;
    while(cond < 4){
        if(rand() % 2){
            printf("Entra\n");
            cond ++;
        }else{
            printf("no entró\n");
        }
        
    } */
    return 0;
}