#ifndef PROGRAMAINICIALIZADOR_C
#define PROGRAMAINICIALIZADOR_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>

#define IPC_RESULT_ERROR (-1)

int isNumber(char s[]) {
    for(int i = 0; s[i] != '\0'; i++){
        if (isdigit(s[i]) == 0)
            return 0;
    }
    return 1;
}

static int obtener_memoria_compartida(char *nombre_archivo, int tamano){
    key_t llave;

    llave = ftok(nombre_archivo, 0);
    if(llave == IPC_RESULT_ERROR) {
        return IPC_RESULT_ERROR;
    }

    return shmget(llave, tamano, 0644 | IPC_CREAT);
}

int pedirTamanoMemoria() {
    char inputMemoria[20]; 
        while(true){
            printf("Insertar el tamano de la memoria compartida: ");
            fgets(inputMemoria, sizeof inputMemoria, stdin);
            char* posicionNulo1;

            if((posicionNulo1 = strchr(inputMemoria, '\n')) != NULL) {
                *posicionNulo1 = '\0';
            }

            if(isNumber(inputMemoria) == 0) {
                printf("Input no es valido, por favor solo insertar numeros\n");
            }
            else 
                return atoi(inputMemoria);
        }
}

int main(){
    int tamanoMemoria = pedirTamanoMemoria();

    // Pide el bloque de memoria compartida
    int bloque = obtener_memoria_compartida("ProgramaInicializador.c", tamanoMemoria); 
    if(bloque == IPC_RESULT_ERROR){
        return IPC_RESULT_ERROR;
    }
    // Mapea los contenidos de la memoria compartida para que esten en formato de char*
    char *contenido_bloque_memoria = shmat(bloque, NULL, 0);
    //      Base+offset, string a insertar, tamano del string a insertar
    strncpy(contenido_bloque_memoria + 1, "ol", 2); // Copia el string en la memoria compartida

    shmdt(contenido_bloque_memoria);

    return 0;
}
#endif