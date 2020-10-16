#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
void manejoDir(){
    struct stat buffer;
    int exist = stat("datos",&buffer);
    if(exist == 0)
        system("rm -r datos");
    system("mkdir datos");
}

int main(){
    manejoDir();
    
    return 0;
}