//Creado por David Benjamin Ruiz Salazar 29/10/2020
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define N 4
#define PS 15

int controlPesos [N];
pthread_mutex_t * tiendas;
pthread_mutex_t * pesos;
pthread_cond_t * condTiendas;

//void comprarEnTienda(int id);
void * robot(void *arg);

int main(){
    int pi;
    int numRobots = 0;

    tiendas = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t) * N);
    pesos = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t) * N);
    condTiendas = (pthread_cond_t*) malloc(sizeof(pthread_cond_t) * N);

    printf("Ingrese la cantidad de ordenes a procesar\n");
    scanf("%d",&numRobots);
    pthread_t robotos[numRobots];
    //creación de robots de acuerdo a la cantidad de ordenes 
    for(int i = 0; i< numRobots; i++){
        pthread_create(&robotos[i], NULL, robot,(void *) (intptr_t) i); 
    }
    for(int i = 0; i < numRobots; i++){
        pthread_join(robotos[i],NULL);
        printf("**Se liberó al robot %d**\n", i+1);
    }

    /* free(tiendas);
    free(pesos);
    free(condTiendas); */
    return 0;
}
void * robot(void *arg){
    int idRobot = (intptr_t) arg;
    int pi = (rand() % 9) + 1;
    int tiendaActual = 0;
    pthread_mutex_t * auxtienda = tiendas;
    pthread_mutex_t * auxPesos = pesos;
    pthread_cond_t * auxCond = condTiendas;

    pthread_mutex_t * finTiendas = tiendas + N;
    //while recorre los mutex de todas las tiendas 
    while(auxtienda < finTiendas){
        printf("Robot %d quiere pasar a tienda %d\n", idRobot+1,tiendaActual+1);
        pthread_mutex_lock(&(*auxtienda));
        pthread_mutex_lock(&(*auxPesos));
        if(pi + controlPesos[tiendaActual] < PS){
            controlPesos[tiendaActual] += pi;
            pthread_mutex_unlock(&(*auxPesos));
            pthread_mutex_unlock(&(*auxtienda));
            //random para determinar si compra en tienda actual
            if(rand() % 2){
                //comprarEnTienda(idRobot);
                printf("Robot %d ha ingresado a la tienda... Comprando\n", idRobot+1);
                sleep(1);
                printf("Robot %d ha terminado de comprar en tienda\n", idRobot+1);
            }else{
                printf("Robot %d no ha comprado en tienda %d... Pasando a siguiente\n", idRobot+1, tiendaActual+1);
            }
            //pthread_mutex_lock(&(*auxtienda));
            pthread_mutex_lock(&(*auxPesos));
            controlPesos[tiendaActual] -= pi;
            pthread_mutex_unlock(&(*auxPesos));
            //pthread_mutex_unlock(&(*auxtienda));

            pthread_cond_signal(&(*auxCond));

            if(tiendaActual < N){
                auxCond ++;
                auxPesos ++;
                auxtienda ++;
                tiendaActual++;
            }
        }else{
            printf("Robot %d no cabe en tienda %d... Esperando\n", idRobot+1,tiendaActual+1);
            pthread_mutex_unlock(&(*auxPesos));
            pthread_cond_wait(&(*auxCond),&(*auxtienda));
            printf("++Se abrió espacio en tienda %d\n",tiendaActual+1);
            pthread_mutex_unlock(&(*auxtienda));
        }
        //pthread_mutex_unlock(&auxtienda);
    }
    printf("--Robot %d ha terminado sus compras--\n", idRobot+1);
    /* for(auxtienda = tiendas; auxtienda < finTiendas; auxtienda ++){

    } */
}
/* void comprarEnTienda(int id){
    //sleep(rand() % 2);
} */