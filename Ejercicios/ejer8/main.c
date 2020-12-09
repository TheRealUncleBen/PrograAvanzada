//compilar con -pthread
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define TAMFILA 50
#define NCAJEROS 8
//status 0=no disponible 1=disponible
typedef struct{
    int clienteId;
    int tipoCliente;
    int status;
}cliente;

cliente filaGeneral[TAMFILA];
cliente filaEmpresarial[TAMFILA];
int clientesEsperaG;
int clientesEsperaE;
int frenteG;
int frenteE;
int ids;
int stop;
int ocupados;

pthread_mutex_t mutexIds = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexFilaG = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexFilaE = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t produceClienteG = PTHREAD_COND_INITIALIZER;
pthread_cond_t produceClienteE = PTHREAD_COND_INITIALIZER;
pthread_cond_t consume_1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t consume_2 = PTHREAD_COND_INITIALIZER;

void * generaCliente(void *);
void * gerenteThr(void *);
void * cajeroG(void *);
void * cajeroE(void *);

int main(int argc, const char * argv[]){
    ids = 0;
    frenteG = 0;
    frenteE = 0;
    ocupados = 0;
    stop = 0;
    int geren,cG,cE;
    pthread_t gerente, generaG, generaE;
    int * temp =(int *) malloc(sizeof(int));
    //genera hilos de creadores
    *temp = 0;
    cG = pthread_create(&generaG, NULL, generaCliente,(void *) temp);
    if (cG){
        printf("Error al iniciar creador de generales\n");
    }
    int * temp2 =(int *) malloc(sizeof(int));
    *temp2 = 1;
    cE = pthread_create(&generaE, NULL, generaCliente,(void *) temp2);
    if (cE){
        printf("Error al iniciar creador de Empresariales\n");
    }
    //genera hilos de cajeros
    
    pthread_t cajeros[NCAJEROS];
    int threads[NCAJEROS];
    int chemps[8];
    for(int i = 0; i < NCAJEROS; i++){
        chemps[i] = i;
        if(i < 5)
            threads[i] = pthread_create(&cajeros[i], NULL, cajeroG,(void*) (chemps + i));
        else if(i>=5 && i<8){
            threads[i] = pthread_create(&cajeros[i], NULL, cajeroE,(void*) (chemps + i));
        }
        if(threads[i]){
            printf("Error al crear el cajero %d\n", i);
        }
    }
    free(temp);
    free(temp2);
    /* Esperar a que los hilos terminen */
    pthread_join(generaE, NULL);
    pthread_join(generaG, NULL);
    for(int i =0; i< NCAJEROS; i++){
        pthread_join(cajeros[i],NULL);
    }
    return 0;
}
void * cajeroG(void * temp){
    int * idCajero = (int *) temp;
    int descanso = 0;
    int cajerin=0;
    while(stop != 2){
        usleep(rand() % 50);
        cliente usuario;
        pthread_mutex_lock(&mutexFilaG);
        usuario = filaGeneral[frenteG];
        if(usuario.status == 1){
            ocupados++;
            filaGeneral[frenteG].status = 0;
            frenteG = (frenteG +1) % TAMFILA;
            descanso++;
            clientesEsperaG--;
            if(clientesEsperaG == 0){
                pthread_cond_signal(&produceClienteG);
            }
            printf("-Cajero %d atiende a cliente %d de tipo General*\n", *idCajero,usuario.clienteId);
            //cajerin = (cajerin +1)%5;
        }else{
            pthread_cond_wait(&consume_1, &mutexFilaG);
        }
        pthread_mutex_unlock(&mutexFilaG);
        sleep((rand() % 2) + 3); 
        //sleep(1);
        ocupados--;
        if(descanso >= 5){
            descanso = 0;
            printf("Se suspende operacion\n");
            sleep(3);
        }
    }
    pthread_exit(NULL);
}
void * cajeroE(void * temp){
    int * idCajero = (int *) temp;
    int descanso = 0;
    int cajerin = 0;
    while(stop != 2){
        usleep(rand() % 50);
        cliente usuario;
        pthread_mutex_lock(&mutexFilaE);
        usuario = filaEmpresarial[frenteE];
        if(usuario.status = 1){
            filaEmpresarial[frenteE].status = 0;
            frenteE = (frenteE +1) % TAMFILA;
            descanso++;
            clientesEsperaE--;
            if(clientesEsperaE == 0){
                pthread_cond_signal(&produceClienteE);
            }
        }else{
            if(ocupados <= 4){
                pthread_mutex_lock(&mutexFilaG);
                usuario = filaGeneral[frenteG];
                if(usuario.status == 1){
                    filaGeneral[frenteG].status = 0;
                    frenteG = (frenteG +1) % TAMFILA;
                    descanso++;
                    clientesEsperaG--;
                    if(clientesEsperaG == 0){
                        pthread_cond_signal(&produceClienteG);
                    }
                    pthread_mutex_unlock(&mutexFilaG);
                }else{
                    pthread_mutex_unlock(&mutexFilaG);
                    pthread_cond_wait(&consume_2, &mutexFilaE);
                }
            }
            else{
                pthread_cond_wait(&consume_2, &mutexFilaE);
            }
        }
        pthread_mutex_unlock(&mutexFilaE);
        if(usuario.status == 1){
            printf("-Cajero %d atiende a cliente %d de tipo ", *idCajero,usuario.clienteId);
            //cajerin = (cajerin + 1) % 3 + 6;
            if(usuario.tipoCliente == 1){
                printf("Empresarial ******\n");
            }else{
                printf("General******\n");
            }
        }
        if(descanso >= 5){
            descanso = 0;
            printf("Se suspenden operaciones\n");
            sleep(3);
        }
    }
    pthread_exit(NULL);
}
    //generar clientes
void * generaCliente(void * temp){
    //si es tipo 0 es general y 1 es empresarial
    int *tipo = (int*) temp;
    int i = 0;
    if(*tipo == 0){
        //Maneja creación de generales
        printf("Inicia creación de generador de Generales\n");
        while(i<100){
            usleep(rand() % 50);
            pthread_mutex_lock(&mutexFilaG);
            if(clientesEsperaG < TAMFILA){
                cliente new;
                
                pthread_mutex_lock(&mutexIds);
                new.clienteId = ids;
                ids++;
                pthread_mutex_unlock(&mutexIds);
                new.status = 1;
                new.tipoCliente = 0;
                filaGeneral[i%TAMFILA] = new;
                clientesEsperaG++;
                i++;
                printf("Llegó cliente con id:%d y de tipo General\n", new.clienteId);
                if(clientesEsperaG == TAMFILA){
                    pthread_cond_signal(&consume_1);
                }
                sleep((rand() % 17)+5); 
                //sleep(2);
            }else{
                //en caso de que esté llena la fila
                pthread_cond_wait(&produceClienteG, &mutexFilaG);
            }
            pthread_mutex_unlock(&mutexFilaG);
        }
    }else{
        //Maneja creación de empresariales
        printf("Inicia creación de generador de Empresariales\n");
        while(i<50){
            usleep(rand() % 50);
            pthread_mutex_lock(&mutexFilaE);
            if(clientesEsperaE < TAMFILA){
                cliente new;
                pthread_mutex_lock(&mutexIds);
                new.clienteId = ids;
                ids++;
                pthread_mutex_unlock(&mutexIds);
                new.status = 1;
                new.tipoCliente = 1;
                filaEmpresarial[i%TAMFILA] = new;
                clientesEsperaE++;
                i++;
                printf("Llegó cliente con id:%d y de tipo Empresarial\n", new.clienteId);
                if(clientesEsperaG == TAMFILA){
                    pthread_cond_signal(&consume_2);
                }
                sleep((rand() % 25)+9);
                //sleep(5);
            }else{
                //en caso de que esté llena la fila
                pthread_cond_wait(&produceClienteE, &mutexFilaE);
            }
            pthread_mutex_unlock(&mutexFilaE);
        }
    }
    stop ++;
    pthread_exit(NULL);
}