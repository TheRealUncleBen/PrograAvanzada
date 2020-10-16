#include <stdio.h>
#include <stdlib.h>
typedef struct{
    void * arreglo;
    size_t tamDato;
    size_t tamArreglo;
}arregloPlus;

int main(){
    /* int * A =(int*) malloc(sizeof(int) * 4);
    int * B = A + 4;
    int i = 0;
    while(B>A){
        printf("%d \n",i);
        i++;
        B--;
    }
    free(A); */
    arregloPlus numeros;
    numeros.tamArreglo = 12;
    numeros.tamDato = sizeof(int);
    numeros.arreglo = (int *) malloc(numeros.tamDato * numeros.tamArreglo);
    void * fin = numeros.arreglo + numeros.tamArreglo;
    int i = 10;

    int * aux = numeros.arreglo;
    int * last = numeros.arreglo + (numeros.tamArreglo);

    printf("\n\n--- Ejercicio #1 ENTEROS ---\n\n");

    printf("\n---> Asignación \n");
    for (; aux < last; ++aux) {
        *aux = rand() % 100 *1.5;
        printf(" assigned %f,    \t ", *aux);
    }
    for (int i = 0; i < 12; i++){
        printf("Num: %d = %d", i, numeros.arreglo);
    }
    
    return 0;
}