#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int Male_in = 0;
int Fem_in = 0;
int menLine = 0;
int womLine = 0;
int capacity = 4;
int Total;
int MaleNum;
int FemaleNum;
pthread_mutex_t Woman;
pthread_mutex_t Man;
pthread_mutex_t Door;
pthread_mutex_t CapLock;
pthread_cond_t ManCond;
pthread_cond_t WoManCond;
pthread_cond_t DoorCond;

void male();
void female();
void *hombre_sale(void *arg);
void *mujer_sale(void *arg);
void *hombre_quiere_entrar(void *arg);
void *mujer_quiere_entrar(void *arg);

int main(void)
{
    printf("Enter the Number of Males: ");
    scanf("%d", &MaleNum);
    printf("Enter the Number of Females: ");
    scanf("%d", &FemaleNum);
    
    Total = MaleNum + FemaleNum;
    pthread_t Person[Total];
    for (int i = 0; i < MaleNum; i++){
        pthread_create(&Person[i], NULL, hombre_quiere_entrar, NULL);
    }
    for (int i = Total - FemaleNum; i < Total; i++){
        pthread_create(&Person[i], NULL, mujer_quiere_entrar, NULL);
    }
    
    for (int i = 0; i < Total; i++){
        pthread_join(Person[i], NULL);
    }
    /* printf("******* Total Women: %d  \n ******** Total Men: %d  \n", womLine , menLine); */
    return 0;
}

void *hombre_quiere_entrar(void *arg){
    sleep(2);
    male();
    sleep(1);
    pthread_t Out;
    
    pthread_create(&Out, NULL, hombre_sale, NULL);
    pthread_join(Out, NULL);
    
    
    return NULL;
}

void *mujer_quiere_entrar(void *arg){    
    female();
    sleep(1);
    pthread_t Out;

    pthread_create(&Out, NULL,  mujer_sale, NULL);
    pthread_join(Out, NULL);
    
    return NULL;
}

void male(){
    pthread_mutex_lock(&Door);
    if(Fem_in > 0){
        menLine++;
        printf("Man wants to get in\n");
        pthread_cond_wait(&DoorCond, &Door);
        pthread_mutex_lock(&Man);
        menLine--;
    }else{
        pthread_mutex_lock(&Man);
    }
    pthread_mutex_lock(&CapLock);
    capacity --;
    Male_in++;
    //printf("\n Available  %d\n", capacity);
    printf("Man Entered! men inside: %d\n", Male_in);

    if (menLine > 0 && capacity >0){
        pthread_mutex_unlock(&CapLock);
        pthread_mutex_unlock(&Man);
        pthread_mutex_unlock(&Door);
    }else if(menLine > 0 && capacity == 0){
        pthread_mutex_unlock(&CapLock);
        pthread_mutex_unlock(&Door);
    }else if(menLine == 0){
        pthread_mutex_unlock(&CapLock);
        pthread_mutex_unlock(&Man);
        pthread_mutex_unlock(&Door);
    }
    return;
}

void female(){
    pthread_mutex_lock(&Door);
    if(Male_in > 0){
        womLine++;
        printf("Woman wants to get in\n");
        pthread_cond_wait(&DoorCond, &Door);
        pthread_mutex_lock(&Woman);
        womLine--;
    }else{
        pthread_mutex_lock(&Woman);
    }
    pthread_mutex_lock(&CapLock);
    capacity --;
    Fem_in++;
    //printf("\n Available  %d\n", capacity);
    printf("        Woman Entered! Fem_in inside: %d\n", Fem_in);

    if ( womLine > 0 && capacity >0){
        pthread_mutex_unlock(&CapLock);
        pthread_mutex_unlock(&Woman);
        pthread_mutex_unlock(&Door);
    }else if(womLine > 0 && capacity == 0){
        pthread_mutex_unlock(&CapLock);
        pthread_mutex_unlock(&Door);
    }else if(womLine == 0){
        pthread_mutex_unlock(&CapLock);
        pthread_mutex_unlock(&Woman);
        pthread_mutex_unlock(&Door);
    }
    return;
}

void *hombre_sale(void *arg){
    pthread_mutex_lock(&Door);
    Male_in--;
    printf("Man Left! Remaining men: %d\n", Male_in);
    pthread_mutex_lock(&CapLock);
    capacity ++;
    if(capacity == 4){    
        pthread_mutex_unlock(&CapLock);
        printf("\n****  Empty *** \n ");
        pthread_cond_signal(&DoorCond);
    }else{
        //printf("\n %d spots available *** Only Men\n", capacity);
        printf("\n*** Men inside **\n");
        pthread_mutex_unlock(&CapLock);
        pthread_mutex_unlock(&Man);
    }
    pthread_mutex_unlock(&Door);
    return NULL;
}

void *mujer_sale(void *arg){
    pthread_mutex_lock(&Door);
    Fem_in--;
    printf("\t Woman Left!  Remaining Women : %d\n", Fem_in);
    pthread_mutex_lock(&CapLock);
    capacity ++;
    if(capacity == 4){    
        pthread_mutex_unlock(&CapLock);
        printf("\n****  Empty *** \n ");
        pthread_cond_signal(&DoorCond);
    }else{
        //printf("\n %d spots available *** Only Women\n", capacity);
        printf("\n*** Women inside **\n");
        pthread_mutex_unlock(&CapLock);
        pthread_mutex_unlock(&Woman);
    }
    pthread_mutex_unlock(&Door);
    return NULL;
}