#include <stdio.h>
#include <stdlib.h>


typedef struct{
    char *titulo;
    int paginas;
}libro;

typedef struct{
    void * arreglo;
    size_t tamDato;
    size_t tamArreglo;
}arregloPlus;

//definicion de tipos de datos
typedef void (*t_impresor)(void *);
typedef void (*t_iterador)(arregloPlus *, t_impresor *);

//tipos de iteradores
void forward(arregloPlus *arre, t_impresor * imprime);
void reverse(arregloPlus *arre, t_impresor *imprime);
void bidirectional(arregloPlus *arre, t_impresor *imprime);

//tipos de recorrido
void *begin(arregloPlus *arreglo);
void *end(const arregloPlus *arreglo);
void *next(void *arreglo, size_t tamDato);
void *prev(void *arreglo, size_t tamDato);

//Funcion recorrer
void recorrer(arregloPlus arreglo, t_iterador *tipoIterador, t_impresor *tipoPrint);

//prints
void imprimeInt(void * cosa);
void imprimeLibro(void * cosa);

int main(){
    arregloPlus numeros;
    numeros.tamArreglo = 12;
    numeros.tamDato = sizeof(int);
    numeros.arreglo = (int *) malloc(numeros.tamDato * numeros.tamArreglo);
    int * aux = numeros.arreglo;
    int * fin = numeros.arreglo + (numeros.tamArreglo*numeros.tamDato);

    for (; aux < fin; ++aux) {
        *aux = rand() % 10;
    }
    t_impresor * tipoImpresor = (t_impresor*) malloc(sizeof(t_impresor));
    *tipoImpresor = imprimeInt;

    t_iterador * tipoIterador = (t_iterador*) malloc(sizeof(t_iterador));
    *tipoIterador = forward;

    recorrer(numeros, tipoIterador, tipoImpresor);

    free(numeros.arreglo);
    free(tipoImpresor);
    free(tipoIterador);

      




   /*  libro * prueb = (libro*) malloc(sizeof(libro)*3);
    libro * final, * temp;
    temp = prueb;
    final = prueb + 3;
    prueb->titulo = (char*) malloc(sizeof("lol"));
    prueb->titulo = "lol";
    prueb->paginas = 5;



    while(temp<final) {
        printf("%s, pag: %d\n", temp->titulo, temp->paginas);
        temp++;
    }
    printf("lenght: %d\n", strlen(prueb));
    free(prueb); */
    return (0);
}
//tipos movimiento
void forward(arregloPlus *arre, t_impresor * imprime){
    void *aux = begin(arre);

    printf("Recorrido forward\n");

    for(int i = 0; i < arre->tamArreglo; i++){
        (*imprime)(aux);
        aux = next(aux, arre->tamDato);
    }
    printf("\n");
}
void reverse(arregloPlus *arre, t_impresor *imprime){
    void *aux = end(arre);

    printf("Recorrido en reversa\n");

    for(int i = 0; i < arre->tamArreglo; i++){
        (*imprime)(aux);
        aux = prev(aux, arre->tamDato);
    }
    printf("\n");
}
void bidirectional(arregloPlus *arre, t_impresor *imprime){
    forward(arre, imprime);
    reverse(arre, imprime);
}

//recorridos
void *begin(arregloPlus *arreglo){
    void * temp = arreglo->arreglo;
    return arreglo->arreglo;
}
void *end(const arregloPlus *arreglo){
    return arreglo->arreglo + (arreglo->tamDato * arreglo->tamArreglo) - arreglo->tamDato;
}
void *next(void *arreglo, size_t tamDato){
    void * temp = arreglo + tamDato;
    if (temp = NULL){
        return NULL;
    }
    return temp;    
}
void *prev(void *arreglo, size_t tamDato){
    void * temp = arreglo - tamDato;
    if (temp = NULL){
        return NULL;
    }
    return temp;    
}

//Funcion recorrer
void recorrer(arregloPlus arreglo, t_iterador *tipoIterador, t_impresor *tipoPrint){
    (*tipoIterador)(&arreglo, tipoPrint);
}

//prints
void imprimeInt(void * cosa){
    int * num =(int *) cosa;
    printf("%d \t", *num);
}
void imprimeLibro(void * cosa){
    libro * temp = cosa;
    printf("Titulo: %s, Paginas: %d\t", temp->titulo, temp->paginas);
}