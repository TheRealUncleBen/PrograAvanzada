#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nombre[30];
    char apellido[30];
    int edad;
    int telefono;
    int disponible;
}paciente;

void ingresar(paciente * camas, int * camasTotales);
void datos(paciente * camas, int noCama);
void alta(paciente * camas, int noCama);
void listado(paciente * camas, int * camasTotales);
int disponibles(paciente * camas, int * camasTotales);

int main(){
    int * numeroCamas = (int *) malloc(sizeof(int));
    *numeroCamas = 5;
    paciente * camas;
    int opcion = 0;
    int noCama = 0;
    int camasLibres = 0;
    
    camas = malloc(*numeroCamas * sizeof(paciente));
    paciente * temp;
    paciente * final = camas + *numeroCamas;
    for(temp = camas; temp < final; temp++){
        temp->disponible = 1;
    }
    printf("Bienvenido al sistema de registro\n");
    while(opcion != 6){
        printf("Seleccione el numero de operacion que desea ejecutar \nMenu: \n 1)Ingresar nuevo paciente \n 2)Obtener datos de una cama \n");
        printf(" 3)Dar de alta un paciente \n 4)Listar pacientes \n 5)Numero de camas disponibles \n 6)Salir del sistema\n");
        scanf("%d", &opcion);
        switch(opcion){
            case 0:
                printf("Opcion invalida\n");
                break;
            case 1:
                //Se manda el apuntador de las camas y el total de camas se manda por referencia por si este cambia 
                ingresar(camas, numeroCamas);
                printf("numero camas: %d\n",*numeroCamas);
                break;
            case 2:
                // noCama es el numero de la cama a revisar
                noCama = 0;
                printf("Ingrese el numero de la cama que desea revisar\n");
                scanf(" %d", &noCama);
                datos(camas, noCama);
                break;
            case 3:
                noCama = 0;
                printf("Ingrese el numero de la cama del paciente que desea dar de alta\n");
                scanf("%d", &noCama);
                alta(camas, noCama);
                break;
            case 4:
                listado(camas, numeroCamas);
                break;
            case 5:
                camasLibres = disponibles(camas, numeroCamas);
                printf("El numero de camas disponibles es: %d \nel numero de camas ocupadas es: %d\n",camasLibres,(*numeroCamas - camasLibres) );
                break;
            case 6:
                printf("Gracias por usar el sistema\n");
                break;
            default:
                printf("Opcion invalida\n");
                break;
        }
    }

    free(camas);
    free(numeroCamas);
    return (0);
}

void ingresar(paciente * camas, int * camasTotales){
    int camasLibres = disponibles(camas, camasTotales);
    //asigna espacio si ya no hay disponibles
    if(camasLibres <= 0){
        *camasTotales += 5;
        
        camas =(paciente *) realloc(camas, (*camasTotales) * sizeof(paciente));
        
        paciente * setup, * final;
        final = camas + *camasTotales;
        
        for(setup = (final - 5); setup < final; setup++){
            setup->disponible = 1;
        }
        /* for(temp = camas; temp < final; temp++){
            temp->disponible = 1;
        } */
    }
    printf("buscando espacio disponible\n");
    //busca el siguiente espacio disponible 
    int salir = 0;
    paciente * ptr;
    paciente * final;
    ptr = camas;
    final = camas + *camasTotales;
        
    for(; ptr < final ; ptr++){
        if(ptr->disponible == 1){
            break;
        }
    }

    //crear nuevo paciente y guardar en espacio correspondiente 
    ptr->disponible = 0;
    printf("Ingrese datos del paciente.\n Apellido: ");
    scanf(" %s", ptr->apellido);

    printf("\nNombre:");
    scanf(" %s", ptr->nombre);

    printf("\nEdad: ");
    scanf(" %d", &ptr->edad);

    printf("\nNumero de contacto: ");
    scanf(" %d", &ptr->telefono);
    printf("\n"); 
}

void datos(paciente * camas, int noCama){
    paciente * aux = camas;
    aux += noCama - 1;
    if(aux->disponible == 0)
        printf("Cama: %d. \tNombre: %s \tApellido: %s \n\t Edad: %d \tTelefono de contacto: %d\n", noCama, aux->nombre, aux->apellido, aux->edad, aux->telefono);
    else
        printf("Cama disponible\n");    
}
void alta(paciente * camas, int noCama){
    paciente * aux = camas;
    aux += noCama - 1;

    aux->disponible = 1;
    printf("Paciente dado de alta\n");
}
void listado(paciente * camas, int * camasTotales){
    for(int i = 1; i <= *camasTotales; i++){
        datos(camas,i);
    }
    printf("Fin de lista\n");
}
int disponibles(paciente * camas, int * camasTotales){
    int libres = 0;
    printf("camas totales %d \n libres %d ", *camasTotales, libres);
    paciente * aux = camas;
    paciente * final = camas + *camasTotales;
    for(; aux < final; aux++){
        if(aux->disponible == 1){
            libres++;
        }
    }
    return libres;
}