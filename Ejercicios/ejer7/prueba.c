#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int main(){
    int n = 3;
    char * buffer = (char *) malloc(sizeof(int) * 9);
    FILE *archivo;
    for(int i =0; i<n; i++){
        int count = 0;
        sprintf(buffer,"datos/a%d",i);
        archivo = fopen(buffer,"w");
        while(count <20){
            fputc('x',archivo);
            count ++;
        }
        fclose(archivo);
    }

    free(buffer);
}