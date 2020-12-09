#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int NHILOS = 4;
int N = 1000;

/* Vector de elementos */
int * vector;

/* Vector de sumas parciales */
int * sumas;

int suma()
{
    int total = 0;
    
    int * fin = vector + N;
    
    for (int * aux = vector; aux < fin; ++aux) {
        total += *aux;
    }
    
    /* Tomar el tiempo final */
    time_t t_fin = time(NULL);
    
    
    
    return total;
}

void * suma_paralela(void * tid)
{
    int id = (int *) tid;
    
    int total = 0;
    
    int elementos = N / NHILOS;
    
    int * inicio = vector + (id * elementos);
    int * fin;
    
    if (id == NHILOS-1) {
        fin = vector + N;
    }
    else {
        fin = inicio + elementos;
    }
    
    for (int * aux = inicio; aux < fin; ++aux) {
        total += *aux;
    }
    
    *(sumas + id) = total;
    
    pthread_exit(NULL);
}


int main(int argc, const char * argv[]) {
    clock_t t;
    /* Leer argumentos */
    if (argc == 3) {
        N = atoi(argv[1]);
        NHILOS = atoi(argv[2]);
    }
        
    /* Reservar memoria para el vector */
    vector = (int *) malloc(sizeof(int) * N);
    
    /* Inicializar el vector */
    int * fin = vector + N;
    for (int * aux = vector; aux < fin; ++aux) {
        *aux = 1;
    }
    
    /* Reservar memoria para el vector */
    sumas = (int *) malloc(sizeof(int) * NHILOS);
    
    /* Crear los hilos de ejecución */
    
    // Tiempo inicio región paralela
    t = clock();
    pthread_t * hilos = (pthread_t * ) malloc(sizeof(pthread_t) * NHILOS);
    
    for (int i = 0; i < NHILOS; ++i) {
        pthread_create(hilos+i, NULL, suma_paralela, (int *) i);
    }
    
    /* Esperar a que terminen los hilos de ejecución */
    for (int i = 0; i < NHILOS; ++i) {
        pthread_join(*(hilos+i), NULL);
    }
    
    /* Realizar la reducción */
    int total = 0;
    
    fin = sumas + NHILOS;
    for (int * aux = sumas; aux < fin; ++aux) {
        total += *aux;
    }
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    // Tiempo final región paralela
    
    /* Obtener la suma */
    printf("La suma total paralela es = %d y tomo %f tiempo\n", total, time_taken);
    
    /* Obtener la suma */
    t = clock();
    //time_t t_inicio = time(NULL);
    total = suma();
    //time_t t_final = time(NULL);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("La suma total secuencial es = %d y demoró %f segundos\n", suma(), time_taken );

    /* Liberar la memoria */
    free(vector);
    free(sumas);
    free(hilos);
    
    return 0;
}