#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){
    char * dir = (char*) malloc(255 * sizeof(char));
    getcwd(dir,255);
    strcat(dir,"/");

    printf("Dirección inicio: %s\n", dir);
    struct dirent *dirStruct = NULL;
    
    DIR *carpeta = NULL;
    carpeta = opendir(dir);

    dirStruct = readdir(carpeta);
    while(dirStruct != NULL){

        if(dirStruct->d_type == DT_DIR){
            if(strcmp(dirStruct->d_name,".") != 0 && strcmp(dirStruct->d_name, "..") != 0){
                strcat(dir,dirStruct->d_name);
                printf("Dirección dir encontrado: %s\n", dir);
                sleep(1);
            }
        }
        dirStruct = readdir(carpeta);
    }
    printf("Dirección final: %s\n", dir);

    return 0;
}
// && dirStruct->d_name != "." && dirStruct->d_name != ".."