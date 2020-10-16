
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define N 10

typedef struct 
{
    char *title;
    int pages;
} Book;

// Declaring type of functions
// Iterator function
typedef void (*printer)(void *);
typedef void (*iterator)(void *, printer *, size_t);

// Recorre function
void recorre(void *, iterator *, printer *, size_t);

// Functionalities
void *begin(void *, size_t);
void *end(void *, size_t);
void *next(void *, size_t);
void *prev(void *, size_t);

// Iterator functions
void forward(void *, printer *, size_t);
void backward(void *, printer *, size_t);
void bidirectional(void *, printer *, size_t);

// Printing functions
void printInt(void *);
void printFloat(void *);
void printBook(void *);

int main(int argc, char const *argv[])
{
    // Testing w array of integers
    int *array = (int *) malloc(N * sizeof(int));
    int i = 1;
    int *last = array + N;

    for (int *aux = array; aux < last; ++aux)
    {
        *aux = i++;
    }
    printer *toPrint = (printer *)malloc(sizeof(printer));
    *toPrint = printInt;
    
    iterator *it = (iterator *)malloc(sizeof(iterator));
    *it = bidirectional;

    size_t position = sizeof(int);

    recorre(array, it, toPrint, position);

    // Testing with array of Books

    Book *books = (Book *) malloc(N * sizeof(Book));
    Book *lastBook = books + N;
    int j = 0;
    for (Book *book = books; book < lastBook; ++book)
    {
        book->title =(char *)malloc(sizeof(char) * 30);
        strcpy(book->title, "Title");
        j += 111;
        book->pages = j;
    }
    position = sizeof(Book);
    *it = bidirectional;
    *toPrint = printBook;
    recorre(books, it, toPrint, position);

    free(array);
    free(it);
    free(toPrint);

    for (Book *book = books; book < lastBook; book++)
    {
        free(book->title);
    }
    free(books);
    // for (size_t i = 0; i < count; i++)
    // {
    //     /* code */
    // }
    return 0;
}

void recorre(void *vector, iterator *it, printer *toPrint, size_t position)
{
    // printf("hey");
    (*it)(vector, toPrint, position);
}

void *begin(void *array, size_t position)
{
    void *aux = array;
    // while (prev(aux, position) != NULL)
    // {
    //     aux = prev(aux, position);
    // }
    return aux;
}
void *end(void *array, size_t position)
{
    void *aux = array;
    int i = 0;
    while (i < 10)
    {
        i++;
        aux = aux + position;
    }
    return aux - position;
}
void *next(void * array, size_t position)
{
    void *aux = array + position;
    if (aux == NULL)
    {
        return NULL;
    }
    return aux;
}
void *prev(void * array, size_t position)
{
    void *aux = array - position;
    if (aux == NULL)
    {
        return NULL;
    }
    return aux;
}

void forward(void *vector, printer *toPrint, size_t position)
{
    printf("Forward Iteration: \n");
    void *aux = begin(vector, position);
    int i = 0;
    do
    {
        (* toPrint)(aux);
        aux = next(aux, position);
        i++;
    } while (i < 10);
    printf("\n");
}
void backward(void *vector, printer *toPrint, size_t position)
{
    printf("Backward Iteration: \n");
    void *aux = end(vector, position);
    int i = 0;
    do
    {
        (*toPrint)(aux);
        aux = prev(aux, position);
        i++;
    } while (i < 10);
    printf("\n");
}
void bidirectional(void *vector, printer *toPrint, size_t position)
{
    forward(vector, toPrint, position);
    backward(vector, toPrint, position);
}

void printInt(void * position)
{
    int *value = (int *)position;
    printf("%d \n", *value);
}
void printBook(void * position)
{
    Book *aux = position;
    printf("Title :%s\n", aux->title);
    printf("Pages: %d\n", aux->pages);
    printf("\n");
}