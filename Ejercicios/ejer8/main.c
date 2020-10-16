#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define BSIZE 10
#define NCAJEROS 8

int elementos[BSIZE];
typedef struct{
    int tipo;
    int tiempo;
} cliente;

int in = 0;
int out = 0;
int 
int total = 0;


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t consume_t = PTHREAD_COND_INITIALIZER;
pthread_cond_t produce_t = PTHREAD_COND_INITIALIZER;

void * cajeroG(int);
void * cajeroE(int);
void * gerente(pthread_t[]);

int main(int argc, const char * argv[]){
    int threads[NCAJEROS];
    int gerente;
    pthread_t cajeros[NCAJEROS];
    pthread_t gerente;

    for(int i = 0; i < NCAJEROS, i++){
        if(i < 5)
            threads[i] = pthread_create(&cajeros[i], NULL, cajeroG, i);
        else
            threads[i] = pthread_create(&cajeros[i], NULL, cajeroE, i);
        if(threads[i]){
            printf("Error al crear el cajero %d\n", i);
            i--;
        }
    }

    gerente = pthread_create(&gerente, NULL, gerente, &cajeros);
    if (gerente){
        printf("Error al crear el gerente\n");
    }

    //generar clientes
    int generales = 100;
    int empresariales = 50;
    for(int i=0; i < 150; i++){
        if(rand() % 2 == 0){
            //general
            rand() %
        }else{
            //empresarial
        }
    }

    /* Esperar a que los hilos terminen */
    pthread_join(gerente, NULL);
    for(int i =0; i<NCAJEROS; i++){
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}

void * gerente(pthread cajeros[8]){
    int i = 0;
    while (i < N) {
        /* Asumir que trabajan a diferentes velocidades */
        usleep(rand() % 500);
        
        pthread_mutex_lock(&mutex);
        
        if (total < BSIZE) {
            
            /* Produce un elemento */
            
            elementos[in] = i;
            
            printf(" +++ Se produjo el elemento %d\n", elementos[in]);
            
            ++i;
            
            ++in;
            in %= BSIZE;
            ++total;
            
            if (total == 1) {
                pthread_cond_signal(&consume_t);
            }
        }
        else {
            /* El buffer está lleno, se va a dormir */
            
            printf("zzzzz El productor se va a dormir \n");
            pthread_cond_wait(&produce_t, &mutex);
            printf("uuuuu El productor se despertó \n");
        }
        
        pthread_mutex_unlock(&mutex);
   
    }
    
    pthread_exit(NULL);
}

void * cajeroE(int espacio){
    int i = 0;
    
    while (i < N) {
        
        /* Asumir que trabajan a diferentes velocidades */
        
        usleep(rand() % 500);
        
        pthread_mutex_lock(&mutex);
        
        if (total > 0)
        {
            /* Consume un elemento */
            
            printf(" --- Se consumió el elemento %d\n", elementos[out]);
            
            ++i;
            ++out;
            out %= BSIZE;
            --total;
            
            if (total == BSIZE - 1) {
                pthread_cond_signal(&produce_t);
            }
            
        }
        else {
            /* El buffer está vacío, se va a dormir */
            printf("ZZZZZ El consumidor se va a dormir \n");
            pthread_cond_wait(&consume_t, &mutex);
            printf("UUUUU El consumidor se despertó \n");
        }
        
        pthread_mutex_unlock(&mutex);
 
    }
    
    pthread_exit(NULL);
}

void * cajeroG(int espacio){
    int i = 0;
    
    while (i < N) {
        
        /* Asumir que trabajan a diferentes velocidades */
        
        usleep(rand() % 500);
        
        pthread_mutex_lock(&mutex);
        
        if (total > 0)
        {
            /* Consume un elemento */
            
            printf(" --- Se consumió el elemento %d\n", elementos[out]);
            
            ++i;
            ++out;
            out %= BSIZE;
            --total;
            
            if (total == BSIZE - 1) {
                pthread_cond_signal(&produce_t);
            }
            
        }
        else {
            /* El buffer está vacío, se va a dormir */
            printf("ZZZZZ El consumidor se va a dormir \n");
            pthread_cond_wait(&consume_t, &mutex);
            printf("UUUUU El consumidor se despertó \n");
        }
        
        pthread_mutex_unlock(&mutex);
 
    }
    
    pthread_exit(NULL);
}